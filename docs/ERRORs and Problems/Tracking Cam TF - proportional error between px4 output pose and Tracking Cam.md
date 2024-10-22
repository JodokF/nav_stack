---
Erstellt: 2024-07-06
tags:
  - TFM/TrackingCam
---
somehow pixhawk references to a wrong frame, since it thinks (blue arrow) that it is in an other spot that the real drone -> `camera_pose_frame`
for example: when the `camera_pose_frame` goes up (like the drone in real life) the pose from px4 (blue arrow) goes down...

The blue arrow reads the topic from `/mavros/local_position/pose`

>[!image] Like this:
>![[Tracking Cam px4 output pose does not correspond.png|500]]

I have no clue, why, because the `px4_realsense_bridge_node` is publishing from `/camera/odom/sample_throttled` to this -> `/mavros/odometry/out`, (like it can be seen [[Files accessed when using Optitrack or the Tracking Cam for localization|here...]]) 
But plotting the data from `/mavros/odometry/out` shows that the data is "correct" (when the drone goes up - z increases) 
ok maybe px4 needs that when the drone goes up z is getting smaller like it can be [[Reference Frames and ROS|seen here...]] 
With Optitrack there is some function in place to transform it to `odom_node` i think so, but how did Pablo and Juan did it?


### Solution:
in the `px4_config_cam.yaml` I changed `odom_ned` to `odom` in the following two places:

```yaml
local_position:
  frame_id: "odom" # used to be "odom_ned"
  tf:
    send: false
    frame_id: "odom" # used to be "odom_ned"
    child_frame_id: "camera_t265"
    send_fcu: false
```


And an offset (z position) was added in QGC to get the origin of the vision aid to the pixhawk controller FCU. This is the corresponding parameter in QGC:`EKF2_EV_POS_Z`
[[Backup parameters for Optitrack or RS T265]]

##### Error continues [[Tracking Cam TF - absolut error between px4-EKF2 output pose and Tracking Cam|here...]]

