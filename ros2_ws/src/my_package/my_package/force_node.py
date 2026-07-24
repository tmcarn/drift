import numpy as np
import copy

from enum import Enum, auto

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import PoseStamped
from lbr_fri_idl.msg import LBRWrenchCommand
from sensor_msgs.msg import JointState

# For RVIZ
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from builtin_interfaces.msg import Duration

# To Trigger Execution
from std_srvs.srv import Trigger

# For TF Tree
from tf2_ros import Buffer, TransformListener
import tf2_geometry_msgs  

# For URDF Subsriber
from rclpy.qos import QoSProfile, DurabilityPolicy

# For IK
import pinocchio as pin
import pink
from pink.tasks import FrameTask, PostureTask


EE_FRAME    = "lbr_link_ee"
BASE_FRAME = "lbr_link_0"  
JOINT_NAMES = ["lbr_A1", "lbr_A2", "lbr_A3", "lbr_A4", "lbr_A5", "lbr_A6", "lbr_A7"]

WORLD_FRAME = "world"
OBJECT_FRAME = "object"

APPROACH_OFFSET   = 0.1 # m (stops this far before the object)
FORCE = 5 # Newtons

JOINT_VELOCITY_LIMITS_DEG = np.array([98, 98, 100, 130, 140, 180, 180])  # A1–A7, deg/s
JOINT_VELOCITY_LIMITS_RAD = np.deg2rad(JOINT_VELOCITY_LIMITS_DEG)
SAFETY_MARGIN = 0.3 


class Phase(Enum):
    IDLE = auto()
    APPROACH = auto()
    CONTACT = auto()
    DONE = auto()

class IKSolver:
    def __init__(self, urdf: str, ee_frame: str, q_ref: np.ndarray, dt: float = 0.01, n_steps: int = 500):
        self.model = pin.buildModelFromXML(urdf)
        self.data = self.model.createData()
        self.dt = dt
        self.n_steps = n_steps
        self.ee_frame = ee_frame
        self.q_ref = q_ref  # posture target, kept separate from the warm-start config
        self.configuration = pink.Configuration(self.model, self.data, q_ref)

    def solve(self, target_pose: pin.SE3, q_init: np.ndarray) -> np.ndarray:
        ee_task = FrameTask(self.ee_frame, position_cost=1.0, orientation_cost=1.0)
        ee_task.set_target(target_pose)

        posture_task = PostureTask(cost=1e-3)
        posture_task.set_target(q_init)  # bias toward starting config, matches hit_node's behavior

        q = q_init.copy()

        for _ in range(self.n_steps):
            self.configuration = pink.Configuration(self.model, self.data, q)
            vel = pink.solve_ik(self.configuration, [ee_task, posture_task], self.dt, solver="quadprog")
            q = self.configuration.integrate(vel, self.dt)

        return q
    
