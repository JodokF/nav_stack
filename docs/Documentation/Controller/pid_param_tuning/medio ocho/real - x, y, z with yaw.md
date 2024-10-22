## PID 1. Test:
too much k in z...

| Gain|    | X   |     |  Y  |     |  Z  |     | YAW |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
|$K_p$|    | 0.02|     | 0.02|     | 0.05|     | 0.04|
|$K_i$|    | 0.01|     | 0.01|     | 0.02|     | 0.01|
|$K_d$|    | 0   |     |  0  |     |  0  |     |  0  |



#### Images:
![[scs-2024-05-28-17-13-38.png|1000]]
![[scs-2024-05-28-17-13-15.png|1000]]
![[scs-2024-05-28-17-11-53.png|1000]]



## PID 2. Test: 
too much k in yaw!?

| Gain|     |X   |     |  Y  |     |  Z  |     | YAW |
| --- | --- |--- | --- | --- | --- | --- | --- | --- |
|$K_p$|     |0.02|     | 0.02|     | 0.04|     | 0.04|
|$K_i$|     |0.01|     | 0.01|     |0.015|     | 0.01|
|$K_d$|     |0   |     |  0  |     |  0  |     |  0  |

#### Images:
		  
![[scs-2024-05-28-17-39-59.png|1000]]
![[scs-2024-05-28-17-39-47.png|1000]]
![[scs-2024-05-28-17-39-15.png|1000]]


## PID 3. Test: 

| Gain|     | X   |     |  Y  |     |  Z  |     | YAW |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
|$K_p$|     |0.025|     |0.025|     | 0.04|     |0.001|
|$K_i$|     |0.015|     |0.015|     |0.015|     |  0  |
|$K_d$|     | 0   |     |  0  |     |  0  |     |  0  |

#### Images:

![[scs-2024-05-28-18-40-26.png|1000]]
![[scs-2024-05-28-18-40-34.png|1000]]
![[scs-2024-05-28-18-40-59.png|1000]]


## PID 4. Test: 

| Gain|     | X   |     |  Y  |     |  Z  |     | YAW |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
|$K_p$|     |0.025|     |0.025|     | 0.04|     |0.001|
|$K_i$|     |0.015|     |0.015|     |0.015|     |0.0005|
|$K_d$|     | 0   |     |  0  |     | 0.01|     |  0  |

#### Images:

![[scs-2024-05-28-18-50-14.png|1000]]
![[scs-2024-05-28-18-50-33.png|1000]]
![[scs-2024-05-28-18-50-46.png|1000]]




## PID 5. Test: 
besser?!

| Gain|     | X   |     |  Y  |     |  Z  |     | YAW |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
|$K_p$|     |0.025|     |0.025|     | 0.04|     |0.01 |
|$K_i$|     |0.015|     |0.015|     |0.015|     |  0  |
|$K_d$|     | 0   |     |  0  |     | 0.01|     |  0  |

#### Images:

![[scs-2024-05-28-18-59-05.png|1000]]
![[scs-2024-05-28-18-59-14.png|1000]]
![[scs-2024-05-28-18-59-24.png|1000]]



## PID 6. Test: 
* WTF
* big change after tuning k for x and y with the straight line
* really strange behaviour! 

| Gain|     | X   |     |  Y  |     |  Z  |     | YAW |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
|$K_p$|     |0.01 |     | 0.01|     |0.035|     | 0.01|
|$K_i$|     |0.004|     |0.004|     |0.015|     |  0  |
|$K_d$|     |0.0005|    |0.0005|    |0.001|     |  0  |

#### Images:

![[scs-2024-05-29-14-40-00.png|1000]]
![[scs-2024-05-29-14-40-07.png|1000]]
![[scs-2024-05-29-14-40-16.png|1000]]

## "break" ➡ pid tuning with the square [[real - x, y, z, no (!) yaw|here]] and [[real - x, y, z, yaw|here]]  

-> continued testing 2024-06-06

## PID 7. Test: 
* 2024-06-06 13:40
* hm, alright, some strangs loops
* going to do a next test, because maybe the reason was because of running OBS at my computer which needs much resources

