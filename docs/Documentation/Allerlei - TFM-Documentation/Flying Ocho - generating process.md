---
tags: []
aliases:
  - hard coded points for flying ocho
---
>[!info] More images and Video here:
>`/home/cconradi/Documents/TFM/Experiments/px4_sitl_sim/flying_ocho`

Choosing the points and all have the same orientation works well:


![[Flying Ocho - generating process-4.png|500]]



## Orientation:
For the orientation a fourth dimension had to be given to the traj. gen. → the yaw of the drone.
(now using a ND eigen-Vector but a 3D anymore)

0° = 0
90° = π / 2
<= 180° = π
\>= 180° = -π
270° = -π / 2
360° = 0
→ When the Drone turns left → positiv Values 
→ When the Drone turns right → negativ Values 

If this is not taken into account the drone is rotating one time around itself to reach the goal like here:

![[Flying Ocho - generating process-3.png|500]]


Then the problem is with different velocities (lin. x, y, z and a yaw velocity → again 4D eigen Vector for each point) that they have (apparently) to be exactly right to go through each point. This is the nearest result:

![[Flying Ocho - generating process-2.png|500]]


If they are to slow it looks like this:

![[Flying Ocho - generating process-1.png|500]]


If they are to fast like this: 

![[Flying Ocho - generating process.png|500]]



