---
Erstellt: 2024-07-23
---
flying the drone, with voxblox , and mav trajectory generation, and with the ROS PID
(using a new generated, cleaner voxblox map than before)

### Problems:
* Optitrack does not detect the drone, maybe because of big Temperture differences between when optit. was calibrated and now.
* Trajectory is crazy, because of no middle points between the RRT waypoints (and because when generating a new path) the old one is still displayed:
>[!img]- Problem:
>![[scs-2024-07-23-13-06-58.png|800]]
* change from hardcoded trajectory (with velocity constraints) back to the RRT waypoints with no vel. constr.

### 1. Flight with Optitrack

>[!img]- RViz
>![[scs-2024-07-23-13-41-02.png|800]]
>![[scs-2024-07-23-13-41-20.png|800]]

>[!info] Video:
>`/home/cconradi/Documents/TFM/Experiments/px4_real_drone/vxblx_follow_traj_gen/new_map`
>[1_Flight_RViz.mp4](file:///home/cconradi/Documents/TFM/Experiments/px4_real_drone/vxblx_follow_traj_gen/new_map/1_Flight_RViz.mp4)
>add GoPro Video

### 2. Flight with Optitrack
>[!img]- RViz
>![[scs-2024-07-23-18-15-59.png|800]]
>![[scs-2024-07-23-18-15-41.png|800]]

##### Recorded mav Trajectory
So that it would be possible to `rosbag play` it and fly the same trajectory with the camera for localization...
![[trajectory_bag_2024-07-23-18-14-17.bag]]

>[!info] Video:
>`/home/cconradi/Documents/TFM/Experiments/px4_real_drone/vxblx_follow_traj_gen/new_map`
>[2_Flight_RViz.mp4](file:///home/cconradi/Documents/TFM/Experiments/px4_real_drone/vxblx_follow_traj_gen/new_map/2_Flight_RViz.mp4)
>add GoPro and Optitrack Video








