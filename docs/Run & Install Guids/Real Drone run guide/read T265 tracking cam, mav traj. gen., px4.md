### launching the tracking cam with mav trajectory generation with real px4, with out voxblox:

### on the drone:
```jade
ssh -X jetson@192.168.0.101

. open_ports_opti.sh

-> jump to 1.

-> 2. to launch the tracking camera, and bring it to the same origin as the cine_mpc drone:
roslaunch px4_realsense_bridge read_t265_w_cinempc.launch x:=$(rosparam get /frame_offset/x) y:=$(rosparam get /frame_offset/y) z:=$(rosparam get /frame_offset/z) yaw:=$(rosparam get /frame_offset/yaw) pitch:=$(rosparam get /frame_offset/pitch) roll:=$(rosparam get /frame_offset/roll)

-> wait for the cam to be launched, then jump to 3.

```


### on the ground computer
```jade

-> 1., to calc the diffrences in the tf tree between the origin (odom) and the cam:
rosrun tracking_cam move_cam_to_cinempc
	(warning about: "odom" passed to lookupTransform argument target_frame does not exist ??? idk)

-> wait for transformation is set to the Parameters then jump to 2. 
roslaunch tracking_cam rviz_and_paths.launch

-> 3. either go free solo with the RC or go on with the rest:

roslaunch nav_stack drone_connection.launch cntrl:=true 
roslaunch nav_stack pid_cntrl.launch
rosrun nav_stack traj_generation
```


