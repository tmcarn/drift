import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
import numpy as np
import pinocchio as pin
import pink
from pink.tasks import FrameTask, PostureTask
from pink import solve_ik
from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint
from builtin_interfaces.msg import Duration

URDF_PATH = "/tmp/iiwa7.urdf"
EE_FRAME = "lbr_link_ee"
JOINT_NAMES = ["lbr_A1", "lbr_A2", "lbr_A3", "lbr_A4", "lbr_A5", "lbr_A6", "lbr_A7"]

OBJECT_POSITION = np.array([0.0, 0.5, 0.5])
APPROACH_OFFSET = 0.1
HIT_VELOCITY = 0.8   # m/s
HIT_DISTANCE = 0.15   # m
DT = 0.01             # IK integration timestep
N_HIT_STEPS = int(HIT_DISTANCE / (HIT_VELOCITY * DT))


class PinkHitNode(Node):
    def __init__(self):
        super().__init__("pink_hit_node")

        self._robot = pin.RobotWrapper.BuildFromURDF(URDF_PATH)
        self._model = self._robot.model
        self._data = self._robot.data

        self._traj_client = ActionClient(
            self,
            FollowJointTrajectory,
            "/lbr/joint_trajectory_controller/follow_joint_trajectory"
        )

        self.get_logger().info("Waiting for trajectory controller...")
        self._traj_client.wait_for_server()
        self.get_logger().info("Ready.")

        # run once after node starts
        self._run_timer = self.create_timer(1.0, self._run)

    def _solve_ik_to(self, target_pos: np.ndarray, q_init: np.ndarray, n_steps: int = 200):
        ee_task = FrameTask(EE_FRAME, position_cost=1.0, orientation_cost=1.0)
        posture_task = PostureTask(cost=1e-3)
        posture_task.set_target(q_init)

        target_rot = pin.utils.rotate("y", np.pi)
        target = pin.SE3(target_rot, target_pos)
        ee_task.set_target(target)

        q = q_init.copy()
        for _ in range(n_steps):
            configuration = pink.Configuration(self._model, self._data, q)
            velocity = solve_ik(
                configuration,
                [ee_task, posture_task],
                DT,
                solver="quadprog"
            )
            q = configuration.integrate(velocity, DT)

        return q
    
    def _wait_for_enter(self):
        input("Press Enter to execute hit...")
        self.get_logger().info("Go signal received.")

    def _run(self):
        self._run_timer.cancel()  # run once

        q0 = self._robot.q0.copy()

        # solve IK for pre-impact pose
        self.get_logger().info("Solving IK for approach...")
        pre_impact_pos = OBJECT_POSITION.copy()
        pre_impact_pos[0] -= APPROACH_OFFSET
        q_approach = self._solve_ik_to(pre_impact_pos, q0)

        self._wait_for_enter()

        # solve IK for hit waypoints at constant velocity
        self.get_logger().info("Solving IK for hit trajectory...")
        waypoints = [q_approach]
        q_prev = q_approach.copy()
        for i in range(1, N_HIT_STEPS + 1):
            target_pos = pre_impact_pos.copy()
            target_pos[0] += i * HIT_VELOCITY * DT
            q_wp = self._solve_ik_to(target_pos, q_prev, n_steps=10)
            waypoints.append(q_wp)
            q_prev = q_wp

        # build trajectory goal
        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = JOINT_NAMES

        # approach point at t=5s
        p0 = JointTrajectoryPoint()
        p0.positions = q_approach.tolist()
        p0.time_from_start = Duration(sec=5)
        goal.trajectory.points.append(p0)

        # hit waypoints after approach
        hit_duration = HIT_DISTANCE / HIT_VELOCITY  # seconds
        for i, q_wp in enumerate(waypoints[1:]):
            p = JointTrajectoryPoint()
            p.positions = q_wp.tolist()
            t = 5.0 + (i + 1) * (hit_duration / N_HIT_STEPS)
            p.time_from_start = Duration(sec=int(t), nanosec=int((t % 1) * 1e9))
            goal.trajectory.points.append(p)

        self.get_logger().info("Sending trajectory...")
        self._traj_client.send_goal_async(goal).add_done_callback(self._goal_cb)

    def _goal_cb(self, future):
        handle = future.result()
        if not handle.accepted:
            self.get_logger().error("Trajectory rejected")
            return
        self.get_logger().info("Trajectory accepted, executing...")
        handle.get_result_async().add_done_callback(
            lambda f: self.get_logger().info("Done.")
        )


def main(args=None):
    rclpy.init(args=args)
    node = PinkHitNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()