### mav traj. gen. px4 w/ voxblox

```jade
export ROS_MASTER_URI=http://192.168.0.29:11311
roslaunch voxblox_ros arena_test.launch
roslaunch voxblox_rrt_planner rrt_saved_map.launch

rosservice call /voxblox_node/load_map "file_path: '/home/cconradi/Documents/catkin_ws/include/vxblx_maps/arena_1obs_upgraded.voxblox'" 
rosservice call /voxblox_node/generate_mesh "{}" 
	--> Wait for mesh to come up in RViz

roslaunch nav_stack mavros_posix_sitl.launch
rosrun nav_stack drone_connection 
	--> Wait for the drone to launch
rosrun nav_stack traj_generation
```
