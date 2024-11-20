## Setup new Computer/User

### 1. [Install ROS noetic](http://wiki.ros.org/noetic/Installation/Ubuntu)
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl # if you haven't already installed curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt update
sudo apt install ros-noetic-desktop-full
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
sudo apt install python3-rosdep
rosdep update
```
#### to check:
```
rosversion -d
```

### 2. [Install catkin build](https://catkin-tools.readthedocs.io/en/latest/installing.html)
Copy / pasta this as one block:
```
sudo sh \
    -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" \
> /etc/apt/sources.list.d/ros-latest.list'
```
now continue each line as one by one:
```
wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
sudo apt-get update
sudo apt-get install python3-catkin-tools
```

### 3. Install necessary dependencies:
```
sudo apt-get install ros-noetic-geographic-msgs ros-noetic-tf2-sensor-msgs ros-noetic-moveit ros-noetic-mavros ros-noetic-mavros-extras ros-noetic-mavros-msgs python3-wstool python3-catkin-tools ros-noetic-cmake-modules libyaml-cpp-dev protobuf-compiler autoconf libompl-dev ros-noetic-hector-trajectory-server ros-noetic-vrpn-client-ros ros-noetic-realsense2-camera

```
#### to check if stuff is working:
```
mkdir -p catkin_ws/src
cd catkin_ws
catkin build
```


### 4. Installing Voxblox and mav_traj_gen
* Suggestion:
	* make directory: `$ mkdir .../catkin_ws/src/voxblox`
	* and git clone to this `voxblox` directory now (because those are 17 ROS packages and things will get messy)

* for voxblox -> [Installation Guide](https://voxblox.readthedocs.io/en/latest/pages/Installation.html)
* for voxblox planning (and mav_traj_gen) -> [Installation Guide](https://github.com/ethz-asl/mav_voxblox_planning?tab=readme-ov-file#installation)

##### Errors may occur:
* [[setting up mavros Packages, mav_trajectory_generat|mav_traj pkg not found]]
* [[error with c++ standard 11 to 14]]
* [[undefined reference to ompl]] 
* [[voxblox_skeleton uint32_t - uint64_t]]


### 5. Setting up the px4 sitl (development environment)
-> Suggestion: clone the `PX4-Autopilot` into the `catkin_ws` although it is not getting build
#### [this commands](https://docs.px4.io/main/en/dev_setup/dev_env_linux_ubuntu.html#simulation-and-nuttx-pixhawk-targets) for the px4 Simulation Environment: 
```
git clone https://github.com/PX4/PX4-Autopilot.git --recursive
bash ./PX4-Autopilot/Tools/setup/ubuntu.sh
```
#### [this commands](https://docs.px4.io/main/en/simulation/ros_interface.html#launching-gazebo-classic-with-ros-wrappers) for Launching ROS and Simulation:
- adapted with comments:
```bash
cd PX4-Autopilot # go to the before downloaded pkg
DONT_RUN=1 make px4_sitl_default gazebo-classic # takes a few minutes
source ~/catkin_ws/devel/setup.bash    # optional -> i did it...
source Tools/simulation/gazebo-classic/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd)
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd)/Tools/simulation/gazebo-classic/sitl_gazebo-classic
roslaunch px4 posix_sitl.launch # to test if the installation worked
```

#### Adapting the `.bashrc` 
* so that the `px4` package is found:
* and other ros stuff ;)
* (!) change `your_path_to`to the one on your system (the absolute path...)
* and change the IPs to your computer
```bash
export ROS_HOSTNAME=192.168.0.29
export ROS_IP=http://192.168.8.29

source /your_path_to/catkin_ws/devel/setup.bash

# this has to be one line: (!)
source /your_path_to/PX4-Autopilot/Tools/simulation/gazebo-classic/setup_gazebo.bash /your_path_to/PX4-Autopilot /your_path_to/PX4-Autopilot/build/px4_sitl_default

export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:/your_path_to/PX4-Autopilot
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:/your_path_to/PX4-Autopilot/Tools/simulation/gazebo-classic/sitl_gazebo-classic 
```

#### Following [[Getting ground truth from gazebo|this guide]] to get the ground truth of the drone from gazebo 

#### adapt `px4_config.yaml` (in `mavros` pkg)
- to get ther: `$ roscd mavros/launch` -> `$ gedit px4_config.yaml`
- change: `local_position tf: send:` to `true` 
- like this:
```
local_position:
  frame_id: "map"
  tf:
    send: true
    frame_id: "map"
    child_frame_id: "base_link"
    send_fcu: false
```

### 6. clone [this git repo](https://github.com/JodokF/nav_stack) into the `catkin_ws/src`
* to get the 3D model in RViz change the absolute path from the `mesh filename` in `.../nav_stack/meshes/cinempc.urdf` to the path from this computer

### 7. [installing QGroundControl ](https://docs.qgroundcontrol.com/master/en/qgc-user-guide/getting_started/download_and_install.html#ubuntu)

#### load QGC parameters for the Drone
- the params are in the git-hub repo
- they have to be added in QGC:
	- click on the *QGC logo* (left upper corner)
		- *Vehicle Setup*
			- *Parameters* (left panel)
				- *Tools* (right upper corner)
					- *load from file*

### 8. [[px4 test|Simulation Enviroment Test Guide]] 

### 9. install the [ROS PID package](http://wiki.ros.org/pid#Installing_the_package)
`sudo apt-get install ros-noetic-pid`
 
### 10. [[px4 with ROS PID Cntrl with out voxblox & with mav traj. ge|Simulated Trajectory Generation Test Guide]]

### 11. Real Drone:
#### [[mav traj. gen.,optitrack, px4|Real Trajectory Generation Test Guide - Optitrack]]

#### [[mav traj. gen.,tracking cam, px4|Real Trajectory Generation Test Guide - Tracking Cam]]

### Info
#### -> [[Important Files]]









