---
Erstellt: 2024-07-06
tags:
  - TFM/RQT_Graphs
  - TFM/TrackingCam
  - TFM/Optitrack
---
- [ ] **Everything in respect to Optitrack or the Tracking Cam runs on the Jetson Nano...**

---

## Optitrack:
For example with this [[mav traj. gen.,optitrack, px4|run guide]]

* `open_ports_opti.sh`:
	* `px4_optitrack.launch` (`mavros` package)
		* `node.launch` (= mavros)
			* reads `px4_config_opti.yaml`
		* `CineMPC_optitrack.launch` (`optitrack_arena` pkg)
			* `vrpn_client_node` (-> node; `vrpn_client_ros` pkg)
			* `optitrack_pose_tf` (-> node; `optitrack_arena` pkg)
				* -> publishes pose of drone from this topic:
					* `/optitrack/pose`  to this -> `/mavros/vision_pose/pose`❗
					
>[!image]- RQT - Graph Optitrack:
>![[optit_rgq.svg|800]]

---
## Tracking Cam:
For example with this [[mav traj. gen.,tracking cam, px4|run guide]]
 
* `open_ports_cam.sh`
	* `bridge_mavros_caspar.launch` (`px4_realsense_bridge` pkg)
		* `node.launch` (= mavros)
			* reads `px4_config_cam.yaml`
	* `bridge.launch`(`px4_realsense_bridge` pkg)
		* `rs_t265.launch` (`realsense2_camera` pkg) 
			* `nodelet.launch.xml`
		* `px4_realsense_bridge_node` (-> node; `px4_realsense_bridge` pkg)
			* -> publishes pose of drone from this topic:
				* `/camera/odom/sample_throttled` to this -> `/mavros/odometry/out`❗ ^this-transformation

>[!image]- RQT - Graph Tracking Cam:
>![[t265_rqt.svg|800]]

