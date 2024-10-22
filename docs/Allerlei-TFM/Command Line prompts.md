##### Running Plot Juggler:
`rosrun plotjuggler plotjuggler`
##### Running RQT - TF Tree visualization:
`rosrun rqt_tf_tree rqt_tf_tree`
##### Starting gazebo 
`roslaunch gazebo_ros empty_world.launch `
##### recording rosbag files with name
`rosbag record -o this_name <topics>`
##### search a directory and subdir. for a string
`grep -r "example" .`
##### Reading (only) the mavros state:
`rostopic echo /mavros/state | grep -oP 'mode:\s*"\K[^"]+'`
##### To get hector going:
`rosservice call /enable_motors true`
##### To get pixhawk going:
`rosservice call /mavros/cmd/arming True`
##### Connect to jetson:
`ssh jetson@192.168.0.101`
##### Show time and date:
`date`
##### jump to a ros package
`roscd ros_package` 
##### jump back from cd 'path' or roscd 'pkg'
`cd -`
##### CPU Usage from the CLI :
`sudo jtop`
(installing: `sudo -H pip install -U jetson-stats` -> then `sudo systemctl restart jtop.service`)
from [here...](https://www.seeedstudio.com/blog/2020/07/09/monitor-gpu-cpu-and-other-stats-on-jetson-nano-xavier-nx-tx1-tx2/)



