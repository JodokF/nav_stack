---
tags:
  - to-do
---
## Packages

### nav_stack
* holds the source files 
	* `drone_connection`
		* establishes connection to the drone and performs the take off
	* `traj_generation`
		* generates the trajectory
and the corresponding launch files

### voxblox
* containes all the ros packages for
	* voxblox
	* voxblox planning
	* mav_traj_generation

### offb_sim (rename)
to ???

### ~~velodyne_simulation
is nececsarry for something in the gazebo simulation, is called somewhere in the urdf-file of the `spawn_quadrotor_ouster.launch` or the `spawn_quadrotor.launch`~~

### ~~hector_moveit_actions~~ ???
I belive it is only the .action file that is necessary in the simulation to get the hector drone to fly

==to-do==