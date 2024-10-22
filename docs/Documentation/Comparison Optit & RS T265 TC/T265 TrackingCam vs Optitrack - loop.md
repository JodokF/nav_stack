---
Erstellt: 2024-07-24
---
##### Flying the trajectory with the drone and using first Optitrack for localization and then the same trajectory with the T265 tracking camera

## Result:
>[!image_transp]- first -> Tracking Cam, second -> Optitrack
![[scs-2024-07-24-11-58-42.png|550]] ![[scs-2024-07-24-12-17-12.png|550]]


### 1. Flight - with T265 TrackingCam
2024-07-24 12:00

##### Current PID Settings:
| Gain  |     | X     |     | Y     |     | Z      |     | YAW   |
| ----- | --- | ----- | --- | ----- | --- | ------ | --- | ----- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.017  |     | 0.01  |
| $K_i$ |     | 0.004 |     | 0.004 |     | 0.0005 |     | 0.005 |
| $K_d$ |     | 0     |     | 0     |     | 0      |     | 0     |

##### ROSBag of the flight
forgot it 🙄


>[!img]- Images
![[scs-2024-07-24-11-59-00.png|500]]
![[scs-2024-07-24-11-58-48.png|500]]
![[scs-2024-07-24-11-58-42.png|500]]

>[!img]- Videos
> RViz, Optitrack, and GoPro Video here:`/home/cconradi/Documents/TFM/Experiments/comparison_optit_T265Cam`

### 1. Flight - with Optitrack
2024-07-24 12:19
##### PID Settings, same as before

##### ROSBag of the flight
![[optit_pose_loop_2024-07-24-12-15-44.bag]]

>[!img]- Images
>![[scs-2024-07-24-12-17-34.png|500]]
>![[scs-2024-07-24-12-17-20.png|500]]
>![[scs-2024-07-24-12-17-12.png|500]]

>[!img]- Videos
> RViz, Optitrack, and GoPro Video here:`/home/cconradi/Documents/TFM/Experiments/comparison_optit_T265Cam`

### 2. Flight - with T265 TrackingCam
2024-07-24 12:31
##### PID Settings, same as before

##### ROSBag of the flight
![[camera_pose_loop_2024-07-24-12-29-12.bag]]

>[!img]- Images
>![[scs-2024-07-24-12-30-42.png|800]]
>![[scs-2024-07-24-12-30-31.png|800]]
>![[scs-2024-07-24-12-30-25.png|800]]

>[!img]- Videos
> RViz, Optitrack, and GoPro Video here:`/home/cconradi/Documents/TFM/Experiments/comparison_optit_T265Cam`
