#!/usr/bin/env python3
import numpy as np
from enum import Enum, auto

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.qos import QoSProfile, DurabilityPolicy

from std_msgs.msg import String
from std_srvs.srv import Trigger
from sensor_msgs.msg import JointState
from geometry_msgs.msg import PoseStamped
from builtin_interfaces.msg import Duration
from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint

from tf2_ros import Buffer, TransformListener
import tf2_geometry_msgs

import pinocchio as pin
import pink
from pink.tasks import FrameTask, PostureTask


EE_FRAME    = "lbr_link_ee"
BASE_FRAME  = "lbr_link_0"
JOINT_NAMES = ["lbr_A1", "lbr_A2", "lbr_A3", "lbr_A4", "lbr_A5", "lbr_A6", "lbr_A7"]

APPROACH_OFFSET = 0.10   # m
HIT_VELOCITY    = 0.5    # m/s
HIT_DISTANCE    = 0.15   # m
DT              = 0.001  # trajectory waypoint spacing
IK_DT           = 0.01
IK_N_STEPS      = 500
APPROACH_DURATION = 5.0
RECOIL_DURATION   = 2.0
NULL_SPACE_GAIN   = 0.5
N_HIT_STEPS = int(HIT_DISTANCE / (HIT_VELOCITY * DT))


class Phase(Enum):
    IDLE = auto()
    APPROACH = auto()
    HIT = auto()
    RECOIL = auto()


