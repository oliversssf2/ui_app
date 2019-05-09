#!/bin/bash

#AUTHOR: ME
#SCRIPT:

source /home/min/catkin_ws/devel/setup.bash
export ROS_PACKAGE_PATH=/home/min/catkin_ws/src/rplidar_ros:$ROS_PACKAGE_PATH
roslaunch rplidar_ros view_rplidar.launch

exit
