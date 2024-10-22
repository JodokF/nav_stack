Important Files for the simulation and for the real drone:
### QGroundControl parameters
* set all parameters from the drone for the mocap and the EKF
	
### `px4_config.yaml`, `px4_config_cam.yaml` or `px4_config_opti.yaml`
* either for using it with the drone
	* `px4_config_cam.yaml`
	* `px4_config_optit.yaml`
* or in the simulation `px4_config.yaml`
* in the `mavros` package, in the `launch` directory
* adjusted so that the frames are published in the ros tf tree

### `iris.sdf`
* actually in the first line it says `DO NOT EDIT: Generated from iris.sdf.jinja`
* but to get the ground truth from gazebo it was necessary -> see [[Getting ground truth from gazebo|here]]

### `mavros_posix_sitl.launch`
* launches the px4 sitl -> the px4 controller simulation
* launches mavros and gazebo