class ForceNode(Node):
    def __init__(self):
        super().__init__('force_node')
        self.phase = Phase.IDLE
        self.ik_solver = None  # gated on URDF arrival
        self.approach_pose = None
        self.contact_pose = None
        self.contact_start = None
        self.control_dt = 0.001 # must match your actual FRI/state rate

        urdf_qos = QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL)
        self.create_subscription(String, 'lbr/robot_description', self.on_urdf, urdf_qos)
        self.create_subscription(PoseStamped, 'object_pose', self.on_object_pose, 10)
        self.create_subscription(JointState, 'lbr/joint_states', self.on_state, 10)
        # self.cmd_pub = self.create_publisher(LBRWrenchCommand, 'command/lbr_wrench_command', 10)

        # For RVIZ
        self.cmd_pub = self.create_publisher(JointTrajectory, '/lbr/joint_trajectory_controller/joint_trajectory', 10)

        self.create_service(Trigger, 'start_push', self.on_start_push)

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        self.max_joint_step = SAFETY_MARGIN * JOINT_VELOCITY_LIMITS_RAD * self.control_dt  # array, shape (7,)        

    def on_object_pose(self, msg: PoseStamped):
        if self.ik_solver is None:
            self.get_logger().warn("Object pose received before URDF ready, ignoring")
            return

        # Converts Object Pose from World frame to Base frame
        try:
            pose_in_base = self.tf_buffer.transform(
                msg, BASE_FRAME, timeout=rclpy.duration.Duration(seconds=0.1)
            )
        except Exception as e:
            self.get_logger().warn(f"TF transform failed: {e}")
            return
        
        self.approach_pose = self.approach_offset(pose_in_base, standoff=0.10)
        self.contact_pose = pose_in_base
    
    def on_urdf(self, msg: String):
        # q_ref choice still open — hardcoded posture vs "current state at APPROACH start"
        q_ref = np.zeros(7)  # placeholder
        self.ik_solver = IKSolver(msg.data, ee_frame="lbr_link_ee", q_ref=q_ref, dt=self.control_dt)
        self.get_logger().info("IK solver ready")

    def on_start_push(self, request, response):
        if self.ik_solver is None:
            response.success = False
            response.message = "IK solver not ready (no URDF received yet)"
            return response
        if self.approach_pose is None:
            response.success = False
            response.message = "No object pose received yet"
            return response
        if self.phase != Phase.IDLE:
            response.success = False
            response.message = f"Already running (phase={self.phase.name})"
            return response

        self.phase = Phase.APPROACH
        response.success = True
        response.message = "Starting approach"
        return response

    def ik(self, pose_stamped) -> np.ndarray:
        target_pos = pose_stamped.pose.position
        target = pin.SE3(pin.utils.rotate("y", np.pi), target_pos)
        return self.ik_solver.solve(target, self.q_curr)

    def approach_offset(self, pose: PoseStamped, standoff: float = 0.10):
        R = self.quat_to_rot(pose.pose.orientation)
        x_axis = R[:, 0]
        offset_pose = copy.deepcopy(pose)
        offset_pose.pose.position.x -= standoff * x_axis[0]
        offset_pose.pose.position.y -= standoff * x_axis[1]
        offset_pose.pose.position.z -= standoff * x_axis[2]
        return offset_pose

    def quat_to_rot(self, q):
        return pin.Quaternion(q.w, q.x, q.y, q.z).toRotationMatrix()

    def pin_se3_from_pose(self, pose):
        quat = pin.Quaternion(pose.orientation.w, pose.orientation.x,
                            pose.orientation.y, pose.orientation.z)
        translation = np.array([pose.position.x, pose.position.y, pose.position.z])

        R_object = quat.matrix()
        R_flip = pin.utils.rotate("y", np.pi)  # 180° about y
        R_target = R_object @ R_flip           # local-frame correction

        return pin.SE3(R_target, translation)
    
    def on_state(self, msg: JointState):
        self.q_curr = np.array(msg.position)
        if self.ik_solver is None or self.phase == Phase.IDLE:
            return

        q_measured = np.array(msg.position)
        # self.ik_solver.configuration.q = q_measured   # ← remove, see note below

        if self.phase == Phase.APPROACH:
            target = self.pin_se3_from_pose(self.approach_pose.pose)
            q = self.ik_solver.solve(target, q_measured)
            q_cmd = self.rate_limit(q, q_measured)
            self.publish_cmd(q_cmd, wrench=[0.0] * 6)
            if self.pose_error(msg, self.approach_pose) < 0.005:
                self.phase = Phase.CONTACT
                self.contact_start = self.get_clock().now()

        elif self.phase == Phase.CONTACT:
            elapsed = (self.get_clock().now() - self.contact_start).nanoseconds * 1e-9
            force = min(FORCE, FORCE * elapsed / 0.3)
            target = self.pin_se3_from_pose(self.contact_pose.pose)
            q = self.ik_solver.solve(target, q_measured)
            q_cmd = self.rate_limit(q, q_measured)
            self.publish_cmd(q_cmd, wrench=[force, 0, 0, 0, 0, 0])
            if elapsed > 1.0:
                self.phase = Phase.DONE

        elif self.phase == Phase.DONE:
            self.publish_cmd(q_measured, wrench=[0.0] * 6)  # was self.ik_solver.configuration.q — stale now
            self.phase = Phase.IDLE

    def pose_error(self, state_msg: JointState, target_pose: PoseStamped) -> float:
        q_measured = np.array(state_msg.position)  # confirm exact field name
        pin.forwardKinematics(self.ik_solver.model, self.ik_solver.data, q_measured)
        pin.updateFramePlacement(self.ik_solver.model, self.ik_solver.data, 
                                self.ik_solver.model.getFrameId("lbr_link_ee"))
        current = self.ik_solver.data.oMf[self.ik_solver.model.getFrameId("lbr_link_ee")]
        target = self.pin_se3_from_pose(target_pose.pose)
    
        err = pin.log6(current.inverse() * target).vector
        return np.linalg.norm(err[:3])  # position-only

    def rate_limit(self, q_target: np.ndarray, q_current: np.ndarray) -> np.ndarray:
        delta = q_target - q_current
        # delta = np.clip(delta, -self.max_joint_step, self.max_joint_step)
        return q_current + delta

    def publish_cmd(self, q: np.ndarray, wrench: list):
        msg = JointTrajectory()
        msg.joint_names = JOINT_NAMES
        point = JointTrajectoryPoint()
        point.positions = q.tolist()
        point.time_from_start = Duration(sec=0, nanosec=int(self.control_dt * 1e9))
        msg.points = [point]
        self.cmd_pub.publish(msg)
    
    # def publish_cmd(self, q: np.ndarray, wrench: list):
    #     msg = LBRWrenchCommand()
    #     msg.joint_position = q.tolist()
    #     msg.wrench = wrench
    #     self.cmd_pub.publish(msg)

# ── Entry point ────────────────────────────────────────────────────────────────

def main(args=None):
    rclpy.init(args=args)
    node = ForceNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()