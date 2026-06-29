import rclpy
from rclpy.node import Node
from tf2_ros import StaticTransformBroadcaster
from geometry_msgs.msg import TransformStamped, PoseStamped

class MockOptiTrackNode(Node):
    def __init__(self):
        super().__init__('optitrack_node')

        self.parent_frame = "world"
        self.poses = {
            'table':      [0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0],
            'object': [0.5, 0.5, 1.0, 0.0, 0.0, 0.2588, 0.9659],
            'robot_base': [-0.2, 0.5, 0.8, 0.0, 0.0, 0.0, 1.0],
        }

        self._tf_broadcaster = StaticTransformBroadcaster(self)

        self._publish_all()

    def _publish_all(self):
        transforms = []
        for name, pose in self.poses.items():
            t = TransformStamped()
            t.header.stamp    = self.get_clock().now().to_msg()
            t.header.frame_id = self.parent_frame
            t.child_frame_id  = name
            t.transform.translation.x = pose[0]
            t.transform.translation.y = pose[1]
            t.transform.translation.z = pose[2]
            t.transform.rotation.x = pose[3]
            t.transform.rotation.y = pose[4]
            t.transform.rotation.z = pose[5]
            t.transform.rotation.w = pose[6]
            transforms.append(t)
        self._tf_broadcaster.sendTransform(transforms)

def main(args=None):
    rclpy.init(args=args)
    node = MockOptiTrackNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

