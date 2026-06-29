from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription # TimerAction, ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():

    lbr_share = get_package_share_directory('lbr_bringup')

    mock = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(lbr_share, 'launch', 'mock.launch.py')
        ),
        launch_arguments={'model': 'iiwa7'}.items(),
    )

    rviz = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(lbr_share, 'launch', 'rviz.launch.py')
        ),
        launch_arguments={
            'rviz_cfg_pkg': 'lbr_bringup',
            'rviz_cfg':     'config/kuka.rviz',
        }.items(),
    )

    move_group = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(lbr_share, 'launch', 'move_group.launch.py')
        ),
        launch_arguments={'model': 'iiwa7'}.items(),
    )

    static_tf = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='robot_base_to_lbr_link_0',
        arguments=[
            '--frame-id',       'robot_base',
            '--child-frame-id', 'lbr_link_0',
            '--x',  '0', '--y', '0', '--z', '0.1',
            '--qx', '0', '--qy', '0', '--qz', '0', '--qw', '1',
        ],
    )

    mock_optitrack = Node(
        package='optitrack_ros2',
        executable='mock_optitrack_node',
        name='optitrack_node',
        output='screen',
    )

    # hit_node = ExecuteProcess(
    #     cmd=['/home/theo/roskuka/bin/python3', 
    #         '/home/theo/drift/ros2_ws/src/my_package/my_package/hit_node.py'],
    #     output='screen',
    # )

    return LaunchDescription([
        mock,
        rviz,
        move_group,
        static_tf,
        mock_optitrack,
        # Delay hit node to give controller time to come up
        # TimerAction(period=5.0, actions=[hit_node]),
    ])