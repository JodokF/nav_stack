---
tags:
  - TFM/Experiments
  - TFM/TrackingCam
---
##### Flying the trajectory with the drone and using the T265 tracking camera for localization

### 1. Flight
2024-07-10
why is there a deviation between the waypoints from the trajectory-planner and the starting position of the drone?
#### Current PID Settings:
| Gain  |     | X     |     | Y     |     | Z      |     | YAW   |
| ----- | --- | ----- | --- | ----- | --- | ------ | --- | ----- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.017  |     | 0.01  |
| $K_i$ |     | 0.004 |     | 0.004 |     | 0.0005 |     | 0.005 |
| $K_d$ |     | 0     |     | 0     |     | 0      |     | 0     |

no Videos
#### Images:
![[scs-2024-07-10-17-17-50.png|300]]![[scs-2024-07-10-17-17-46.png|300]]![[scs-2024-07-10-17-17-39.png|300]]

### 2. Flight
2024-07-10
Just tried it again, I think with the same settings
Strange oscilation of the PID (?)
#### Same PID Settings as Flight 1:

no Videos
#### Images:
![[scs-2024-07-10-19-41-47.png|300]]![[scs-2024-07-10-19-41-32.png|300]]![[scs-2024-07-10-19-41-23.png|300]]


#### tried to solve [[Tracking Cam TF error in trajectory generation|the Problem]] with the offset/error in Z

### 3. Flight
2024-07-15
I mean the deviation in z is better than in the 2. Flight but it still there...

#### Same PID Settings as Flight 2:

no Videos

>[!image]- Images:
![[scs-2024-07-15-18-14-49.png|300]] 
![[scs-2024-07-15-18-14-31.png|300]] 
![[scs-2024-07-15-18-14-20.png|300]]

#### Problems that arised:
[[Tracking Cam TF error in trajectory generation|The problem]] that the trajectory generation didn't red the correct pose of the drone.
[[Tracking Cam TF - absolut error between px4-EKF2 output pose and Tracking Cam|The problem]] that the drone didn't used the right tf frames. 
##### [[Tracking Cam docu and structure|Full Documentation of using the Tracking Camera]]

### 4. Flight
2024-07-18
It looks quite good now
###### Same PID Settings as Flight 3

no Videos....

>[!image]- Images:
![[scs-2024-07-18-10-17-56.png|300]]
![[scs-2024-07-18-10-17-43.png|300]]
![[scs-2024-07-18-10-17-35.png|300]]

### 5. Flight
2024-07-18
Didn't really changed anything, just checked if the merge to main git branch worked

###### Same PID Settings as Flight 4

no Videos....

>[!image]- Images:
![[scs-2024-07-18-15-53-46.png|500]]
![[scs-2024-07-18-15-53-38.png|500]]
![[scs-2024-07-18-15-53-33.png|500]]