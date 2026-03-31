import os
from glob import glob

from setuptools import find_packages, setup

package_name = 'my_package'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/my_package']),
        ('share/my_package', ['package.xml']),
        ('share/my_package/launch', glob('launch/*.py')),
        ('share/my_package/urdf', glob('urdf/*.xacro')),
        ('share/my_package/config', glob('config/*.yaml')),
        ('share/my_package/config', glob('config/*.rviz')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='theo',
    maintainer_email='theo@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'diff_drive_controller = my_package.sim:main',
            'arm_controller = my_package.arm:main',
            'arm_ik_controller = my_package.arm_ik_controller:main',
        ],
    },
)
