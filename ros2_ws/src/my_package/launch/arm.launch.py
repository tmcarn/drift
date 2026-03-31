# from launch import LaunchDescription
# from launch_ros.actions import Node
# from launch_ros.parameter_descriptions import ParameterValue
# from launch.substitutions import Command
# from launch.actions import ExecuteProcess, TimerAction
# from ament_index_python.packages import get_package_share_directory

# import os

# def generate_launch_description():
#     launch_description = []

#     pkg  = get_package_share_directory('my_package')
#     urdf_path = os.path.join(pkg, 'urdf', 'arm.urdf.xacro')
#     robot_description = Command(['xacro ', urdf_path])

#     srdf_path = os.path.join(pkg, 'config', 'moveit', 'arm.srdf')
#     with open(srdf_path, 'r') as f:
#         robot_description_semantic = f.read()

#     print(robot_description_semantic)

#     kinematics = os.path.join(pkg, 'config', 'moveit', 'kinematics.yaml')
#     planning = os.path.join(pkg, 'config', 'moveit', 'planning.yaml')
#     moveit_controllers = os.path.join(pkg, 'config', 'moveit', 'moveit_controllers.yaml')


#     state_publisher = Node(
#         package="robot_state_publisher",
#         executable="robot_state_publisher",
#         parameters=[{"robot_description": robot_description}]
#     )
#     launch_description.append(state_publisher)

#     controller_manager = Node(
#         package="controller_manager",
#         executable="ros2_control_node",
#         parameters=[os.path.join(pkg, 'config', 'arm_controllers.yaml')],
#         output="screen"
#     )
#     launch_description.append(controller_manager)

#     spawn_joint_state_broadcaster = Node(
#         package="controller_manager",
#         executable="spawner",
#         arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
#         output="screen"
#     )
#     launch_description.append(spawn_joint_state_broadcaster)

#     spawn_joint_trajectory_controller = Node(
#         package="controller_manager",
#         executable="spawner",
#         arguments=["joint_trajectory_controller", "--controller-manager", "/controller_manager"],
#         output="screen"
#     )
#     launch_description.append(spawn_joint_trajectory_controller)

#     spawn_gripper_controller = Node(
#         package="controller_manager",
#         executable="spawner",
#         arguments=["gripper_controller", "--controller-manager", "/controller_manager"],
#         output="screen"
#     )
#     launch_description.append(spawn_gripper_controller)

#     move_group = Node(
#         package="moveit_ros_move_group",
#         executable="move_group",
#         output="screen",
#         parameters=[
#             {"robot_description": robot_description},
#             {"robot_description_semantic": robot_description_semantic},
#             kinematics,
#             planning,
#             moveit_controllers,
#             {"use_sim_time": False},
#         ],
#     )
#     launch_description.append(move_group)

#     rviz = Node(
#         package="rviz2",
#         executable="rviz2",
#         arguments=["-d", os.path.join(pkg, "config", "arm.rviz")], # Save from Config
#         output="screen"
#     )
#     launch_description.append(rviz)

#     return LaunchDescription(launch_description)


from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command
from launch.actions import TimerAction
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    pkg = get_package_share_directory('my_package')
    robot_description = Command(['xacro ', os.path.join(pkg, 'urdf', 'arm.urdf.xacro')])

    state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description}],
    )

    controller_manager = Node(
        package='controller_manager',
        executable='ros2_control_node',
        parameters=[os.path.join(pkg, 'config', 'arm_controllers.yaml')],
        output='screen',
    )

    spawn_jsb = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['joint_state_broadcaster'],
    )

    spawn_jtc = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['joint_trajectory_controller'],
    )

    spawn_gripper = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['gripper_controller'],
    )

    rviz = Node(
        package="rviz2",
        executable="rviz2",
        arguments=["-d", os.path.join(pkg, "config", "arm.rviz")], # Save from Config
        output="screen"
    )

    delayed = TimerAction(
        period=3.0,
        actions=[spawn_jsb, spawn_jtc, spawn_gripper],
    )

    return LaunchDescription([
        state_publisher,
        controller_manager,
        delayed,
        rviz,
    ])
