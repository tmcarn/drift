#!/usr/bin/env python3
"""
pink_hit_node.py
----------------
Three-phase hitting motion for the KUKA iiwa7 using Pink IK.

  Approach  — current config → pre-impact config
  Hit       — pre-impact → through object at constant Cartesian velocity
  Recoil    — post-hit config → pre-impact config
"""

import threading
import time

import numpy as np
import pinocchio as pin
import pink
from pink import solve_ik
from pink.tasks import FrameTask, PostureTask

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from builtin_interfaces.msg import Duration
from control_msgs.action import FollowJointTrajectory
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectoryPoint

from tf2_ros import Buffer, TransformListener
import rclpy.time
import rclpy.duration


# ── Constants ──────────────────────────────────────────────────────────────────

URDF_PATH   = "/tmp/iiwa7.urdf"
EE_FRAME    = "lbr_link_ee"
JOINT_NAMES = ["lbr_A1", "lbr_A2", "lbr_A3", "lbr_A4", "lbr_A5", "lbr_A6", "lbr_A7"]

WORLD_FRAME = "world"
OBJECT_FRAME = "object"

APPROACH_OFFSET   = 0.1    # m   — stop this far before the object
HIT_VELOCITY      = 0.5    # m/s — desired Cartesian EE speed during hit
HIT_DISTANCE      = 0.15   # m   — total Cartesian distance to travel
DT          = 0.001   # trajectory timestep — controls waypoint density
IK_DT       = 0.01    # IK integration timestep — controls convergence speed
IK_N_STEPS  = 500     # more steps to ensure convergence

APPROACH_DURATION = 5.0    # s   — how long to take moving to pre-impact
RECOIL_DURATION   = 2.0    # s   — how long to take returning after hit
NULL_SPACE_GAIN   = 0.5    # how hard to pull joints toward posture reference

N_HIT_STEPS = int(HIT_DISTANCE / (HIT_VELOCITY * DT))


# ── Node ───────────────────────────────────────────────────────────────────────

