### Main error:

#### <span style="color: bf4040;">FCU: Preflight Fail: Yaw estimate error</span>

### Other errors (yet no solution:)

<font color=bf4040> FCU: Connection to mission computer lost</font>  
<font color=bf4040> FCU: Preflight Fail: position estimate error</font> 


## Source:

- The network traffic of the computer connection is occupied so the messages arrive with an delay (or don't arrive at all idk.)
- This was discovered by playing a 4k YouTube Video while having the Drone running  
- The problem with the Video is that also the CPU usage is rising so I wasn't sure from what it comes. 
- But when downloading a large file from the internet (high network usage, low CPU usage) the problem with the yaw estimate error consists
- Building a big catkin_ws in the background (low network usage, high cpu usage) the problem of yaw estimate error seems not to come up

>[!image]- Problem:
>![[yaw estimate error (connection to mission computer.png]]


## Solution:
- running the optitrack node on the jetson
-> [[Running Optitrack on the drone|how it works here...]]


---
#### Prior / old theories:

Honestly I have no idea why, sometimes they apper more sometimes less.  
Last stand was that they (almost) didn't appear.

- CPU usage to high, when I download the logs they tend to apper more often
- Somthing with the connection over the telemetry or also over the WLAN
- Maybe somthing with tf tree
- Maybe somthing with tf tree transformation from Optitrack to NED frame
- [Mag type](https://github.com/PX4/PX4-Autopilot/issues/14876#issuecomment-626266994): changing `EKF2_MAG_TYPE` from `none` to `automatic`
    - less occurences!  
        \-> and add. reboot ???

### Log fies discoverys

- Jumps in Z position and velocity. [here](https://review.px4.io/plot_app?log=7e713f52-d2fb-4b6d-a3c7-88f197400490)
- When starting downloading the log data from the pxh. (at min. 41:16) strange things happen. see [here](https://review.px4.io/plot_app?log=0f1cff0c-52dd-45a5-a875-efa34299e744)