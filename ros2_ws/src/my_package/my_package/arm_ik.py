import rclpy
from rclpy.node import Node
import numpy as np
import pinocchio as pin
import pink
from pink.tasks import FrameTask, PostureTask
from pink import solve_ik
from lbr_fri_idl.msg import LBRJointPositionCommand, LBRState
from rcl_interfaces.srv import GetParameters

URDF_PATH = "/tmp/iiwa7.urdf"
EE_FRAME = "lbr_link_ee"

OBJECT_POSITION = np.array([0.5, 0.0, 0.4])
APPROACH_OFFSET = 0.1
HIT_VELOCITY = 0.05
HIT_DISTANCE = 0.15


class PinkHitNode(Node):
    def __init__(self):
        super().__init__("pink_hit_node")

        # load robot
        self._robot = pin.RobotWrapper.BuildFromURDF(URDF_PATH)
        self._model = self._robot.model
        self._data = self._robot.data

        # tasks
        self._ee_task = FrameTask(
            EE_FRAME,
            position_cost=1.0,
            orientation_cost=0.1,
        )
        self._posture_task = PostureTask(cost=1e-3)
        self._posture_task.set_target(self._robot.q0)

        self._phase = "idle"
        self._hit_progress = 0.0
        self._dt = None

        self._cmd_pub = self.create_publisher(
            LBRJointPositionCommand, "command/lbr_joint_position_command", 1
        )
        self._state_sub = self.create_subscription(
            LBRState, "lbr_state", self._on_lbr_state, 1
        )

        self.get_logger().info("Pink hit node ready.")

    def set_dt(self, dt: float):
        self._dt = dt

    def _on_lbr_state(self, lbr_state: LBRState) -> None:
        if self._dt is None:
            return

        if lbr_state.session_state != 4:
            self._phase = "idle"
            self._hit_progress = 0.0
            return

        q = np.array(lbr_state.measured_joint_position)
        configuration = pink.Configuration(self._model, self._data, q)

        if self._phase == "idle":
            self._phase = "approach"
            self.get_logger().info("Starting approach...")

        if self._phase == "approach":
            self._do_approach(configuration)
        elif self._phase == "hit":
            self._do_hit(configuration)

    def _do_approach(self, configuration: pink.Configuration):
        target_pos = OBJECT_POSITION.copy()
        target_pos[0] -= APPROACH_OFFSET

        target = pin.SE3(np.eye(3), target_pos)
        self._ee_task.set_target(target)

        velocity = solve_ik(
            configuration,
            [self._ee_task, self._posture_task],
            self._dt,
            solver="quadprog"
        )
        q_next = configuration.integrate(velocity, self._dt)

        # check if close enough
        ee_id = self._model.getFrameId(EE_FRAME)
        pin.forwardKinematics(self._model, self._data, q_next)
        pin.updateFramePlacements(self._model, self._data)
        ee_pos = self._data.oMf[ee_id].translation
        if np.linalg.norm(ee_pos - target_pos) < 0.01:
            self.get_logger().info("At pre-impact pose, starting hit...")
            self._phase = "hit"
            self._hit_progress = 0.0

        self._publish(q_next)

    def _do_hit(self, configuration: pink.Configuration):
        self._hit_progress += HIT_VELOCITY * self._dt

        target_pos = OBJECT_POSITION.copy()
        target_pos[0] += self._hit_progress - APPROACH_OFFSET

        target = pin.SE3(np.eye(3), target_pos)
        self._ee_task.set_target(target)

        velocity = solve_ik(
            configuration,
            [self._ee_task, self._posture_task],
            self._dt,
            solver="quadprog"
        )
        q_next = configuration.integrate(velocity, self._dt)

        if self._hit_progress >= HIT_DISTANCE:
            self.get_logger().info("Hit complete.")
            self._phase = "done"

        self._publish(q_next)

    def _publish(self, q: np.ndarray):
        cmd = LBRJointPositionCommand()
        cmd.joint_position = q.tolist()
        self._cmd_pub.publish(cmd)


def main(args=None):
    rclpy.init(args=args)
    node = PinkHitNode()
    node.set_dt(1.0 / 100.0)  # 100 Hz mock update rate
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()