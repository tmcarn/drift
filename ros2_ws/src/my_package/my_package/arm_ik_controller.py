import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint
from geometry_msgs.msg import PointStamped
from builtin_interfaces.msg import Duration
import pinocchio as pin
import numpy as np
import subprocess


class ArmIKController(Node):
    def __init__(self):
        super().__init__('arm_ik_controller')

        # Load URDF into Pinocchio
        urdf_path = '/home/theo/drift/ros2_ws/install/my_package/share/my_package/urdf/arm.urdf.xacro'
        urdf_string = subprocess.check_output(['xacro', urdf_path]).decode()
        self.model = pin.buildModelFromXML(urdf_string)
        self.data = self.model.createData()
        self.ee_frame_id = self.model.getFrameId('tool_tip')

        for i, name in enumerate(self.model.names):
            self.get_logger().info(f'Joint {i}: {name}')

        self.get_logger().info(f'EE frame id: {self.ee_frame_id}')
        self.get_logger().info(f'EE pos at neutral: {self.data.oMf[self.ee_frame_id].translation}')
        self.get_logger().info(f'Model nq: {self.model.nq}')

        self.q_current = pin.neutral(self.model)

        # Arm action client
        self.arm_client = ActionClient(
            self,
            FollowJointTrajectory,
            '/joint_trajectory_controller/follow_joint_trajectory'
        )
        self.get_logger().info('Waiting for action server...')
        self.arm_client.wait_for_server(timeout_sec=10.0)
        self.get_logger().info('Connected to arm controller')

        # Subscribe to task space commands
        self.create_subscription(
            PointStamped,
            '/target_position',
            self.target_callback,
            10
        )
        self.get_logger().info('Listening for task space commands on /target_position')

    def target_callback(self, msg):
        target = np.array([msg.point.x, msg.point.y, msg.point.z])
        self.get_logger().info(f'Target: {target}')

        q_sol = self.solve_ik(target)
        if q_sol is None:
            return

        arm_joints = q_sol[:3].tolist()
        self.get_logger().info(f'Joint solution: {arm_joints}')

        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = [
            'shoulder_joint', 'elbow_joint', 'wrist_joint'
        ]
        point = JointTrajectoryPoint()
        point.positions = arm_joints
        point.time_from_start = Duration(sec=2)
        goal.trajectory.points = [point]

        future = self.arm_client.send_goal_async(goal)
        future.add_done_callback(self.goal_response_callback)

        self.q_current = q_sol

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('Goal rejected')
            return
        self.get_logger().info('Goal accepted')

    def solve_ik(self, target_pos):
        q = self.q_current.copy()
        eps = 1e-4
        dt = 0.1
        arm_idx = [0, 1, 2]  # shoulder, elbow, wrist indices in q

        for i in range(1000):
            pin.forwardKinematics(self.model, self.data, q)
            pin.updateFramePlacements(self.model, self.data)

            oMcurrent = self.data.oMf[self.ee_frame_id]
            err = target_pos - oMcurrent.translation

            if i % 100 == 0:
                self.get_logger().info(f'Iter {i}: err={np.linalg.norm(err):.6f}, ee={oMcurrent.translation}, q={q[:3]}')


            if np.linalg.norm(err) < eps:
                self.get_logger().info(f'IK converged in {i} iterations')
                return q

            J_full = pin.computeFrameJacobian(
                self.model, self.data, q,
                self.ee_frame_id,
                pin.ReferenceFrame.LOCAL_WORLD_ALIGNED
            )
            # Only use the 3 arm joint columns, ignore gripper columns
            J_arm = J_full[:3, arm_idx]
            dq_arm = np.linalg.pinv(J_arm) @ err

            # Only update arm joints, keep gripper at 0
            q[arm_idx] += dq_arm * dt
            q[arm_idx] = np.clip(
                q[arm_idx],
                self.model.lowerPositionLimit[arm_idx],
                self.model.upperPositionLimit[arm_idx]
            )

        self.get_logger().warn('IK did not converge')
        return None


def main():
    rclpy.init()
    node = ArmIKController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()