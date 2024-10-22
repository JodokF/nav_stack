---
Erstellt: 2024-09-26
tags:
  - TFM/PID
  - TFM/px4
---
# PX4 [Architectural Overview](https://docs.px4.io/main/en/concept/architecture.html)

### PX4 - Flight Stack

> [!img] Flight Stack Scheme
> ![[PX4 Control Architecture.png|1000]]

![[Basic Drone Terms#Flight Stack]]




### [Multicopter Control Architecture](https://docs.px4.io/main/en/flight_stack/controller_diagrams.html#multicopter-control-architecture)

> [!img] MCA Scheme
> ![[Pasted image 20240926124241.png|850]]

#### Notation:
* $\text{sp}$ = Set Point (?) -> target value the system is trying to achieve 
* $X_{sp}$ = Position Set Point 
* $\psi_{sp}$ = Yaw Set Point 
* $V_{sp}$ = Velocity Set Point
* $A_{sp}$ = Acceleration (?!) Set Point
* $q_{sp}$ = Quaternion (?!) (Orientation) Set Point
* $\Omega_{sp}$ = Quaternion (?!) over time (= Angular Speed) Set Point
* $\delta_{\#_{sp}}$  = Change Set Point in: 
	* $A$ = aileron = roll
	* $E$ = elevator = pitch
	* $R$ = rudder = yaw
	* $T$ = Thrust
* $T_{sp}$ = Throttle Set Point to the four engines (?)

##### Inertial and Body Frame
- **Inertial frame**: 
	- fixed to the *"earth"*
	- represents position and movement of the drone
	- used for **global navigation** and **trajectory control**
	- handles high-level control
- **Body frame**: 
	- attached to the drone itself and moves with it
	- focuses on **stabilization** and **orientation** of the drone -> it adjusts motor outputs to maintain or change the quadcopter's orientation as needed for the trajectory
	- handles low-level control
##### ![[Basic Drone Terms#Angular Cntrl vs Angular Rate Cntrl|Angular Cntrl vs Angular Rate Cntrl]]
##### ![[Basic Drone Terms#Mixer]]