class PinkHitNode(Node):
    def __init__(self):
        super().__init__("pink_hit_node")
        self.phase = Phase.IDLE

        self.model = None
        self.data = None
        self.current_q = None
        self.object_pose_base = None
        self.q_start = self.q_approach = self.waypoints = None

        urdf_qos = QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL)
        self.create_subscription(String, '/lbr/robot_description', self.on_urdf, urdf_qos)
        self.create_subscription(JointState, '/lbr/joint_states', self.on_joint_state, 10)
        self.create_subscription(PoseStamped, '/object_pose', self.on_object_pose, 10)
        self.create_service(Trigger, 'start_push', self.on_start_push)


        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        self.traj_client = ActionClient(
            self, FollowJointTrajectory,
            '/lbr/joint_trajectory_controller/follow_joint_trajectory')
        self.get_logger().info("Waiting for trajectory controller...")
        self.traj_client.wait_for_server()  # fine to block here — before spin() starts

    # ── subscriptions ──────────────────────────────────────────────────────
    def on_urdf(self, msg: String):
        self.model = pin.buildModelFromXML(msg.data)
        self.data = self.model.createData()
        self.get_logger().info("URDF received, model ready")

    def on_joint_state(self, msg: JointState):
        pos_map = dict(zip(msg.name, msg.position))
        self.current_q = np.array([pos_map[n] for n in JOINT_NAMES])

    def on_object_pose(self, msg: PoseStamped):
        if self.model is None:
            self.get_logger().warn("Object pose received before URDF ready, ignoring")
            return
        try:
            self.object_pose_base = self.tf_buffer.transform(
                msg, BASE_FRAME, timeout=rclpy.duration.Duration(seconds=0.1))
        except Exception as e:
            self.get_logger().warn(f"TF transform failed: {e}")

    # ── trigger ────────────────────────────────────────────────────────────
    def on_start_push(self, request, response):
        if self.model is None or self.current_q is None or self.object_pose_base is None:
            response.success = False
            response.message = "Not ready (missing URDF, joint state, or object pose)"
            return response
        if self.phase != Phase.IDLE:
            response.success = False
            response.message = f"Already running (phase={self.phase.name})"
            return response

        self.get_logger().info("Solving IK for approach + hit waypoints...")
        self._solve_all()
        self.phase = Phase.APPROACH
        self._send_approach_goal()

        response.success = True
        response.message = "Hit sequence started"
        return response

    # ── IK solving ───────────────────────────────────────
    def _solve_all(self):
        q_start = self.current_q.copy()
        pos = self.object_pose_base.pose.position
        quat = self.object_pose_base.pose.orientation
        object_pos = np.array([pos.x, pos.y, pos.z])
        R = pin.Quaternion(quat.w, quat.x, quat.y, quat.z).toRotationMatrix()
        hit_direction = R[:, 0]
        pre_impact_pos = object_pos - hit_direction * APPROACH_OFFSET

        q_approach = self._solve_ik_to(pre_impact_pos, q_start)

        v_desired = np.zeros(6)
        v_desired[:3] = hit_direction * HIT_VELOCITY
        waypoints = self._solve_hit_waypoints(q_approach, v_desired)

        self.q_start, self.q_approach, self.waypoints = q_start, q_approach, waypoints

    def _solve_ik_to(self, target_pos, q_init, n_steps=IK_N_STEPS):
        target = pin.SE3(pin.utils.rotate("y", np.pi), target_pos)
        ee_task = FrameTask(EE_FRAME, position_cost=1.0, orientation_cost=1.0)
        ee_task.set_target(target)
        posture_task = PostureTask(cost=1e-3)
        posture_task.set_target(q_init)

        q = q_init.copy()
        for _ in range(n_steps):
            configuration = pink.Configuration(self.model, self.data, q)
            vel = pink.solve_ik(configuration, [ee_task, posture_task], IK_DT, solver="quadprog")
            q = configuration.integrate(vel, IK_DT)
        return q

    def _solve_hit_waypoints(self, q_approach, v_desired):
        frame_id = self.model.getFrameId(EE_FRAME)
        I = np.eye(len(JOINT_NAMES))
        waypoints = []
        q = q_approach.copy()
        for _ in range(N_HIT_STEPS):
            pin.forwardKinematics(self.model, self.data, q)
            pin.updateFramePlacements(self.model, self.data)
            J = pin.computeFrameJacobian(
                self.model, self.data, q, frame_id, pin.ReferenceFrame.LOCAL_WORLD_ALIGNED)
            J_pinv = np.linalg.pinv(J)
            dq_primary = J_pinv @ v_desired
            dq_posture = -NULL_SPACE_GAIN * (q - q_approach)
            dq_null = (I - J_pinv @ J) @ dq_posture
            q = pin.integrate(self.model, q, (dq_primary + dq_null) * DT)
            waypoints.append(q.copy())
        return waypoints

    # ── trajectory builders ────────────────────────────────────────────────
    @staticmethod
    def _make_point(q, t_sec):
        pt = JointTrajectoryPoint()
        pt.positions = q.tolist()
        pt.time_from_start = Duration(sec=int(t_sec), nanosec=int((t_sec % 1) * 1e9))
        return pt

    def _send_approach_goal(self):
        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = JOINT_NAMES
        goal.trajectory.points = [
            self._make_point(self.q_start, 0.0),
            self._make_point(self.q_approach, APPROACH_DURATION),
        ]
        self._send_goal(goal, "Approach", self._on_approach_done)

    def _send_hit_goal(self):
        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = JOINT_NAMES
        goal.trajectory.points = [
            self._make_point(q, (i + 1) * DT) for i, q in enumerate(self.waypoints)
        ]
        self._send_goal(goal, "Hit", self._on_hit_done)

    def _send_recoil_goal(self):
        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = JOINT_NAMES
        goal.trajectory.points = [
            self._make_point(self.waypoints[-1], 0.0),
            self._make_point(self.q_approach, RECOIL_DURATION),
        ]
        self._send_goal(goal, "Recoil", self._on_recoil_done)

    # ── execution — chained callbacks, no threading/blocking ───────────────
    def _send_goal(self, goal, phase_name, on_done_cb):
        def on_goal_response(future):
            handle = future.result()
            if not handle.accepted:
                self.get_logger().error(f"[{phase_name}] goal rejected")
                self.phase = Phase.IDLE
                return
            self.get_logger().info(f"[{phase_name}] accepted, executing...")
            handle.get_result_async().add_done_callback(on_done_cb)
        self.traj_client.send_goal_async(goal).add_done_callback(on_goal_response)

    def _on_approach_done(self, future):
        if future.result().status != 4:
            self.get_logger().error("[Approach] failed")
            self.phase = Phase.IDLE
            return
        self.get_logger().info("[Approach] complete")
        self.phase = Phase.HIT
        self._send_hit_goal()

    def _on_hit_done(self, future):
        if future.result().status != 4:
            self.get_logger().error("[Hit] failed")
            self.phase = Phase.IDLE
            return
        self.get_logger().info("[Hit] complete")
        self.phase = Phase.RECOIL
        self._send_recoil_goal()

    def _on_recoil_done(self, future):
        if future.result().status != 4:
            self.get_logger().error("[Recoil] failed")
        else:
            self.get_logger().info("[Recoil] complete. Sequence done.")
        self.phase = Phase.IDLE  # ready to trigger again


def main(args=None):
    rclpy.init(args=args)
    rclpy.spin(PinkHitNode())
    rclpy.shutdown()


if __name__ == "__main__":
    main()