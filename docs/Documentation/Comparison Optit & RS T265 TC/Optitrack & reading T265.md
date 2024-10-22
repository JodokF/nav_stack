---
tags:
  - TFM/Experiments
---
##### Flying the trajectory with the drone and using Optitrack for localization and at the same time reading the T265 tracking camera

### 1. Flight

#### Current PID Settings:
| Gain  |     | X     |     | Y     |     | Z      |     | YAW   |
| ----- | --- | ----- | --- | ----- | --- | ------ | --- | ----- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.017  |     | 0.01  |
| $K_i$ |     | 0.004 |     | 0.004 |     | 0.0005 |     | 0.005 |
| $K_d$ |     | 0     |     | 0     |     | 0      |     | 0     |

>[!info]- Video paths:
>**RViz**: `/home/cconradi/Documents/TFM/Experiments/trackin_cam_t265/flying_ocho/2024-06-07 16-23-43.mp4`
>** Optitrack**: -> on mrrobot PC

#### Images:
yellow -> optitrack, green -> tracking cam
![[scs-2024-06-07-16-27-32.png|300]] ![[scs-2024-06-07-16-28-05.png|300]] ![[scs-2024-06-07-16-27-59.png|300]] 

### [[Tracking Cam path deviation (rotation)|Problem with deviation -> solved]] 

### 2. Flight

###### Same PID Settings as Flight 1

>[!info]- Video paths:
>**RViz**: ❌
>** Optitrack**: -> on mrrobot PC

#### Images:
yellow -> optitrack, blue -> tracking cam
![[scs-2024-06-27-12-55-47.png|400]] ![[scs-2024-06-27-12-55-30.png|400]]


#### Check out [[real - x, y, z with yaw#PID 11. Test - lower trajectory|this test]]
 without the cam, the trajectory seams to work much better than with the cam -> compare tho the 3. Flight test further down
 even if I just read the information of the cam but does not do anything with it

### 3. Flight
* 2024-07-01 18:32
* -> why is it so much worse than with out reading the pose from the cam?
* -> and wtf is happening in the begining?

###### Same PID Settings as Flight 2

>[!info]- Video paths:
>**RViz**: ❌
>** Optitrack**: ❌

#### Images:
yellow -> optitrack, green -> tracking cam
![[scs-2024-07-01-18-31-04.png|300]] ![[scs-2024-07-01-18-30-57.png|300]] ![[scs-2024-07-01-18-30-50.png|300]]
