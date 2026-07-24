import rclpy
from rclpy.node import Node
from tf2_ros import TransformBroadcaster, StaticTransformBroadcaster
from geometry_msgs.msg import TransformStamped, PoseStamped


class MockOptiTrackNode(Node):
    def __init__(self):
        super().__init__('optitrack_node')
        self.parent_frame = "world"

        self.static_poses = {
            'table':      [0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0],
            'robot_base': [-0.2, 0.5, 0.8, 0.0, 0.0, 0.0, 1.0],
        }
        self.dynamic_poses = {
            'object': [0.5, 0.5, 1.0, 0.0, 0.0, 0.2588, 0.9659],
        }

        self._static_broadcaster = StaticTransformBroadcaster(self)
        self._dynamic_broadcaster = TransformBroadcaster(self)
        self._pose_pubs = {
            name: self.create_publisher(PoseStamped, f'{name}_pose', 10)
            for name in self.dynamic_poses
        }

        self._publish_static()
        self.create_timer(0.02, self._publish_dynamic)  # both TF + topic, same tick

    def _make_transform(self, name, pose):
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = self.parent_frame
        t.child_frame_id = name
        t.transform.translation.x, t.transform.translation.y, t.transform.translation.z = pose[0:3]
        t.transform.rotation.x, t.transform.rotation.y, t.transform.rotation.z, t.transform.rotation.w = pose[3:7]
        return t

    def _make_pose(self, pose):
        p = PoseStamped()
        p.header.stamp = self.get_clock().now().to_msg()
        p.header.frame_id = self.parent_frame
        p.pose.position.x, p.pose.position.y, p.pose.position.z = pose[0:3]
        p.pose.orientation.x, p.pose.orientation.y, p.pose.orientation.z, p.pose.orientation.w = pose[3:7]
        return p

    def _publish_static(self):
        transforms = [self._make_transform(n, p) for n, p in self.static_poses.items()]
        self._static_broadcaster.sendTransform(transforms)

    def _publish_dynamic(self):
        transforms, now = [], self.get_clock().now().to_msg()
        for name, pose in self.dynamic_poses.items():
            transforms.append(self._make_transform(name, pose))
            self._pose_pubs[name].publish(self._make_pose(pose))
        self._dynamic_broadcaster.sendTransform(transforms)


def main(args=None):
    rclpy.init(args=args)
    node = MockOptiTrackNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()