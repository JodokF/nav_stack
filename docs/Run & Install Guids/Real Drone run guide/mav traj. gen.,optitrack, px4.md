### mav trajectory generation with real px4 and with out voxblox:

###### see [[Files accessed when using Optitrack or the Tracking Cam for localization#Optitrack|here]] which files are accessed when opening `open_ports_opti.sh`

-> check that the [[Backup parameters for Optitrack or RS T265|right parameters]] are set in QGC
#### for the drone:
```jade
ssh -X jetson@192.168.0.101

. open_ports_opti.sh
```

#### on the ground computer
```jade
rviz -d /home/cconradi/Documents/catkin_ws/src/nav_stack_cc/nav_stack/cnfg/cnfg_real_drone_flying_ocho.rviz

roslaunch nav_stack drone_connection.launch cntrl:=true
roslaunch nav_stack pid_cntrl.launch

rosrun nav_stack traj_generation
```


