### Solution
In the **CMakeList.txt** from these packages:
`voxblox/mav_voxblox_planning/voxblox_rrt_planner/` 
`voxblox/mav_voxblox_planning/voxblox_skeleton/` 
`voxblox/mav_voxblox_planning/voxblox_skeleton_planner/` 
`voxblox/mav_voxblox_planning/mav_local_planner/` 
`voxblox/mav_voxblox_planning/mav_planning_benchmark/` 

change this:
`add_definitions(-std=c++11)` 
to this:
```
set(CMAKE_CXX_STANDARD 14)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

### Error
```
7 |   #error PCL requires C++14 or above
```

-> needs C++14 standard

```jsp
Starting  >>> voxblox_rviz_plugin                                       
Finished  <<< voxblox_rviz_plugin                               [ 3.3 seconds ]
Starting  >>> voxblox_ros
Finished  <<< voxblox_ros                                       [ 2 minutes and 36.8 seconds ]                         
Starting  >>> voxblox_planning_common
Starting  >>> voxblox_rrt_planner
Starting  >>> voxblox_skeleton
_______________________________________________________________________________________________________________________
Errors     << voxblox_skeleton:make /home/ia3/Documents/catkin_ws/logs/voxblox_skeleton/build.make.003.log             
/home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/mav_voxblox_planning/voxblox_skeleton/src/io/skeleton_io.cpp: In function ‘bool voxblox::io::loadSparseSkeletonGraphFromFile(const string&, voxblox::SparseSkeletonGraph*)’:
/home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/mav_voxblox_planning/voxblox_skeleton/src/io/skeleton_io.cpp:72:59: error: cannot convert ‘uint32_t*’ {aka ‘unsigned int*’} to ‘uint64_t*’ {aka ‘long unsigned int*’}
   72 |   if (!utils::readProtoMsgFromStream(&proto_file, &proto, &tmp_byte_offset)) {
      |                                                           ^~~~~~~~~~~~~~~~
      |                                                           |
      |                                                           uint32_t* {aka unsigned int*}
In file included from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/mav_voxblox_planning/voxblox_skeleton/src/io/skeleton_io.cpp:1:
/home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/voxblox/voxblox/include/voxblox/utils/protobuf_utils.h:23:39: note:   initializing argument 3 of ‘bool voxblox::utils::readProtoMsgFromStream(std::istream*, google::protobuf::Message*, uint64_t*)’
   23 |                             uint64_t* byte_offset);
      |                             ~~~~~~~~~~^~~~~~~~~~~
make[2]: *** [CMakeFiles/voxblox_skeleton.dir/build.make:63: CMakeFiles/voxblox_skeleton.dir/src/io/skeleton_io.cpp.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:354: CMakeFiles/voxblox_skeleton.dir/all] Error 2
make: *** [Makefile:141: all] Error 2
cd /home/ia3/Documents/catkin_ws/build/voxblox_skeleton; catkin build --get-env voxblox_skeleton | catkin env -si  /usr/bin/make --jobserver-auth=3,4; cd -

.......................................................................................................................
Failed     << voxblox_skeleton:make                             [ Exited with code 2 ]                                 
Failed    <<< voxblox_skeleton                                  [ 16.6 seconds ]                                       
Abandoned <<< mav_voxblox_planning                              [ Unrelated job failed ]                               
Abandoned <<< voxblox_loco_planner                              [ Unrelated job failed ]                               
Abandoned <<< mav_local_planner                                 [ Unrelated job failed ]                               
Abandoned <<< voxblox_skeleton_planner                          [ Unrelated job failed ]                               
Abandoned <<< mav_planning_benchmark                            [ Unrelated job failed ]                               
Finished  <<< voxblox_planning_common                           [ 34.0 seconds ]                                       
_____________________________________________________________________________________________________________________________________________
Errors     << voxblox_rrt_planner:make /home/ia3/Documents/catkin_ws/logs/voxblox_rrt_planner/build.make.003.log                             
In file included from /usr/include/pcl-1.10/pcl/pcl_macros.h:77,
                 from /usr/include/pcl-1.10/pcl/PCLPointField.h:10,
                 from /usr/include/pcl-1.10/pcl/conversions.h:46,
                 from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/voxblox/voxblox_ros/include/voxblox_ros/tsdf_server.h:8,
                 from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/voxblox/voxblox_ros/include/voxblox_ros/esdf_server.h:11,
                 from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/mav_voxblox_planning/voxblox_rrt_planner/include/voxblox_rrt_planner/voxblox_rrt_planner.h:21,
                 from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/mav_voxblox_planning/voxblox_rrt_planner/src/voxblox_rrt_planner.cpp:9:
/usr/include/pcl-1.10/pcl/pcl_config.h:7:4: error: #error PCL requires C++14 or above
    7 |   #error PCL requires C++14 or above
      |    ^~~~~
In file included from /usr/include/pcl-1.10/pcl/console/print.h:44,
                 from /usr/include/pcl-1.10/pcl/conversions.h:53,
                 from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/voxblox/voxblox_ros/include/voxblox_ros/tsdf_server.h:8,
                 from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/voxblox/voxblox_ros/include/voxblox_ros/esdf_server.h:11,
                 from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/mav_voxblox_planning/voxblox_rrt_planner/include/voxblox_rrt_planner/voxblox_rrt_planner.h:21,
                 from /home/ia3/Documents/catkin_ws/src/nav_stack_cc/voxblox/mav_voxblox_planning/voxblox_rrt_planner/src/voxblox_rrt_planner.cpp:9:
/usr/include/pcl-1.10/pcl/pcl_config.h:7:4: error: #error PCL requires C++14 or above
    7 |   #error PCL requires C++14 or above
      |    ^~~~~
In file included from /opt/ros/noetic/include/pcl_ros/point_cloud.h:284,
                 from /home/ia3/Documents/catk
```