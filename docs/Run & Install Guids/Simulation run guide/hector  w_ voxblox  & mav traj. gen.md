### mav trajectory generation with hector and voxblox  

```jade
roslaunch voxblox_ros arena_test.launch
roslaunch voxblox_rrt_planner rrt_saved_map.launch
rosrun rviz rviz --display-config=/home/cconradi/Documents/catkin_ws/src/nav_stack_cc/nav_stack/cnfg/cnfg.rviz

> Arena Map:
rosservice call /voxblox_node/load_map "file_path: '/home/cconradi/Documents/catkin_ws/include/vxblx_maps/arena_1obs_upgraded.voxblox'" 
> Machinehall:
rosservice call /voxblox_node/load_map "file_path: '/home/cconradi/Documents/catkin_ws/include/vxblx_maps/rs_esdf_0.10.voxblox'" 

rosservice call /voxblox_node/generate_mesh "{}" 
--> Wait for mesh to come up in RViz
roslaunch nav_stack sim_enviroment.launch
roslaunch nav_stack sim_poly_traj_plan.launch
```