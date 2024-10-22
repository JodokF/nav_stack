explanation of [[read T265 tracking cam, mav traj. gen., px4|this]] basically...
* At the beginning the cam is at the same position as the optitrack pose
* this is managed by first taking the node `move_cam_to_cinempc` which calculates the difference in the tf tree between the origin and the optitrack pose and puts it on the param server
* than a static_transform_publisher is launched (with the launch file) and the params are passed as an argument 
* and than read the path from the cam and from optitrack