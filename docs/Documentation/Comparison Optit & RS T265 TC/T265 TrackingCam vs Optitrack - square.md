---
Erstellt: 2024-07-24
---
##### Flying the trajectory with the drone and using first Optitrack for localization and then the same trajectory with the T265 tracking camera

## Result:
>[!image_transp]- first -> Tracking Cam, second -> Optitrack
![[scs-2024-07-24-18-29-16.png|550]] ![[scs-2024-07-24-16-34-12.png|550]]


### 1. Flight - with Optitrack
2024-07-24 16:33

##### Current PID Settings:
| Gain  |     | X     |     | Y     |     | Z      |     | YAW   |
| ----- | --- | ----- | --- | ----- | --- | ------ | --- | ----- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.017  |     | 0.01  |
| $K_i$ |     | 0.004 |     | 0.004 |     | 0.0005 |     | 0.005 |
| $K_d$ |     | 0     |     | 0     |     | 0      |     | 0     |

##### ROSBag of the flight
![[optit_pose_square_2024-07-24-16-32-08.bag]]


>[!img]- Images
>![[scs-2024-07-24-16-34-32.png|800]]
>![[scs-2024-07-24-16-34-23.png|800]]
>![[scs-2024-07-24-16-34-12.png|800]]


>[!img]- Videos
> add Optitrack, and GoPro
> [1_square_optit_RVIZ.mp4](file:///home/cconradi/Documents/TFM/Experiments/comparison_optit_T265Cam/1_square_optit_RVIZ.mp4)


### 1. Flight - with T265 Tracking Cam
2024-07-24 16:45
❗I forgot to set the right RQT Parameters, therefore the EKF does not have the offset for the camera and is flying around 25cm too high... 🙄 (I think the actual problem was that I didn't call the `drone_connection.launch` with the  `tracking_camera:=true` flag but psssst 🤫 just wasted 45 min of my life with this...)

##### PID - Same settings as with the previous fly 

##### ROSBag of the flight
![[camera_pose_square_2024-07-24-16-43-40.bag]]

>[!img]- Images
>![[scs-2024-07-24-16-45-27.png|800]]
>![[scs-2024-07-24-16-45-12.png|800]]
>![[scs-2024-07-24-16-45-05.png|800]]

>[!img]- Videos
> add Optitrack, and GoPro
> [1_square_cam_Riz.mp4](file:///home/cconradi/Documents/TFM/Experiments/comparison_optit_T265Cam/1_square_cam_Riz.mp4)

### 2. Flight - with T265 Tracking Cam
2024-07-24 18:28

##### PID - Same settings as with the previous fly 

##### ROSBag of the flight
![[camera_pose_square_2024-07-24-18-26-55.bag]]

>[!img]- Images
>![[scs-2024-07-24-18-29-30.png|800]]
>![[scs-2024-07-24-18-29-23.png|800]]
>![[scs-2024-07-24-18-29-16.png|800]]

>[!img]- Videos
> add Optitrack, and GoPro
> [2_square_cam_RViz.mp4](file:///home/cconradi/Documents/TFM/Experiments/comparison_optit_T265Cam/2_square_cam_RViz.mp4)


