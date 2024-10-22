---
Erstellt: 2024-07-06
tags:
  - TFM/TrackingCam
  - TFM/Errors-Problems
  - TFM/EKF
---
###### [[Tracking Cam TF - proportional error between px4 output pose and Tracking Cam|Previous problem...]]
### Problem: 
EKF does not correspond to the real camera pose
![[scs-2024-07-09-11-22-57.png|200]] ![[scs-2024-07-09-11-22-43.png|300]] ![[px4 output pose does not correspond with Tracking Cam.png|300]]


### Solution: 
~~we changed it [[Tracking Cam TF - proportional error between px4 output pose and Tracking Cam|here]] to `odom` but using`camera_odom_frame` instead this current offset-problem is also gone.~~ -> when `frame_id:` is set to  `"camera_odom_frame"` , the drone thinks it is 25 cm higher as it is, because the `camera_odom_frame` has an offset of [0.15, 0, 0.25] (defined in the `bridge.launch`)

Changing the `static_transformer ` in the `bridge.launch` so that the camera is at [0, 0, 0.25] (no offset in X ❗) and the `base_link` is at [-0.15, 0, 0] 

like this it works, I'm not 💯 % sure why... :/ 
The full documentation can be seen [[Tracking Cam docu and structure|here]]