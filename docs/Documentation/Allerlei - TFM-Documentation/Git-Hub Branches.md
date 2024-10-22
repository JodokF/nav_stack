
## main
✅ working (checked 2024-07-18)
- merged from ros_pid
* run it like [[px4 with ROS PID Cntrl with out voxblox & with mav traj. ge|this for the sim]] , or [[mav traj. gen.,optitrack, px4|this for the real drone]] 
* works also with voxblox

### main_square
exactly the same as `main` but instead of hard-coded loop a hard-coded square is flown

## voxblox
✅ working? (checked ???)
- run it like [[px4 with voxblox & w_ mav traj. gen|this]]
- mav trajectory generation
- px4 autopilot simulated in gazebo
- using the voxblox map and path planner
- no controller (?)
- no hardcoded routes

## flying_ocho 
✅ working (*checked 22.05.24*)
- run it like [[px4 w_o voxblox & w_ mav traj. gen|this]]
	- flys to 2m and than the loop trajectory
- does not have the better working `drone_connection.cpp` from `sim_and_real_half_ocho`
- mav trajectory generation 
- px4 autopilot simulated in gazebo
- without using the voxblox map and path planner 
- using hard coded waypoints (3D eight trajectory)
- **using k controller for the z altitude**

## sim_and_real_half_ocho 
✅ working (*checked 22.05.24*)
- branched from `flyling_ocho`
- run it like [[mav traj. gen.,optitrack, px4|this]]
- flyies the half ocho with the real drone
- works also for the sim like `flying ocho` -> [[px4 w_o voxblox & w_ mav traj. gen|here]]

## ros_pid
✅ working (checked 2024-07-18)
- branched from `sim_and_real_half_ocho`
- run it like [[px4 with ROS PID Cntrl with out voxblox & with mav traj. ge|this for the sim]] , or [[mav traj. gen.,optitrack, px4|this for the real drone]] 
- uses the hard coded 3d loop (aka medio ocho or loop)
- can eather run on camera or optitrack (latter noch checked)
#### ros_pid_line
* branched from `ros_pid`
* just like `ros_pid` but instead but flying the line trajectory
#### ros_pid_square
* branched from `ros_pid`
* just like `ros_pid` but instead but flying the square traj.


## hector sim
⚠ ⚠️ to-do, does not exist yet lolololol 
- run it like [[hector  w_ voxblox  & mav traj. gen|this]]
- mav trajectory generation 
- with hector quadrotor drone simulated in gazebo 
- with using voxblox map and path planner



