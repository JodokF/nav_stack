## 2024-05-30:
## Square:
flying the square, and in each corner a 90 degree rotation
### Videos:
OBS - RVIZ: `/home/cconradi/Documents/TFM/Experiments/pid_tuning/videos_31_05/RVIZ`
GoPro: `/home/cconradi/Documents/TFM/Experiments/pid_tuning/videos_31_05/GoPro`
Optitrack: `/home/cconradi/Documents/TFM/Experiments/pid_tuning/videos_31_05/Optitrack`



## 1. Test:
-> old motors! really bad execution!

| Gain  |     | X      |     | Y      |     | Z     |     | YAW  |
| ----- | --- | ------ | --- | ------ | --- | ----- | --- | ---- |
| $K_p$ |     | 0.01   |     | 0.01   |     | 0.035 |     | 0.01 |
| $K_i$ |     | 0.004  |     | 0.004  |     | 0.015 |     | 0    |
| $K_d$ |     | 0.0005 |     | 0.0005 |     | 0.001 |     | 0    |

### Images:
![[scs-2024-05-30-12-09-14.png|300]] ![[scs-2024-05-30-12-07-15.png|300]] ![[scs-2024-05-30-12-06-57.png|300]]



### No Videos...



--- 
## 2024-05-31:
## 2. Test:
-> new motors, works much somoother than before but still oscilates!

| Gain  |     | X      |     | Y      |     | Z     |     | YAW  |
| ----- | --- | ------ | --- | ------ | --- | ----- | --- | ---- |
| $K_p$ |     | 0.01   |     | 0.01   |     | 0.035 |     | 0.01 |
| $K_i$ |     | 0.004  |     | 0.004  |     | 0.015 |     | 0.005|
| $K_d$ |     | 0.0005 |     | 0.0005 |     | 0.001 |     | 0    |

#### Images:

![[scs-2024-05-31-11-48-13 1.png|300]] ![[scs-2024-05-31-11-47-43 1.png|300]] ![[scs-2024-05-31-11-47-25 1.png|300]]



#### Videos:

no OBS - Rviz Recording
GoPro:
Optitrack:


## 3. Test:
-> reduce x, y and z a little bit and no K_d!
-> even worse to be honest 

| Gain  |     | X      |     | Y     |     | Z     |     | YAW   |
| ----- | --- | ------ | --- | ----- | --- | ----- | --- | ----- |
| $K_p$ |     | 0.0075 |     | 0.0075 |     | 0.03  |     | 0.01  |
| $K_i$ |     | 0.003  |     | 0.003 |     | 0.015 |     | 0.005 |
| $K_d$ |     | 0      |     | 0     |     | 0     |     | 0     |

#### Images:

![[scs-2024-05-31-12-26-08.png|300]] ![[scs-2024-05-31-12-25-36.png|300]] ![[scs-2024-05-31-12-24-21.png|300]]


#### Videos:
OBS - RVIZ:
GoPro:
Optitrack:


## 4. Test:
-> no $K_i$
-> puh idk, still fucked

| Gain  |     | X      |     | Y     |     | Z     |     | YAW   |
| ----- | --- | ------ | --- | ----- | --- | ----- | --- | ----- |
| $K_p$ |     | 0.0075 |     | 0.0075 |     | 0.03  |     | 0.01  |
| $K_i$ |     | 0      |     | 0     |     | 0     |     | 0.005 |
| $K_d$ |     | 0      |     | 0     |     | 0     |     | 0     |

#### Images:

![[scs-2024-05-31-12-43-08.png|300]] ![[scs-2024-05-31-12-43-02.png|300]] ![[scs-2024-05-31-12-42-55.png|300]]


#### Videos:
OBS - RVIZ:
GoPro:
Optitrack:


## 5. Test:
-> reduce k_z, 
-> puh idk, still fucked

| Gain  |     | X      |     | Y     |     | Z     |     | YAW   |
| ----- | --- | ------ | --- | ----- | --- | ----- | --- | ----- |
| $K_p$ |     | 0.0075 |     | 0.0075 |     | 0.03  |     | 0.01  |
| $K_i$ |     | 0      |     | 0     |     | 0     |     | 0.005 |
| $K_d$ |     | 0      |     | 0     |     | 0     |     | 0     |

#### Images:

![[scs-2024-05-31-12-43-08.png|300]] ![[scs-2024-05-31-12-43-02.png|300]] ![[scs-2024-05-31-12-42-55.png|300]]

#### Videos:
OBS - RVIZ:
GoPro:
Optitrack:


## Tuned without yaw [[real - x, y, z, no (!) yaw|here]]

2024-06-06 - Continued testing...with yaw:

## 6. Test :
2024-06-06 12:22

| Gain  |     | X     |     | Y     |     | Z      |     | YAW   |
| ----- | --- | ----- | --- | ----- | --- | ------ | --- | ----- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.017  |     | 0.01  |
| $K_i$ |     | 0.004 |     | 0.004 |     | 0.0005 |     | 0.005 |
| $K_d$ |     | 0     |     | 0     |     | 0      |     | 0     |

#### Images:

![[scs-2024-06-06-12-10-54.png|300]] ![[scs-2024-06-06-12-11-09.png|300]] ![[scs-2024-06-06-12-11-03.png|300]]

#### Videos:
OBS - RVIZ: `/home/cconradi/Documents/TFM/Experiments/pid_tuning/real_square/with_yaw`
GoPro: ❌
Optitrack: -> noch am compi


