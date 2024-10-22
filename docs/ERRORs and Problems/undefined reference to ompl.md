
##  [ompl issue](https://github.com/ethz-asl/mav_voxblox_planning/issues/22):
`undefined reference to 'ompl::geometric::SimpleSetup::haveExactSolutionPath() const'`
-> `ros_noetic_ompl` has to be deleted and `libompl-dev` installed:
deleting `ros_noetic_ompl` (installation is in the package list further up): 
```
sudo apt remove ros-noetic-ompl
```
#### Next Problem:
![434532253868a980e14be2966954d113.png](434532253868a980e14be2966954d113.png)
-> `catkin clean` and `catkin build` solved it

