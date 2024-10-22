---
tags:
---
#### [Basic Docs](https://docs.px4.io/main/en/ros/external_position_estimation.html) for external position estimate
#### [Basic Docs](https://docs.px4.io/main/en/advanced_config/tuning_the_ecl_ekf.html) for the EKF2 

[Scheme](https://docs.px4.io/main/en/simulation/ros_interface.html#launching-gazebo-classic-with-ros-wrappers) of the sitl px4 simulation, ROS and Gazebo with the corresponding ports
## Two possibilities for the sitl simulation:

Publishing the odometry to one of these topics (from the gazebo plugin in the iris.sdf file)

* `/mavros/odometry/out` (= *nav_msgs::Odometry*)
	* `Odometry` has also Velocities.
	* The problem is that the gazebo plugin is publishing these veolocities probably in an other orientation frame.
	* So in the QGroundControl the **`3D Velocities` has to be turned off in the `EKF2_EV_CTRL` Parameter**!!! If not this crazy behaviour comes where the Drone is going completly nuts.
	* When it is turned off it works.

* `/mavros/vision_pose/pose` (= *geometry_msgs/PoseStamped*)
	* `PoseStamped` has no velocities so thats no problem
	* Problem is that the Gazebo Plugin is publishing as `nav_msgs::Odometry` 
	* So we made the `vision_topic_handler.cpp` to taransforme the message from `Odemetry` to `PoseStamped` (and leave the velocities out of the message)
	* So it doesn't matter if `3D Velocities` is turned on or not

### [[important EKF2 Parameters with explanation]]


### px4 simulation Angular Velocity clusterfuck
* Drone is "stable" in x and y but is rising in z direction. Why? -> partially because of the wrong calibrated IMU (?) calibration in the simulation not really possible because you cant move the drone by hand
* Other explantion for drift when sending only velocities [see here](https://discuss.px4.io/t/position-hold-or-zero-velocity/3009/4) and [here (the solution at the end](https://github.com/PX4/PX4-Autopilot/issues/3642#issuecomment-180409042) with sending at higher hz does not work)

### [[Reference Frames and ROS]]




