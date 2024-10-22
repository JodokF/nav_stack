---
Erstellt: 2024-07-08
tags:
  - TFM/EKF
  - TFM/QGC
---

* `EKF2_AGP_CTRL`  
	* no fucking idea, apparently (chatgpt) it uses auxiliary global position sensor data to help for the pose estimation. Official references say: *"Aux global position (AGP) sensor aiding"*
	* testet it and doesnt really change much!??
* `EKF2_BARO_CTRL` --> turn off the Barometer
* `EKF2_DRAG_CTRL` 
	* reference: *"Activate wind speed estimation using specific-force measurements and a drag model defined by ..."*
* `EKF2_EV_CTRL`
	* [most important](https://docs.px4.io/main/en/advanced_config/tuning_the_ecl_ekf.html#external-vision-system), to use the extern vision (EV) syestem for the pose estimation
* `EKF2_GPS_CTRL` --> turn off the GPS
* `EKF2_IMU_CTRL` --> turn off the IMU, but apparently the IMU is still used? stated in the beggining of the EKF docs
* `EKF2_OF_CTRL` --> "optical flo aiding" since we don't have it, turned off
* `EKF2_RNG_CTRL` --> "Range control sensor" for the height estm. not used -> turn off