class PinkHitNode(Node):

    def __init__(self):
        super().__init__("pink_hit_node")

        self._robot = pin.RobotWrapper.BuildFromURDF(URDF_PATH)
        self._model = self._robot.model
        self._data  = self._robot.data

        self._traj_client = ActionClient(
            self,
            FollowJointTrajectory,
            "/lbr/joint_trajectory_controller/follow_joint_trajectory",
        )
        self.get_logger().info("Waiting for trajectory controller...")
        self._traj_client.wait_for_server()

        # Joint state — populated by subscription, read by background thread
        self._current_q: np.ndarray | None = None
        self._js_lock = threading.Lock()
        self.create_subscription(JointState, "/lbr/joint_states", self._js_cb, 10)

        self._tf_buffer = Buffer()
        self._tf_listener = TransformListener(self._tf_buffer, self)


        # Run the sequence in a background thread so input() and threading.Event
        # don't block the ROS executor (which lives on the main thread).
        threading.Thread(target=self._run_sequence, daemon=True).start()




    # ── Joint state ───────────────────────────────────────────────────────────

    def _js_cb(self, msg: JointState) -> None:
        pos_map = dict(zip(msg.name, msg.position))
        with self._js_lock:
            self._current_q = np.array([pos_map[n] for n in JOINT_NAMES])

    def _get_current_q(self) -> np.ndarray:
        """Block until the first joint state arrives, then return it."""
        self.get_logger().info("Waiting for joint states...")
        while rclpy.ok():
            with self._js_lock:
                if self._current_q is not None:
                    q = self._current_q.copy()
                    break
            time.sleep(0.05)
        self.get_logger().info("Joint state received.")
        return q
    
    # -- Pose helpers ------------
    def _get_object_pose(self):
        self.get_logger().info("Looking up object pose from TF...")
        while rclpy.ok():
            try:
                tf = self._tf_buffer.lookup_transform(
                    'world',
                    'object',
                    rclpy.time.Time(),
                    timeout=rclpy.duration.Duration(seconds=1.0),
                )
                t = tf.transform.translation
                r = tf.transform.rotation
                pos = np.array([t.x, t.y, t.z])
                quat = np.array([r.x, r.y, r.z, r.w])

                self.get_logger().info(f"OBJECT: {pos}")
                return pos, quat
            
            except Exception as e:
                self.get_logger().warn(f"TF lookup failed: {e}, retrying...")
                time.sleep(0.5)

    def _to_base_frame(self, pos_world: np.ndarray):
        while rclpy.ok():
            try:
                tf = self._tf_buffer.lookup_transform(
                    'world',
                    'lbr_link_0',
                    rclpy.time.Time(),
                    timeout=rclpy.duration.Duration(seconds=1.0),
                )
                t = tf.transform.translation
                r = tf.transform.rotation
                R = pin.Quaternion(r.w, r.x, r.y, r.z).toRotationMatrix()
                p = np.array([t.x, t.y, t.z])

                if np.linalg.norm(p) < 0.1:
                    self.get_logger().warn("Got near-identity transform, retrying...")
                    time.sleep(0.1)
                    continue

                self.get_logger().info(f"R:{R}, position:{p}")
                return R.T @ (pos_world - p), R
            
            except Exception as e:
                self.get_logger().warn(f"base frame lookup failed: {e}, retrying...")
                time.sleep(0.5)

    def _wait_for_tf(self, target: str, source: str) -> None:
        self.get_logger().info(f"Waiting for TF: {target} -> {source}...")
        while rclpy.ok():
            try:
                self._tf_buffer.lookup_transform(
                    target, source,
                    rclpy.time.Time(),
                    timeout=rclpy.duration.Duration(seconds=1.0),
                )
                self.get_logger().info(f"TF ready: {target} -> {source}")
                return
            except Exception:
                time.sleep(0.1)


    # ── IK helpers ────────────────────────────────────────────────────────────

    def _solve_ik_to(
        self,
        target_pos: np.ndarray,
        q_init: np.ndarray,
        n_steps: int = IK_N_STEPS,
    ) -> np.ndarray:
        """Integrate IK from q_init toward target_pos. Returns final joint config."""
        target = pin.SE3(pin.utils.rotate("y", np.pi), target_pos)

        ee_task = FrameTask(EE_FRAME, position_cost=1.0, orientation_cost=1.0)
        ee_task.set_target(target)

        posture_task = PostureTask(cost=1e-3)
        posture_task.set_target(q_init)

        q = q_init.copy()
        for _ in range(n_steps):
            cfg = pink.Configuration(self._model, self._data, q)
            vel = solve_ik(cfg, [ee_task, posture_task], IK_DT, solver="quadprog")
            q   = cfg.integrate(vel, IK_DT)
        return q

    def _solve_hit_waypoints(
        self,
        q_approach: np.ndarray,
        v_desired: np.ndarray,
    ) -> list[np.ndarray]:
        """
        Compute hit waypoints using direct Jacobian control.

        Rather than specifying a target position and running IK toward it,
        we specify the Cartesian velocity we want and map it to joint
        velocities via the Jacobian pseudoinverse. This guarantees a straight
        line because we're directly commanding zero Y and Z velocity.

          v_cartesian = J @ dq        (Jacobian maps joint vel to EE vel)
          dq = J+ @ v_cartesian       (pseudoinverse inverts that)

        The null-space term (I - J+J) @ dq_posture uses the iiwa7's redundant
        7th DOF to pull joints toward q_approach without affecting EE motion,
        keeping the config well-conditioned across the trajectory.
        """
        # Desired EE velocity: translate along world X only, nothing else.
        # Indices 0-2 = linear xyz, 3-5 = angular xyz.
        

        frame_id = self._model.getFrameId(EE_FRAME)
        I        = np.eye(len(JOINT_NAMES))

        waypoints: list[np.ndarray] = []
        q = q_approach.copy()

        for _ in range(N_HIT_STEPS):
            # Update kinematics so the Jacobian reflects current q
            pin.forwardKinematics(self._model, self._data, q)
            pin.updateFramePlacements(self._model, self._data)

            # LOCAL_WORLD_ALIGNED: Jacobian columns are expressed in world-axis
            # directions but evaluated at the EE position. This means
            # v_desired[0] = HIT_VELOCITY in the world X direction, regardless
            # of how the EE is currently oriented.
            J = pin.computeFrameJacobian(
                self._model, self._data, q, frame_id,
                pin.ReferenceFrame.LOCAL_WORLD_ALIGNED,
            )

            J_pinv = np.linalg.pinv(J)

            # Primary task: achieve v_desired exactly
            dq_primary = J_pinv @ v_desired

            # Null-space task: drift joints back toward q_approach.
            # The projection (I - J+J) removes any component that would
            # affect EE motion, so this is truly free of Cartesian side-effects.
            dq_posture = -NULL_SPACE_GAIN * (q - q_approach)
            dq_null    = (I - J_pinv @ J) @ dq_posture

            # pin.integrate handles joint-space geometry correctly
            q = pin.integrate(self._model, q, (dq_primary + dq_null) * DT)
            waypoints.append(q.copy())

        self._verify_straight_line(q_approach, waypoints)

        return waypoints
    
    def _verify_straight_line(
            self,
            q_approach: np.ndarray,
            waypoints: list[np.ndarray],
        ) -> None:
        """
        Log the EE position at each waypoint and report max lateral deviation.
        Run this during development to confirm the hit path is straight.
        """
        frame_id = self._model.getFrameId(EE_FRAME)

        pin.forwardKinematics(self._model, self._data, q_approach)
        pin.updateFramePlacements(self._model, self._data)
        p_start = self._data.oMf[frame_id].translation.copy()

        deviations = []
        for q in waypoints:
            pin.forwardKinematics(self._model, self._data, q)
            pin.updateFramePlacements(self._model, self._data)
            p = self._data.oMf[frame_id].translation.copy()
            lateral = np.linalg.norm(p[1:] - p_start[1:])   # Y and Z deviation
            deviations.append(lateral)

        self.get_logger().info(
            f"Hit path: max lateral deviation = {max(deviations)*1000:.3f} mm "
            f"over {len(waypoints)} steps"
        )


    # ── Trajectory builders ───────────────────────────────────────────────────
    # Each method takes joint configs and returns a ready-to-send Goal.
    # Nothing is executed here — building and sending are kept separate.

    @staticmethod
    def _make_point(q: np.ndarray, t_sec: float) -> JointTrajectoryPoint:
        pt = JointTrajectoryPoint()
        pt.positions = q.tolist()
        pt.time_from_start = Duration(
            sec=int(t_sec),
            nanosec=int((t_sec % 1) * 1e9),
        )
        return pt

    def _build_approach_trajectory(
        self,
        q_start: np.ndarray,
        q_approach: np.ndarray,
    ) -> FollowJointTrajectory.Goal:
        """
        Two-point trajectory: current config → pre-impact config.
        The controller fills in smooth interpolation between them.
        """
        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = JOINT_NAMES
        goal.trajectory.points = [
            self._make_point(q_start,    0.0),
            self._make_point(q_approach, APPROACH_DURATION),
        ]
        return goal

    def _build_hit_trajectory(
        self,
        waypoints: list[np.ndarray],
    ) -> FollowJointTrajectory.Goal:
        """
        One point per timestep, spaced DT seconds apart.
        The tight time spacing is what enforces the Cartesian hit velocity —
        the controller has to move fast enough to reach each waypoint on time.
        """
        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = JOINT_NAMES
        goal.trajectory.points = [
            self._make_point(q, (i + 1) * DT)
            for i, q in enumerate(waypoints)
        ]
        return goal

    def _build_recoil_trajectory(
        self,
        q_hit_final: np.ndarray,
        q_approach: np.ndarray,
    ) -> FollowJointTrajectory.Goal:
        """
        Two-point trajectory: post-hit config → pre-impact config.
        """
        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = JOINT_NAMES
        goal.trajectory.points = [
            self._make_point(q_hit_final, 0.0),
            self._make_point(q_approach,  RECOIL_DURATION),
        ]
        return goal


    # ── Execution ─────────────────────────────────────────────────────────────

    def _execute_trajectory(
        self,
        goal: FollowJointTrajectory.Goal,
        phase_name: str,
    ) -> bool:
        """
        Send a trajectory goal and block the calling thread until the
        controller signals completion (or failure).
        Uses threading.Event so the ROS executor thread stays free.
        """
        done    = threading.Event()
        success = [True]   # list so the nested closure can write to it

        def on_result(future):
            result = future.result()
            # GoalStatus.STATUS_SUCCEEDED == 4
            if result.status != 4:
                self.get_logger().error(
                    f"[{phase_name}] failed — status {result.status}"
                )
                success[0] = False
            else:
                self.get_logger().info(f"[{phase_name}] complete.")
            done.set()

        def on_goal_response(future):
            handle = future.result()
            if not handle.accepted:
                self.get_logger().error(f"[{phase_name}] goal rejected by controller.")
                success[0] = False
                done.set()
                return
            self.get_logger().info(f"[{phase_name}] accepted, executing...")
            handle.get_result_async().add_done_callback(on_result)

        self._traj_client.send_goal_async(goal).add_done_callback(on_goal_response)
        done.wait()
        return success[0]


    # ── Main sequence ─────────────────────────────────────────────────────────

    def _run_sequence(self) -> None:
        """
        Runs entirely in a background thread.

        Separating IK solving from execution means:
          1. All phases are verified feasible before the robot moves at all.
          2. The hit trajectory is ready instantly when the user confirms,
             with no solve delay between approach finishing and hit starting.
        """
        self._wait_for_tf('world', 'object')
        self._wait_for_tf('world', 'lbr_link_0')

        q_start = self._get_current_q()

        object_pos, object_quat = self._get_object_pose()
        self.get_logger().info(f"OBJECT POS:{object_pos}")
        R = pin.Quaternion(object_quat[3], object_quat[0], object_quat[1], object_quat[2]).toRotationMatrix()
        hit_direction = R[:, 0]  # local X axis of object in world frame
        pre_impact_pos = object_pos - (hit_direction * APPROACH_OFFSET)
        pre_impact_pos_base, R_b2w = self._to_base_frame(pre_impact_pos)

        self.get_logger().info(f"HIT DIR:{hit_direction}")
        self.get_logger().info(f"PREIMPACT:{pre_impact_pos_base}")


        self.get_logger().info("Solving IK for approach config...")
        q_approach = self._solve_ik_to(pre_impact_pos_base, q_start)

        # verify IK result
        pin.forwardKinematics(self._model, self._data, q_approach)
        pin.updateFramePlacements(self._model, self._data)
        frame_id = self._model.getFrameId(EE_FRAME)
        ee_pos = self._data.oMf[frame_id].translation.copy()
        self.get_logger().info(f"Target:  {pre_impact_pos_base}")
        self.get_logger().info(f"EE pos after IK: {ee_pos}")

        hit_direction_base = R_b2w.T @ hit_direction
        v_desired    = np.zeros(6)
        v_desired[:3] = hit_direction_base * HIT_VELOCITY

        self.get_logger().info(f"Solving hit waypoints ({N_HIT_STEPS} steps)...")
        waypoints   = self._solve_hit_waypoints(q_approach, v_desired)
        q_hit_final = waypoints[-1]

        self.get_logger().info("All solved. Ready to execute.")

        approach_goal = self._build_approach_trajectory(q_start, q_approach)
        hit_goal      = self._build_hit_trajectory(waypoints)
        recoil_goal   = self._build_recoil_trajectory(q_hit_final, q_approach)

        input("\n[APPROACH] Press Enter to move to pre-impact config...")
        if not self._execute_trajectory(approach_goal, "Approach"):
            return

        input("\n[HIT] Press Enter to execute hit...")
        if not self._execute_trajectory(hit_goal, "Hit"):
            return

        input("\n[RECOIL] Press Enter to recoil to approach config...")
        if not self._execute_trajectory(recoil_goal, "Recoil"):
            return

        self.get_logger().info("Sequence complete.")


# ── Entry point ────────────────────────────────────────────────────────────────

def main(args=None):
    rclpy.init(args=args)
    node = PinkHitNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()