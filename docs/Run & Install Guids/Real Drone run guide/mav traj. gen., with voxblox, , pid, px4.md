# mav traj. gen. px4 with voxblox

with optitrack, if you want to use the camera? check [[mav traj. gen.,tracking cam, px4|this.]]

#### on the drone:
```jade
ssh -X jetson@192.168.0.101
. open_ports_opti.sh
```

#### on the ground computer
```jade
roslaunch nav_stack vxblx_start.launch
roslaunch voxblox_rrt_planner rrt_saved_map.launch
rosservice call /voxblox_node/load_map "file_path: '/home/cconradi/Documents/catkin_ws/include/vxblx_maps/arena_torre.voxblox'" 
rosservice call /voxblox_node/generate_mesh "{}" 
	--> Wait for mesh to come up in RViz
roslaunch nav_stack drone_connection.launch voxblox:=true cntrl:=true
roslaunch nav_stack pid_cntrl.launch
rosrun nav_stack traj_generation

```


