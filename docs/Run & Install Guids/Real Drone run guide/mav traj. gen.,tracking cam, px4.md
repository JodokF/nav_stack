### mav trajectory generation with real px4 and with out voxblox:

##### see [[Files accessed when using Optitrack or the Tracking Cam for localization#Tracking Cam|here]] which files are accessed when opening `open_ports_cam.sh`

-> check that the [[Backup parameters for Optitrack or RS T265|right parameters]] are set in QGC

~~turn off cineMPC tag in optitrack~~ actually I think if we don't start the optitrack-node it doesnt matter
#### for the drone:
```jade
ssh -X jetson@192.168.0.101

. open_ports_cam.sh
```

#### on the ground computer
```jade
rviz -d /home/cconradi/Documents/catkin_ws/src/nav_stack_cc/traj_generation/cnfg/t265_cam_for_localization.rviz

roslaunch nav_stack drone_connection.launch tracking_camera:=true cntrl:=true
roslaunch nav_stack pid_cntrl.launch
rosrun nav_stack traj_generation
```


