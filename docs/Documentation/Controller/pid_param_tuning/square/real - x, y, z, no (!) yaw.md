## Square:
flying the square, without any yaw rotation

### Videos:
OBS - RVIZ: `/home/cconradi/Documents/TFM/Experiments/pid_tuning/videos_31_05/RVIZ`
GoPro: `/home/cconradi/Documents/TFM/Experiments/pid_tuning/videos_31_05/GoPro`
Optitrack: `/home/cconradi/Documents/TFM/Experiments/pid_tuning/videos_31_05/Optitrack`


## 1. Test:
-> same values as with rotation, yaw values don't matter...
action...

| Gain  |     | X      |     | Y      |     | Z    |     | ~~YAW~~   |
| ----- | --- | ------ | --- | ------ | --- | ---- | --- | --------- |
| $K_p$ |     | 0.0075 |     | 0.0075 |     | 0.03 |     | ~~0.01~~  |
| $K_i$ |     | 0      |     | 0      |     | 0    |     | ~~0.005~~ |
| $K_d$ |     | 0      |     | 0      |     | 0    |     | ~~0~~     |
|       |     |        |     |        |     |      |     |           |

### Images:

![[scs-2024-05-31-13-16-43.png|1000]]
![[scs-2024-05-31-13-16-30.png|1000]]
![[scs-2024-05-31-13-16-55.png|1000]]


## 2. Test:
-> reducing kp_z, raising kp_x and kp_y
action...
-> forgot to make screenshots
-> but kp_x and kp_y maybe still to low and kp_z too high

| Gain  |     | X    |     | Y    |     | Z     |     | ~~YAW~~   |
| ----- | --- | ---- | --- | ---- | --- | ----- | --- | --------- |
| $K_p$ |     | 0.01 |     | 0.01 |     | 0.015 |     | ~~0.01~~  |
| $K_i$ |     | 0    |     | 0    |     | 0     |     | ~~0.005~~ |
| $K_d$ |     | 0    |     | 0    |     | 0     |     | ~~0~~     |
### Images:

FUUUUCK closed RVIZ to early! 😩 



## 3. Test:
-> even more: reducing kp_z, raising kp_x and kp_y
action...
-> not too bad actually, kp_z maybe too low, maybe adding ki_x/y 


| Gain  |     | X      |     | Y     |     | Z    |     | ~~YAW~~   |
| ----- | --- | ------ | --- | ----- | --- | ---- | --- | --------- |
| $K_p$ |     | 0.02   |     | 0.02   |     | 0.01 |     | ~~0.01~~  |
| $K_i$ |     | 0      |     | 0     |     | 0    |     | ~~0.005~~ |
| $K_d$ |     | 0      |     | 0     |     | 0    |     | ~~0~~     |

### Images:

![[scs-2024-05-31-14-13-19.png|1000]]
![[scs-2024-05-31-14-13-12.png|1000]]
![[scs-2024-05-31-14-13-25.png|1000]]


### Videos:
OBS - RVIZ:
GoPro:
Optitrack:

## 4. Test:
-> even more: reducing kp_z, raising kp_x and kp_y, adding ki_x/y 
action...
-> ??? no idea, maybe make some rosbags to compare it better with PLOTJUGGLER!


| Gain  |     | X     |     | Y     |     | Z     |     | ~~YAW~~   |
| ----- | --- | ----- | --- | ----- | --- | ----- | --- | --------- |
| $K_p$ |     | 0.018 |     | 0.018 |     | 0.015 |     | ~~0.01~~  |
| $K_i$ |     | 0.002 |     | 0.002 |     | 0.001 |     | ~~0.005~~ |
| $K_d$ |     | 0     |     | 0     |     | 0     |     | ~~0~~     |

### Images:

![[scs-2024-05-31-14-35-41.png|1000]]
![[scs-2024-05-31-14-35-33.png|1000]]
![[scs-2024-05-31-14-35-48.png|1000]]


### Videos:

-> One failed attemped!! -> choose next video in the row

