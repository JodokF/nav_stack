---
tags:
  - to-do/get_images_from_joplin
---
## flying medio ocho with real drone:

see more images here: 

`/home/cconradi/Documents/TFM/Experiments/px4_real_drone/fyling_medio_ocho`



#### flying without the own p controller:
![[p cntrl test - comparison.png|500]]

#### flying with the own p controller for z:

```
double k_z = 0.1 // right?
error_pose.position.z = pose_cmd_in.pose.position.z - curr_pose.pose.position.z;
vel_calc_z = k_z * (error_pose.position.z / passed_time.toSec());

```
![[p cntrl test - comparison-2.png|500]]
![[p cntrl test - comparison-3.png|500]]

#### compared to the same controller in the simulation:

Only the 'k' factor was reduced for the real drone. But the controller as the same -> much better in the simulation than in real life

![[p cntrl test - comparison-1.png|500]]








