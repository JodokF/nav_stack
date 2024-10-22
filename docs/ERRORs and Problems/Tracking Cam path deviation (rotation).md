As seen [[Optitrack & reading T265#Images|here]] and in this image:
![[scs-2024-06-07-16-27-59.png|300]] 
there was a absolut deviation between the tracking camera and the Optitrack path when firstly installing the camera.

This was because when reading the position of the Camera from Optitrack (to tell the camera that it has the same position now) the Quaternion values where taken as euler-angles in the `move_cam_to_cinempc.cpp` file. 
Now after converting the quats to euler before passing it to the position of the cam the aboslut deviation is gone as seen [[Optitrack & reading T265#2. Flight|here]] and in this image:
![[scs-2024-06-27-12-55-38.png|300]]