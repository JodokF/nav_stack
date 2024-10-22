---
Erstellt: 2024-07-10
tags:
  - TFM/TrackingCam
  - TFM/RQT_Graphs
  - TFM/tf
---
Ok setting up the tracking cam was a ==**fuuuucking hustle**==. 

Because of these problems: [[TF Frames jumping back to origin in RViz with Tracking Cam|jumping tf]], [[Tracking Cam TF - proportional error between px4 output pose and Tracking Cam|proportional error]] and [[Tracking Cam TF - absolut error between px4-EKF2 output pose and Tracking Cam|absolut error]] (and also [[Tracking Cam TF error in trajectory generation|this deviation problem]] for the trajectory generation)
Since they are connected together they are difficult to tackle, here is the current setup :

>[!image]- RQT Graph:
![[frames_tracking_cam.svg|500]]

#### Important Files:`px4_config_cam.yaml`, `bridge.launch` and QGC Params
I also touched `rs_t265.launch` and `nodelet.launch.xml` in the process (because of this [suggestions](https://github.com/IntelRealSense/realsense-ros/issues/749#issuecomment-526096242) where he also says that it doesn't work), but in the end I leave them as they are (I think the original files are coming from the realsense docs, [here](https://dev.intelrealsense.com/docs/depth-and-tracking-cameras-alignment) or [here](https://dev.intelrealsense.com/docs/intel-realsensetm-visual-slam-and-the-t265-tracking-camera)...)

See the full process of the files accessed on the drone [[Files accessed when using Optitrack or the Tracking Cam for localization#Tracking Cam|here...]]

Important parts of the files:

##### QGC - Params:
![[Tracking Cam structure.png]]


###### `bridge.launch`:
```xml
	<node pkg="tf" type="static_transform_publisher" name="static_tf_pub_1"
	args="0 0 0 0 0 0 map odom 1000"/> 

	<node pkg="tf" type="static_transform_publisher" name="static_tf_pub_2"
	args="0 0 0.205 0 0 0 odom camera_odom_frame 1000"/> 

	<node pkg="tf" type="static_transform_publisher" name="static_tf_pub_4"
        args="-0.15 0 0.05 0 0 0 camera_pose_frame base_link 1000"/> 
```
###### `px4_config_cam.yaml`
```yaml
# global_position
global_position:
  frame_id: "map"             # origin frame
  child_frame_id: "base_link" # body-fixed frame
  tf:
    send: false               
    frame_id: "map"  # TF frame_id
    global_frame_id: "earth"  # TF earth frame_id
    child_frame_id: "base_link" # TF child_frame_id

# local_position
local_position:
  frame_id: "odom" 
  tf:
    send: false
    frame_id: "odom"    # if "send = false" it doesn't matter what's the (child_)frame_id
    child_frame_id: "base_link"
    send_fcu: false 
```

