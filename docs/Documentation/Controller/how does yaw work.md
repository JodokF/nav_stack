---
tags:
  - to-do/get_images_from_joplin
---
## the mav traj. gen. constraints:
(for the waypoints to make/generate the trajectory)

- the yaw orientation (in euler angles) goes counterclockwise(ccw ↶) from 0° to 360° (actually from 0 to 2π rad but for better understanding now in degree)
- when it moves over 360° it does not start again at 0° but goes to 361°...
- when the drone moves clockwise (cw ↷) it reduces the degrees again:

|#|Rotation|Orientation|
|---| ---    | --- | 
|1.|60° ↶ CCW  |  60°|
|2.|20° ↶ CCW | 80° |
|3.|90° ↷ CW| -10°|
|4.|180° ↶ CCW  | 170° |
|5.|200° ↶ CCW  | 370° |
|6.|380° ↷ CW | -10° |
|7.|360° ↷ CW | -370° |
|8.|370° ↶ CCW | 0° |

## the mav traj. gen. output:
(the orientation of the output of the trajectory generation)

- the yaw orientation is between 0° to 180° (0 to π) on the left side and 0° to -180° on the right side 
- right and left side? I think it depends on the world frame and there everything that is on positiv y side is positiv degree and everything on the negativ y side is negativ degree
- doesnt matter how often the fucking dron spins around:
- This is also the command that the `drone_connection.cpp` becomes:

>[!img]- Like this:
>![[how does yaw work.png|800]]

|#|Rotation|Orientation|
|---| ---    | --- | 
|1.|60° ↶ CCW  |  60°|
|2.|20° ↶ CCW | 80° |
|3.|90° ↷ CW| -10°|
|4.|180° ↶ CCW  | 170° |
|5.|200° ↶ CCW  | 10° |
|6.|380° ↷ CW | -10° |
|7.|360° ↷ CW | -10° |
|8.|370° ↶ CCW | 0° |
|9.|170° ↶ CCW | 170° |
|10.|30° ↶ CCW | -160° |
