from setuptools import setup

package_name = 'ros_talk_with_dds_py'
utils = "ros_talk_with_dds_py/utils"

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name, utils],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='root',
    maintainer_email='he.xu@intel.com',
    description='For testing msg_lib dds port talking with ROS2 Python node',
    license='BSD-3-Clause',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'ros_pub = ros_talk_with_dds_py.publisher:main',
            'ros_sub = ros_talk_with_dds_py.subscriber:main',
        ],
    },
)