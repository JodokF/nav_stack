I changed the Parameters
`CAL_GYRO0_PRIO` and `CAL_ACC0_PRIO` to *disabled* then I got the ERROR.
The problem was that it took the (iris) Drone ages to connect to QGroundControl and again ages to load the new parameters (enabling the Gyro and Acc). After loading it it worked again. (with ages I mean a couple of minutes)


ERROR [simulator_mavlink] poll timeout 0, 22
poll timeout

![eea72bb09143118864cc97419ffa0a9b.png](eea72bb09143118864cc97419ffa0a9b.png)