| Gain  |     | X     |     | Y     |     | Z      |     | YAW   |
| ----- | --- | ----- | --- | ----- | --- | ------ | --- | ----- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.017  |     | 0.01  |
| $K_i$ |     | 0.004 |     | 0.004 |     | 0.0005 |     | 0.005 |
| $K_d$ |     | 0     |     | 0     |     | 0      |     | 0     |

#### Images:

![[scs-2024-06-06-13-37-28.png|1000]]
![[scs-2024-06-06-13-37-23.png|1000]]
![[scs-2024-06-06-13-36-36.png|1000]]


#### Videos:
OBS - RViz: /home/cconradi/Documents/TFM/Experiments/pid_tuning/real_ocho/2024-06-06 13-23-24.mp4
Optitrack: -> mrrobo pc














## PID 8. Test: 
* 2024-06-06 14:20
* ok without running OBS (to reduce ) it doesn't changed almost anything...
* idk

| Gain  |     | X     |     | Y     |     | Z      |     | YAW   |
| ----- | --- | ----- | --- | ----- | --- | ------ | --- | ----- |
| $K_p$ |     | 0.017 |     | 0.017 |     | 0.017  |     | 0.01  |
| $K_i$ |     | 0.004 |     | 0.004 |     | 0.0005 |     | 0.005 |
| $K_d$ |     | 0     |     | 0     |     | 0      |     | 0     |

#### Images:

![[scs-2024-06-06-14-18-45.png|300]] ![[scs-2024-06-06-14-18-40.png|300]] ![[scs-2024-06-06-14-18-34.png|300]]


#### Videos:
OBS - RViz: ❌
Optitrack: -> mrrobo pc

## "break" ➡ three weeks on a different (learning for the exam) project
2024-06-26 test
## PID 9. Test: 
* 2024-06-26 17:42
* **same parameters as with test flight 8 but quite a different result:**


#### Images:

![[scs-2024-06-26-17-44-31.png|300]] ![[scs-2024-06-26-17-44-23.png|300]] ![[Pasted image 20240626174622.png|300]]


#### Videos:
OBS - RViz: ❌
Optitrack: -> mrrobo pc


## PID 10. Test: 
* 2024-07-01 17:54
* **same parameters as with test flight 9**
* i did an PID autotune in QGC, but I'm not sure if it really works better because of that

#### Images:

![[scs-2024-07-01-17-51-17.png|300]] ![[scs-2024-07-01-17-51-01.png|300]] ![[scs-2024-07-01-17-50-53.png|300]]

#### Videos:
OBS - RViz: ❌
Optitrack: ❌

## PID 11. Test - lower trajectory: 
* 2024-07-01 18:11
* **same parameters as with test flight 10**
* lowered the hight (z value) of the loop by half a meter 
	* had the feeling that the higher it gets, the worse the optitrack measurment gets
-> seems to work better now!

#### Images:

![[scs-2024-07-01-18-09-27.png|300]]![[scs-2024-07-01-18-09-14.png|300]]![[scs-2024-07-01-18-09-05.png|300]]

#### Videos:
OBS - RViz: ❌
Optitrack: ❌

### -> long break, implemented the tracking cam...

## PID 12. Test - higher velocity: 
* 2024-07-19 12:14
* **same parameters as with test flight 11**
* Wanted to try it with higher velocity. 
	* Now instead of 0.3 m/s for the trajectory generation 0.6 m/s
	* -> seems to work pretty fucking well 

#### Images:

![[scs-2024-07-19-12-13-45.png|500]]
![[scs-2024-07-19-12-13-31.png|500]]
![[scs-2024-07-19-12-13-24.png|500]]

#### Videos:
OBS - RViz: ❌
Optitrack: ❌

## PID 13. Test - even higher velocity: 
* 2024-07-19 12:14
* **same parameters as with test flight 11**
* Wanted to try it with higher velocity. 
	* Now instead of 0.6 m/s for the trajectory generation 0.9 m/s
	* -> seems to work pretty well, but i think 0.6 m/s worked better 

#### Images:

![[scs-2024-07-19-12-59-24.png|500]] 
![[scs-2024-07-19-12-59-07.png|500]] 
![[scs-2024-07-19-12-58-59.png|500]]

#### Videos:
OBS - RViz: ❌
Optitrack: ❌








