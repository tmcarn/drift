from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command
from launch.actions import ExecuteProcess

from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    launch_description = []

    pkg = get_package_share_directory('my_package')

    urdf_path = os.path.join(pkg, 'urdf', 'diff_drive.urdf.xacro')

    print(f"Package share directory: {pkg}")
    robot_description = Command(['xacro ', urdf_path])

    print(f"Robot description: {robot_description}")

    state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": robot_description}]
    )
    launch_description.append(state_publisher)

    controller_manager = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[{"robot_description": robot_description},
                    os.path.join(pkg, 'config', 'controllers.yaml')],
        output="screen"
    )
    launch_description.append(controller_manager)

    spawn_joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
        output="screen"
    )
    launch_description.append(spawn_joint_state_broadcaster)

    spawn_diff_drive_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["diff_drive_controller", "--controller-manager", "/controller_manager"],
        output="screen"
    )
    launch_description.append(spawn_diff_drive_controller)

    rviz = Node(
        package="rviz2",
        executable="rviz2",
        arguments=["-d", os.path.join(pkg, "config", "rviz.rviz")], # Save from Config
        output="screen"
    )
    launch_description.append(rviz)

    teleop = ExecuteProcess(
        cmd=["ros2", "run", "teleop_twist_keyboard", "teleop_twist_keyboard",
            "--ros-args", "-r", "/cmd_vel:=/diff_drive_controller/cmd_vel", "-p","stamped:=true"],
        prefix="xterm -e",
        output="screen"
    )
    launch_description.append(teleop)

    # TODO: Add Gazebo launch here

    


    return LaunchDescription(launch_description)



