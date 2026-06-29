# iiwa7 Hitting Motion

A ROS 2 system that drives a KUKA iiwa7 through a three-phase hitting motion using Pink IK and OptiTrack pose data.

## Overview

The system reads object and robot poses from OptiTrack via TF, computes a pre-impact configuration using inverse kinematics, then executes three phases:

- **Approach** — moves from current config to a pre-impact position offset from the object
- **Hit** — drives the end-effector through the object at a constant Cartesian velocity using Jacobian control
- **Recoil** — returns to the pre-impact config

Each phase is confirmed by the user before execution.

---

## Packages

| Package | Description |
|---|---|
| `optitrack_ros2` | Mock OptiTrack node — publishes rigid body poses to `/tf_static` |
| `my_package` | Hit node — IK solving, trajectory building, execution |
| `lbr_bringup` | KUKA iiwa7 simulation and hardware bringup (lbr-stack) |

---

## Dependencies

**ROS 2 Jazzy**

**Python (install in your virtual environment):**
```bash
pip install pin pink quadprog
```

**lbr-stack** — build and source separately:
```bash
source ~/drift/ros2_ws/src/lbr-stack/install/setup.bash
```

---

## TF Tree

```
world
├── table
├── object
└── robot_base
    └── lbr_link_0          ← static offset (0, 0, 0.1)
        └── lbr_link_1
            └── ... → lbr_link_ee
```

---

## Configuration

Edit poses in `optitrack_ros2/optitrack_ros2/mock_optitrack_node.py`:

```python
self.poses = {
    'table':      [x, y, z, qx, qy, qz, qw],
    'object':     [x, y, z, qx, qy, qz, qw],
    'robot_base': [x, y, z, qx, qy, qz, qw],
}
```

Edit motion parameters at the top of `my_package/my_package/hit_node.py`:

```python
APPROACH_OFFSET   = 0.1    # m   — distance from object to pre-impact position
HIT_VELOCITY      = 0.5    # m/s — Cartesian speed during hit
HIT_DISTANCE      = 0.15   # m   — total hit travel distance
DT                = 0.001  # s   — trajectory timestep
APPROACH_DURATION = 5.0    # s   — time to complete approach
RECOIL_DURATION   = 2.0    # s   — time to complete recoil
```

---

## Running

**1. Build:**
```bash
cd ~/drift/ros2_ws
source src/lbr-stack/install/setup.bash
colcon build --packages-select optitrack_ros2 my_package
source install/setup.bash
```

**2. Launch the system:**
```bash
ros2 launch my_package mock.launch.py
```

This starts the simulator, RViz, MoveIt, the static transform publisher, and the mock OptiTrack node.

**3. Run the hit node in a separate terminal:**
```bash
source ~/roskuka/bin/activate
python3 ~/drift/ros2_ws/src/my_package/my_package/hit_node.py
```

Follow the prompts to execute each phase.

---

## TODO: Switching to Real Hardware

1. Enable VRPN streaming in OptiTrack Motive — Edit → Settings → Streaming
2. Replace `mock_optitrack_node` with `optitrack_node` in the launch file
3. Change the lbr bringup launch to hardware mode:
```python
launch_arguments={'model': 'iiwa7', 'mode': 'hardware'}.items()
```
4. Deploy the FRI application to the robot cabinet via KUKA Sunrise Workbench