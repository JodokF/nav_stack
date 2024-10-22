
### Solution:
In the file: `voxblox/mav_voxblox_planning/voxblox_skeleton/src/io/skeleton_io.cpp`
Changing: `uint32_t` to `uint64_t`;  this one:

`uint32_t tmp_byte_offset = 0;`
to
`uint64_t tmp_byte_offset = 0;`

### Error:
```jsp
Finished  <<< voxblox_ros                         [ 1 minute and 46.8 seconds ]                                                              
Starting  >>> voxblox_skeleton                                                                                                               
_____________________________________________________________________________________________________________________________________________
Errors     << voxblox_skeleton:make /home/ia3/Documents/catkin_ws/logs/voxblox_skeleton/build.make.002.log                                   
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
make[2]: *** Waiting for unfinished jobs....
make[1]: *** [CMakeFiles/Makefile2:354: CMakeFiles/voxblox_skeleton.dir/all] Error 2
make: *** [Makefile:141: all] Error 2
cd /home/ia3/Documents/catkin_ws/build/voxblox_skeleton; catkin build --get-env voxblox_skeleton | catkin env -si  /usr/bin/make --jobserver-auth=3,4; cd -

.............................................................................................................................................
Failed     << voxblox_skeleton:make               [ Exited with code 2 ]                                                                     
Failed    <<< voxblox_skele
```