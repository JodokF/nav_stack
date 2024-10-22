---
Erstellt: 2024-07-11
---
##### `/mavros/local_position/pose` = `/mavros/odometry/in` =(?)`/mavros/global_position/local`
 
... given by px4/EKF2 and represents the drones localization (as understand by px4 after the sensor fusion)
as discussed [here](https://discuss.px4.io/t/external-position-with-px4/12205/7), [here (last month, no answers)](https://github.com/mavlink/mavros/issues/1936), and [here (bad answers)](https://discuss.px4.io/t/mavros-question-about-odometry-and-local-position/26982)

##### `/mavros/local_position/velocity_body` 
(not sure)
... given by px4/EKF2 and represents the drones velocity (as understand by px4 after the sensor fusion)

##### `/mavros/odometry/out` & `/mavros/vision_pose/pose` 
see difference [[Setting up mocap & EKF2 mofo for Sim#Two possibilities for the sitl simulation|here]]
Is used by optitrack or the camera (or in the Simulation by gazebo) to send the pose to the EKF to fuse it into it's position estimation

##### `/mavros/setpoint_velocity/cmd_vel_unstamped` & `/mavros/setpoint_position/local`
...we can send velocities or position commands to this topic to the pixhawk4 controller on the drone 
(before we have to go into offboard mode)










