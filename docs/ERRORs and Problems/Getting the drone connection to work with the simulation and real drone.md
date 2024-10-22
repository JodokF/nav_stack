---
tags:
---
#### problem:
```C++
pose_sub_sim = nh.subscribe<nav_msgs::Odometry> ("/mavros/odometry/out", 10, &drone_connection::sim_pose_cb, this); 
pose_sub_real = nh.subscribe<geometry_msgs::PoseStamped> ("/optitrack/pose", 10, &drone_connection::real_pose_cb, this);
```

Simulation publishes the drone pose to a `nav_msgs::Odometry`
Real drone (Optitrack) publishes the drone pose to `geometry_msgs::PoseStamped`

#### solution: 
transform the pose from the simulation to a `geometry_msgs::PoseStamped`


-> so the drone_connection.cpp listens to both topics and eaither way, wherever the messages is published to curren pose is used.
