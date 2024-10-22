Adding the last plugin to the .sdf file of the iris drone:
Path: `.../catkin_ws/src/nav_stack_cc/px4_sitl/PX4-Autopilot/Tools/simulation/gazebo-classic/sitl_gazebo-classic/models/iris/iris.sdf`


```xml

		  <!-- ... -->
		  <input_scaling>0.524</input_scaling>
          <zero_position_disarmed>0</zero_position_disarmed>
          <zero_position_armed>0</zero_position_armed>
          <joint_control_type>position</joint_control_type>
        </channel>
      </control_channels>
    </plugin>
    <static>0</static>
    <plugin name='rotors_gazebo_imu_plugin' filename='libgazebo_imu_plugin.so'>
      <robotNamespace/>
      <linkName>/imu_link</linkName>
      <imuTopic>/imu</imuTopic>
      <gyroscopeNoiseDensity>0.00018665</gyroscopeNoiseDensity>
      <gyroscopeRandomWalk>3.8785e-05</gyroscopeRandomWalk>
      <gyroscopeBiasCorrelationTime>1000.0</gyroscopeBiasCorrelationTime>
      <gyroscopeTurnOnBiasSigma>0.0087</gyroscopeTurnOnBiasSigma>
      <accelerometerNoiseDensity>0.00186</accelerometerNoiseDensity>
      <accelerometerRandomWalk>0.006</accelerometerRandomWalk>
      <accelerometerBiasCorrelationTime>300.0</accelerometerBiasCorrelationTime>
      <accelerometerTurnOnBiasSigma>0.196</accelerometerTurnOnBiasSigma>
    </plugin>
	<!-- This Plugin: -->
  	<plugin name="p3d_base_controller" filename="libgazebo_ros_p3d.so">
		<alwaysOn>true</alwaysOn>
		<updateRate>50.0</updateRate>
		<bodyName>base_link</bodyName>
		<topicName>/mavros/odometry/out</topicName>
		<gaussianNoise>0</gaussianNoise>
		<frameName>map</frameName>
		<xyzOffsets>0 0 0</xyzOffsets>
		<rpyOffsets>0 0 0</rpyOffsets>
  	</plugin>
	<!-- until here, still in the model tags-->
  </model>
</sdf>

```
