---
Erstellt: 2024-10-14
---
### Solution: 
reinstalling GeographicLib -> nope has not worked (maybe i did it wrong lol)
since the directory in `/usr/share/GeographicLib` was empty I took the stuff that was on the other computer in this directory and manually copied it there -> worked lolololol

### Error:
==`[FATAL] [1728913529.559459508]: UAS: GeographicLib exception: File not readable /usr/share/GeographicLib/geoids/egm96-5.pgm | Run install_geographiclib_dataset.sh script in order to install Geoid Model dataset!`==

```bash
INFO  [parameters] BSON document size 274 bytes, decoded 274 bytes (INT32:11, FLOAT:3)
INFO  [param] selected parameter backup file parameters_backup.bson
process[vehicle_spawn_ia3_SVS1312C5E_76529_209759696653915593-4]: started with pid [76584]
process[mavros-5]: started with pid [76591]
process[map2odom-6]: started with pid [76608]
process[gt/trajectory_server_loam-7]: started with pid [76621]
process[rviz-8]: started with pid [76629]
process[offb_sim_node-9]: started with pid [76649]
[FATAL] [1728913529.559459508]: UAS: GeographicLib exception: File not readable /usr/share/GeographicLib/geoids/egm96-5.pgm | Run install_geographiclib_dataset.sh script in order to install Geoid Model dataset!
INFO  [dataman] data manager file './dataman' size is 7872608 bytes
INFO  [init] PX4_SIM_HOSTNAME: localhost
INFO  [simulator_mavlink] Waiting for simulator to accept connection on TCP port 4560
[INFO] [1728913530.224225, 0.000000]: Loading model XML from file /home/ia3/Documents/catkin_ws/src/nav_stack_cc/px4_sitl/PX4-Autopilot/Tools/simulation/gazebo-classic/sitl_gazebo-classic/models/iris/iris.sdf
[INFO] [1728913530.234238, 0.000000]: Waiting for service /gazebo/spawn_sdf_model
================================================================================REQUIRED process [mavros-5] has died!
process has finished cleanly
log file: /home/ia3/.ros/log/923d68d8-8a32-11ef-a59d-2bd965c9db38/mavros-5*.log
Initiating shutdown!
================================================================================
[offb_sim_node-9] killing on exit
[rviz-8] killing on exit
[gt/trajectory_server_loam-7] killing on exit
[map2odom-6] killing on exit
[vehicle_spawn_ia3_SVS1312C5E_76529_209759696653915593-4] killing on exit
[mavros-5] killing on exit
[gazebo-3] killing on exit
[sitl-2] killing on exit
ERROR [px4] Startup script returned with return value: 2
Traceback (most recent call last):
  File "/opt/ros/noetic/lib/gazebo_ros/spawn_model", line 239, in <module>
    exit_code = sm.run()
  File "/opt/ros/noetic/lib/gazebo_ros/spawn_model", line 187, in run

```