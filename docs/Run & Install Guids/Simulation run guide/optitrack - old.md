# Optitrack

<details><summary style="font-size: 1.4em; font-weight: normal; line-height: 1.8; color: #b58900;">Opti Track:</summary>

To launch optitrack "tester" (?):

```cpp
roslaunch optitrack_arena CineMPC_optitrack.launch
```

The file: `catkin_ws/src/Dwa3D/optitrack_arena/launch/tyrion_gt_optitrack.launch`

#### File Explanation:

- `trackers:`
    - choose which system (drone, camera, goal) should be tracked
- in RViz
    - fixed frame = `odom` = referenz coordinatesystem (origin)
    - TF shows the different tracked systems
- topics in ROS
    - when `tyrion_gt_optitrack.launch` is launched
        - tyrion pose topic = `/optitrack/pose`
        - the goal = `/vrpn_client_node/goal_optitrack/pose`
        - dummy = `/vrpn_client_node/dummy/pose`
    - when instead `dummy_optitrack.launch` is launched
        - dummy = `/optitrack/pose`
        - tyrion = `/vrpn_client_node/base_link/pose`(base_link = tyrion...that how it is)
    - \-> **check remaping in the launch files**

#### New Object to track:

- select the detected balls on the object -> right click `create rigid body` and finish...mit dem Namen kann man in RViz dann die Position checken

</details>

<details>
<summary style="font-size: 1.4em; font-weight: normal; line-height: 1.8; color: #b58900;">Voxblox Simulation:</summary>

For each command a new terminal window, explanation for each line below:

```
roslaunch voxblox_ros arena_test.launch
rosservice call /voxblox_node/load_map "file_path: '/home/jodok/Documents/catkin_ws/src/arena_1obs_upgraded.voxblox'" 
rosservice call /voxblox_node/generate_mesh "{}" 
roslaunch voxblox_rrt_planner rrt_saved_map.launch
rviz


```

#### Explanation:

1.  opening the voxblox_node
2.  see [here](https://voxblox.readthedocs.io/en/latest/pages/The-Voxblox-Node.html)  
    "The service call loads the tsdf layer from a .vxblx file."
3.  the rosservice calls can be run in the same terminail
4.  starting the rrt planner, to get the way points  
    <br/>

</details>



