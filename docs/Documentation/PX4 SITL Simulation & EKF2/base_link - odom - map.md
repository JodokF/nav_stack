---
tags: []
---
## To get it like this:
![[base_link - odom - map.png|500]]

* The reference frame ("frame_id") from the base_link in the **px4_config.yaml** file must be odom:

```
# local_position
local_position:
  frame_id: "odom" # not map
  tf:
    send: true
    frame_id: "odom" # not map
    child_frame_id: "base_link"
    send_fcu: false
```

* And in the `mavros_posix_sitl.launch` the position of `odom` can now be set in the tf publisher like this: 
```
<node pkg="tf" type="static_transform_publisher" name="map2odom" args="-1 2 0 0 0 0 map odom 100" />
```

* In the `mavros_posix_sitl.launch` the `<!-- vehicle pose -->` must be set to **0** so that the drone starts at the odom frame. 

