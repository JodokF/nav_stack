```C++
wp1.pose.pose.position.x = 1;
wp1.pose.pose.position.y = 1;
wp1.pose.pose.position.z = 2.5;
wp1.pose.pose.orientation.z = 0; // we use it now as if it were yaw and not a quaternion
wp1.twist.twist.linear.x = x_y_vel;
wp1.twist.twist.linear.y = 0; 
wp1.twist.twist.linear.z = z_vel_lin;
wp1.twist.twist.angular.z = -z_vel_ang;

wp2.pose.pose.position.x = 2;
wp2.pose.pose.position.y = 0;
wp2.pose.pose.position.z = 3;
wp2.pose.pose.orientation.z = ((-M_PI)/2) ; // (3*M_PI)/2; // we use it now as if it were yaw and not a quaternion
wp2.twist.twist.linear.x = 0;
wp2.twist.twist.linear.y = -x_y_vel; 
wp2.twist.twist.linear.z = 0;
wp2.twist.twist.angular.z = -z_vel_ang;

wp3.pose.pose.position.x = 1;
wp3.pose.pose.position.y = -1;
wp3.pose.pose.position.z = 2.5;
wp3.pose.pose.orientation.z = - M_PI; 
wp3.twist.twist.linear.x = -x_y_vel;
wp3.twist.twist.linear.y = 0; 
wp3.twist.twist.linear.z = -z_vel_lin;
wp3.twist.twist.angular.z = -z_vel_ang;

wp4.pose.pose.position.x = 0;
wp4.pose.pose.position.y = 0;
wp4.pose.pose.position.z = 2;
wp4.pose.pose.orientation.z = (-5*M_PI)/4; 
wp4.twist.twist.linear.x = -x_y_vel;
wp4.twist.twist.linear.y =  x_y_vel; 
wp4.twist.twist.linear.z = -z_vel_lin;
wp4.twist.twist.angular.z = 0;

wp5.pose.pose.position.x = -1;
wp5.pose.pose.position.y = 1;
wp5.pose.pose.position.z = 1.5;
wp5.pose.pose.orientation.z = - M_PI; 
wp5.twist.twist.linear.x = -x_y_vel;
wp5.twist.twist.linear.y = 0; 
wp5.twist.twist.linear.z = -z_vel_lin;
wp5.twist.twist.angular.z = z_vel_ang;

wp6.pose.pose.position.x = -2;
wp6.pose.pose.position.y = 0;
wp6.pose.pose.position.z = 1;
wp6.pose.pose.orientation.z = (-M_PI)/2; 
wp6.twist.twist.linear.x = 0;
wp6.twist.twist.linear.y = -x_y_vel; 
wp6.twist.twist.linear.z = 0;
wp6.twist.twist.angular.z = z_vel_ang;

wp7.pose.pose.position.x = -1;
wp7.pose.pose.position.y = -1;
wp7.pose.pose.position.z = 1.5;
wp7.pose.pose.orientation.z = 0; 
wp7.twist.twist.linear.x = x_y_vel;
wp7.twist.twist.linear.y = 0; 
wp7.twist.twist.linear.z = z_vel_lin;
wp7.twist.twist.angular.z = z_vel_ang;
```