OBS - RVIZ:
GoPro:
Optitrack:


## 5 Test:
-> same pid params as before, recording rosbag:
`rosbag record -o pid_checker /x_pos/setpoint /x_pos/state /x_pos/control_effort /mavros/setpoint_velocity/cmd_vel_unstamped /optitrack/pose /mavros/vision_pose/pose `

![[pid_checker_2024-05-31-17-48-59.bag]]

### Images:

![[scs-2024-05-31-17-51-37 1.png|1000]]
![[scs-2024-05-31-17-51-30 1.png|1000]]
![[scs-2024-05-31-17-51-24 1.png|1000]]


### Videos:

OBS - RVIZ:
GoPro:
Optitrack:


## 6 Test:
-> same pid params as before, recording rosbag with x, y and z pid:
`rosbag record -o pid_checker /x_pos/setpoint /x_pos/state /x_pos/control_effort /y_pos/setpoint /y_pos/state /y_pos/control_effort /z_pos/setpoint /z_pos/state /z_pos/control_effort `

![[pid_checker_2024-05-31-18-09-55.bag]]
![[plot_juggler_layout_2024-05-31.xml]]

#### Plotjuggler:
![[scs-2024-05-31-18-21-12.png|1000]]

| Gain  |     | X     |     | Y     |     | Z     |     | ~~YAW~~   |
| ----- | --- | ----- | --- | ----- | --- | ----- | --- | --------- |
| $K_p$ |     | 0.018 |     | 0.018 |     | 0.015 |     | ~~0.01~~  |
| $K_i$ |     | 0.002 |     | 0.002 |     | 0.001 |     | ~~0.005~~ |
| $K_d$ |     | 0     |     | 0     |     | 0     |     | ~~0~~     |

### Images:

![[scs-2024-05-31-18-11-52.png|1000]]
![[scs-2024-05-31-18-11-46.png|1000]]
![[scs-2024-05-31-18-11-40.png|1000]]


### Videos:

only OBS - RVIZ:
~~GoPro:~~
~~Optitrack:~~


## 7. Test:
-> reducing k_p, raising k_i
action....
-> worse than before... :/

![[pid_checker_2024-06-03-16-18-28.bag]]

| Gain  |     | X     |     | Y     |     | Z     |     | ~~YAW~~   |
| ----- | --- | ----- | --- | ----- | --- | ----- | --- | --------- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.013 |     | ~~0.01~~  |
| $K_i$ |     | 0.003 |     | 0.003 |     | 0.0015|     | ~~0.005~~ |
| $K_d$ |     | 0     |     | 0     |     | 0     |     | ~~0~~     |

#### Plotjuggler:

##### X:
![[scs-2024-06-03-17-05-11.png|1000]]

##### Y:
![[scs-2024-06-03-17-19-50.png|1000]]

### Images:
-> only one picture 🙄 (forgot the others and closed RViz)
![[scs-2024-06-03-16-20-30.png|1000]]

### Videos:

OBS - RVIZ:  ❌
GoPro: ❌
Optitrack: ❌







## 8. Test:
-> going into the other direction as before raising k reducing i -> only for z
action...
-> jesus fuck idk, I think tweaking the PID parameters does not really help at this point any more

![[pid_checker_2024-06-03-17-25-11.bag]]

| Gain  |     | X     |     | Y     |     | Z     |     | ~~YAW~~   |
| ----- | --- | ----- | --- | ----- | --- | ----- | --- | --------- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.017 |     | ~~0.01~~  |
| $K_i$ |     | 0.003 |     | 0.003 |     | 0.0005|     | ~~0.005~~ |
| $K_d$ |     | 0     |     | 0     |     | 0     |     | ~~0~~     |

### Images:

![[scs-2024-06-03-17-27-31.png|1000]]
![[scs-2024-06-03-17-27-22.png|1000]]
![[scs-2024-06-03-17-27-13.png|1000]]


### Videos:

OBS - RVIZ:  ❌
GoPro: ❌
Optitrack: ❌





