### mav trajectory generation with px4 and with out voxblox & the ROS PID Controller:

```jade
roslaunch nav_stack mavros_posix_sitl.launch

roslaunch nav_stack drone_connection.launch cntrl:=true
	
	--> wait for take_off and start_hight_reached
	
roslaunch nav_stack pid_cntrl.launch
rosrun nav_stack traj_generation
```
