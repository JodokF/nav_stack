Ok thing is I did the stuff with the tracking cam but then I had to do the three weeks of break.
Afterwards i wanted to do the Simulation with [[px4 with ROS PID Cntrl with out voxblox & with mav traj. ge|this]] guide
But then I got this error:

```jade
[ WARN] [1719409731.408736236, 20.464000000]: No transform between frames map and base_link available after 20.464000 seconds of waiting. This warning only prints once.
```

A static transformer
```
<node pkg="tf" type="static_transform_publisher" name="odom2base_link" args="0 0 0 0 0 0 odom base_link 100" /> 
```
also didn't do the job, because the frame didn't moved in RViz.

Turned out I had to turn the `tf: send:` parameter on `true` In the [[Important Files#`px4_config.yaml`|px4_config.yaml]] :

> [!image]- Like this
>![[No transform between frames map and base_link.png|500]]

BUT the thing is I'm reaaaaally sure I haven't changed this since the last run??? So i dont know...