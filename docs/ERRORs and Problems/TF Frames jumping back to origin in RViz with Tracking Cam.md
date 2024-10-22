---
Erstellt: 2024-07-06
tags:
  - TFM/TrackingCam
  - TFM/RQT_Graphs
---
### Video of Problem:
![[2024-07-06 15-33-03.mp4|500]]


### Problem & Solution: 

##### Problem
In RViz the frame jumps back to the origin.
I think the frames are published two times, one that stays in the origin, one that goes to the real position of the drone
![[problem_tree.svg|400]]
##### Solution
Yes, it appears that in the `bridge.launch` file in the `px4_realsense_bridge` package the tf frames where transformed/published. but actually they are also published in the `/realsense2_camera_manager` (idk where this is), so after deleting the transformer from the bridge.launch it stops jumping

![[frames_right_cam.svg|400]]
##### Problem that still remains [[Tracking Cam TF - proportional error between px4 output pose and Tracking Cam|here...]]


