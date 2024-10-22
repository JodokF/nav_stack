## Solution:
- change the path (!)
- for example: `/home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/mav_trajectory_generation/mav_trajectory_generation_example`
```shell
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/path/to/mav_trajectory_generation_example
export mav_trajectory_generation_example_DIR=/path/to/mav_trajectory_generation_example
```

![31f6b7a0e8ea090f929d9a18d6c1a660.png](31f6b7a0e8ea090f929d9a18d6c1a660.png)

```shell
Errors     << traj_generation:cmake /home/cconradi/Documents/catkin_ws/logs/traj_generation/build.cmake.000.log                      
CMake Error at /opt/ros/noetic/share/catkin/cmake/catkinConfig.cmake:83 (find_package):
  Could not find a package configuration file provided by
  "mav_trajectory_generation_example" with any of the following names:

    mav_trajectory_generation_exampleConfig.cmake
    mav_trajectory_generation_example-config.cmake

  Add the installation prefix of "mav_trajectory_generation_example" to
  CMAKE_PREFIX_PATH or set "mav_trajectory_generation_example_DIR" to a
  directory containing one of the above files.  If
  "mav_trajectory_generation_example" provides a separate development package
  or SDK, be sure it has been installed.
Call Stack (most recent call first):
  CMakeLists.txt:4 (find_package)


cd /home/cconradi/Documents/catkin_ws/build/traj_generation; catkin build --get-env traj_generation | catkin env -si  /usr/bin/cmake /home/cconradi/Documents/catkin_ws/src/nav_stack_cc/traj_generation --no-warn-unused-cli -DCATKIN_DEVEL_PREFIX=/home/cconradi/Documents/catkin_ws/devel/.private/traj_generation -DCMAKE_INSTALL_PREFIX=/home/cconradi/Documents/catkin_ws/install; cd -
```