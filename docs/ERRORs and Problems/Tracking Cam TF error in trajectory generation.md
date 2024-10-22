---
Erstellt: 2024-07-15
tags:
  - TFM/TrackingCam
---
![[Tracking Cam TF  error in trajectory generation.png|500]]

##### Problem:
The trajectory planner (blue) starts further down in z than the drone (yellow)

##### Solution:
-> that's because the trajectory planner reads the position of the camera from /mavros/odometry/out (= `/camera/odom/sample_throttled` see [[Files accessed when using Optitrack or the Tracking Cam for localization#^this-transformation|here]]) 

And this topic has as *"frame_id"* `camera_odom_frame` and as *"child_frame_id"* `camera_pose_frame` 
This means that it calculates the pose as `cameara_odom_frame` would be the origin -> (0, 0, 0) but that's not the case, `camera_odom_frame` has an offset (0.16, 0.0, 0.05) which it gets in the `bridge.launch` from an static_transformer.
~~So we need to make a tf-transformation  to get the `camera_pose_frame`in respect to `odom`.~~
So we need to read the pose of the `base_link` in respect to `odom` ([[Reading Pose from TF Tree]])
bc. the camera has also an offset to the pixhawk4 cntrl -> which is represented by `base_link`

##### Comparison of 
old topic:`camera_odom_frame` -> `camera_pose_frame`  (= blue)
new topic: `odom` -> `camera_pose_frame` (=red) (should actually be `base_link` )
Since there is no deviation in **y** for `odom` and `camera_pose_frame` there is no difference in the graph...
>[!image]- Plot Juggler:
>![[Tracking Cam TF  error in trajectory generation-1.png]]


#### `camera_odom_frame` -> `camera_pose_frame` 
![[scs-2024-07-16-16-40-54.png|500]]

#### `odom` -> `camera_pose_frame` 
![[scs-2024-07-16-16-37-41.png|500]]
#### `odom` -> `base_link`
![[scs-2024-07-16-16-43-14.png|500]]

The error that the Goal is too far down (in reality the drone is to high up) was corrected later by [[Tracking Cam TF - proportional error between px4 output pose and Tracking Cam#Solution|this solution]] and later [[Tracking Cam TF - absolut error between px4-EKF2 output pose and Tracking Cam#Solution|this solution]]