#include <traj_generation.h>

/******************** Constructors ******************/

traj_planner::traj_planner(ros::NodeHandle& nh)
                : tf_listener(tf_buffer, nh) 
{    

    //odom_topic = "/mavros/odometry/out";
    // pose_nav_msg_odom_msg_topic = "/optitrack/pose"; // = cine_mpc drone pose (when the optitrack launch file is executed)
    goal_topic = "/vrpn_client_node/goal_optitrack/pose";

    nh.param("/planner_service", planner_service, std::string("/voxblox_rrt_planner/plan"));
    nh.getParam("/drone_connection_node/tracking_camera", tracking_camera); // check if tracking camera is used
    nh.getParam("/drone_connection_node/vxblx_active", vxblx_active);
    nh.getParam("/drone_connection_node/use_pid", use_pid); // determine if PID should be used or not
    nh.getParam("/drone_connection_node/use_mpc", use_mpc); // determine if MPC should be used or not

    nmbr_of_states = 0;
    curr_state = 0;
    waypoint_cntr = 0;
    marker_cntr = 0;


    vel_pub = nh.advertise<geometry_msgs::Twist>
                ("/vel_cmd_2_drone",10);
    pose_pub = nh.advertise<geometry_msgs::PoseStamped>
                ("/pose_cmd_2_drone", 10);
    marker_pub = nh.advertise<visualization_msgs::MarkerArray>
                ("/waypoint_markers", 10);
    pose_sub_geomtry_msg_pose = nh.subscribe<geometry_msgs::PoseStamped>
                ("/optitrack/pose",10,&traj_planner::poseCallback_geomtry_msg_pose,this);
    pose_sub_nav_msg_odom = nh.subscribe<nav_msgs::Odometry>
                ("/mavros/odometry/out",10,&traj_planner::poseCallback_nav_msg_odom,this);
    goal_sub = nh.subscribe<geometry_msgs::PoseStamped>
                (goal_topic,10,&traj_planner::goalCallback,this);
    plan_sub = nh.subscribe<geometry_msgs::PoseArray>
                ("/waypoint_list",10,&traj_planner::planCallback,this);
    path_plan_client = nh.serviceClient<std_srvs::Empty>
                ("/voxblox_rrt_planner/publish_path");
    // motor_enable_service = nh.serviceClient<hector_uav_msgs::EnableMotors>
    //             ("/enable_motors");

    waypoints_received = false;
    odom_received = false;
    planner_service_called = false;

    // pid -> publish in real time since drone_connection is using it 
    if(use_pid) sampling_interval = 0.2; 
    // mpc -> publish all "at once" since mpc needs "the whole" trajectory
    if(use_mpc) sampling_interval = 0.01; 
    if(!use_pid && !use_mpc) sampling_interval = 0.2;

    target_frame = "odom";
    source_frame = "base_link";
    temp_pose.pose.orientation.w = 1.0;
    odom_info_geo_msg.pose.orientation.w = 1.0;
}

/******************** Functions ******************/


void traj_planner::planCallback(const geometry_msgs::PoseArray::ConstPtr& msg){
    
    vxblx_waypoints = *msg;
    ROS_INFO("RRT Planner waypoints received.");
    waypoints_received = true;
    
}

void traj_planner::goalCallback(const geometry_msgs::PoseStamped::ConstPtr &msg){

    goal = *msg;
    goal.pose.position.z = 1.2; // so it's not on the floor...
    if (goal_recieved == false) ROS_INFO("Goal pose received from optitrack ");
    
    goal_recieved = true;

}

void traj_planner::poseCallback_nav_msg_odom(const nav_msgs::Odometry::ConstPtr &msg){    
    
    if (tracking_camera == false){
        odom_info = *msg;
        odom_received = true;
    }

    // The following is necessary because the tracking camera publishes only a topic in respect to the camera_odom_frame 
    // but since this frame is at (0.16, 0, 0.205) at start up and not (0, 0, 0) we need the pose of the camxera
    // in respect to the odom frame
    if(tracking_camera == true){ 
        // to evade some error msgs at the startup
        if (tf_buffer.canTransform(target_frame, source_frame, ros::Time(0))) {
            try{
                tf_odom_to_camera = tf_buffer.lookupTransform(target_frame, source_frame, ros::Time(0));
            } catch (tf2::TransformException ex){
                ROS_ERROR("%s",ex.what());
            }
            tf2::doTransform(temp_pose, odom_info_geo_msg, tf_odom_to_camera); // temp_pose has to be an geometry_msgs::PoseStamped...
        
            odom_info.header = odom_info_geo_msg.header; 
            odom_info.pose.pose = odom_info_geo_msg.pose;
            odom_received = true;
        }
        else {
        ROS_WARN("Transform not available yet, waiting...");
        ros::Duration(0.5).sleep();
        }

    }
}

void traj_planner::poseCallback_geomtry_msg_pose(const geometry_msgs::PoseStamped::ConstPtr &msg){
    
    odom_info.header = msg->header;
    odom_info.pose.pose = msg->pose;    

    odom_received = true;
}

void traj_planner::drawMarkerArray(std::vector<nav_msgs::Odometry> waypoints, int color, int offset){
     
    // offset -> if else markers would be on the same spot
    
    // color -> 1 = RED
    // color -> 2 = GREEN
    // color -> 3 = BLUE

    // Create a publisher for the marker array
    
    // Create a marker array message
    visualization_msgs::MarkerArray marker_array;

    // Create a marker for each pose in the PoseArray
    for (size_t i = 0; i < waypoints.size(); ++i) {
        // Create a new marker for each pose
        visualization_msgs::Marker marker;
        marker.header.frame_id = "map"; 
        marker.header.stamp = ros::Time::now();
        marker.ns = "waypoints";
        marker.id = marker_cntr; // same id are getting overwritten 
        marker_cntr++;
        marker.type = visualization_msgs::Marker::ARROW;
        marker.action = visualization_msgs::Marker::ADD;
        if (offset == 0) marker.pose = waypoints.at(i).pose.pose; // Set the pose of the marker
        if (offset == 1 ){
            marker.pose.position.x = waypoints.at(i).pose.pose.position.x + 0.5;
            marker.pose.position.y = waypoints.at(i).pose.pose.position.y;
            marker.pose.position.z = waypoints.at(i).pose.pose.position.z;
            marker.pose.orientation.x = 0;
            marker.pose.orientation.y = 0;
            marker.pose.orientation.z = 0;
            marker.pose.orientation.w = 1;
        }
        marker.scale.x = 0.15;  // Increase the length of the arrow
        marker.scale.y = 0.01; // Increase the width of the shaft
        marker.scale.z = 0.01;  // Increase the size of the arrowhead
        marker.color.a = 1.0; // Alpha (transparency)
        

        switch (color)
        {
        case 1:
            marker.color.r = 1.0;
            marker.color.g = 0.0; 
            marker.color.b = 0.0; 
            break;
        
        case 2:
            marker.color.r = 0.0;
            marker.color.g = 1.0; 
            marker.color.b = 0.0; 
            break;

        case 3:
            marker.color.r = 0.04;
            marker.color.g = 0.24; 
            marker.color.b = 0.898; 
            break;
        
        default:
            break;
        }
        

        // Add the marker to the marker array
        marker_array.markers.push_back(marker);
    }

    // Publish the marker array
    std::cout << "Markers published\n";
    marker_pub.publish(marker_array);
}


int traj_planner::run_navigation_node(){

    ROS_INFO("Navigation Node Starts");

    int while_loop_ctrl = 0;
    while(odom_received == false){
        ros::Duration(1).sleep();
        std::cout << "Waiting for odom.\n";
        while_loop_ctrl++;
        if (while_loop_ctrl == 10) 
            return -1;
    }
    while_loop_ctrl = 0;

    // Debug Info:
    std::cout << "---\nDrone position for planner (x, y, z): (" << odom_info.pose.pose.position.x << ", " 
                                                                << odom_info.pose.pose.position.y << ", " 
                                                                << odom_info.pose.pose.position.z << ") \n"; 



    
    if(generate_trajectory() == true) return 0;
    
    return -1;
}

// to avoid angle wrap
double traj_planner::get_yaw_difference(double from, double to)
{
    double difference = to - from; 
    while (difference < -M_PI) difference += 2 * M_PI;
    while (difference >  M_PI) difference -= 2 * M_PI;
    return difference;
}


bool traj_planner::generate_trajectory() 
{
    ROS_INFO("Starting trajectory generation!");
    
    // get static odom:
    nav_msgs::Odometry odom_static; // -> to fly away from the drones current position
    nav_msgs::Odometry traj_wp_old; // for velocity calculation
    odom_static = odom_info;
    traj_wp_old = odom_info;
    traj_wp = odom_info; 
    
    double fac = 0.025;
    int cntr = 0;
    double circle_radius = 1.5;
    double slope = 0.1;
    double yaw = 0.0;
    double old_yaw = 0.0;
        

    // trajectory generation 
    while(cntr < 625)
    {
        // calculating the poses for the helix
        traj_wp.pose.pose.position.x = circle_radius * sin(cntr * fac);
        traj_wp.pose.pose.position.y = circle_radius * cos(cntr * fac);
        traj_wp.pose.pose.position.z = slope * cntr * fac + odom_static.pose.pose.position.z; // odom_static; -> to fly away from the drones current hight
        
        // orientation
        yaw = atan2(-1.5 * (sin(cntr * fac)), 1.5 * cos(cntr * fac));

        //Transform yaw pose for helix to quaternions:
        tf2::Quaternion quaternion;
        quaternion.setRPY(0, 0, yaw);

        traj_wp.pose.pose.orientation.x = quaternion.getX();
        traj_wp.pose.pose.orientation.y = quaternion.getY();
        traj_wp.pose.pose.orientation.z = quaternion.getZ();
        traj_wp.pose.pose.orientation.w = quaternion.getW();

        // calculating the velocity 
        traj_wp.twist.twist.linear.x = (traj_wp.pose.pose.position.x - traj_wp_old.pose.pose.position.x) / sampling_interval;
        traj_wp.twist.twist.linear.y = (traj_wp.pose.pose.position.y - traj_wp_old.pose.pose.position.y) / sampling_interval;
        traj_wp.twist.twist.linear.z = (traj_wp.pose.pose.position.z - traj_wp_old.pose.pose.position.z) / sampling_interval;

        // getting the yaw difference to the next pose for the velocity
        traj_wp.twist.twist.angular.z = get_yaw_difference(old_yaw, yaw) / sampling_interval;

        traj_vec.push_back(traj_wp);   
        traj_wp_old = traj_wp;  
        old_yaw = yaw;
        cntr++;    
    }


    drawMarkerArray(traj_vec, 3, 0);
    // drawMAVTrajectoryMarkers();

    return true;

}

void traj_planner::send_vel_commands() {
    
    cmd_pose.header.stamp = ros::Time::now();
    cmd_pose.header.frame_id = "map";
    if(curr_state + 1 <= traj_vec.size()){  // + 1 because if not it sends one 0 0 0 pose...
        
        /*
        std::cout << std::fixed << std::showpoint << std::setprecision(5);
        std::cout   << "Vel. send lin. & yaw: (" 
            << cmd_vel.linear.x << ", "
            << cmd_vel.linear.y << ", "
            << cmd_vel.linear.z << ") - "
            << cmd_vel.angular.z << "\n";
        */

        cmd_vel.linear.x = traj_vec.at(curr_state).twist.twist.linear.x;
        cmd_vel.linear.y = traj_vec.at(curr_state).twist.twist.linear.y;
        cmd_vel.linear.z = traj_vec.at(curr_state).twist.twist.linear.z;
        cmd_vel.angular.x = traj_vec.at(curr_state).twist.twist.angular.x;
        cmd_vel.angular.y = traj_vec.at(curr_state).twist.twist.angular.y;
        cmd_vel.angular.z = traj_vec.at(curr_state).twist.twist.angular.z;

        cmd_pose.pose.position.x = traj_vec.at(curr_state).pose.pose.position.x;
        cmd_pose.pose.position.y = traj_vec.at(curr_state).pose.pose.position.y;
        cmd_pose.pose.position.z = traj_vec.at(curr_state).pose.pose.position.z;
        cmd_pose.pose.orientation.x = traj_vec.at(curr_state).pose.pose.orientation.x;
        cmd_pose.pose.orientation.y = traj_vec.at(curr_state).pose.pose.orientation.y;
        cmd_pose.pose.orientation.z = traj_vec.at(curr_state).pose.pose.orientation.z;
        cmd_pose.pose.orientation.w = traj_vec.at(curr_state).pose.pose.orientation.w;


        // Publish the command
        pose_pub.publish(cmd_pose);
        vel_pub.publish(cmd_vel);


    }else{
        cmd_vel.linear.x = 0.0;
        cmd_vel.linear.y = 0.0;
        cmd_vel.linear.z = 0.0;
        cmd_vel.angular.x = 0.0;
        cmd_vel.angular.y = 0.0;
        cmd_vel.angular.z = 0.0;

        cmd_pose.pose.position.x = traj_vec.at(traj_vec.size()-1).pose.pose.position.x;
        cmd_pose.pose.position.y = traj_vec.at(traj_vec.size()-1).pose.pose.position.y;
        cmd_pose.pose.position.z = traj_vec.at(traj_vec.size()-1).pose.pose.position.z;
        cmd_pose.pose.orientation.x = traj_vec.at(traj_vec.size()-1).pose.pose.orientation.x;
        cmd_pose.pose.orientation.y = traj_vec.at(traj_vec.size()-1).pose.pose.orientation.y;
        cmd_pose.pose.orientation.z = traj_vec.at(traj_vec.size()-1).pose.pose.orientation.z;
        cmd_pose.pose.orientation.w = traj_vec.at(traj_vec.size()-1).pose.pose.orientation.w;

        pose_pub.publish(cmd_pose);
        vel_pub.publish(cmd_vel);
        
    }
        curr_state++;
}


/******************** main() ******************/


int main(int argc, char** argv){
    
    ros::init(argc, argv, "traj_generator");
    ros::AsyncSpinner ich_spinne(1);
    ich_spinne.start();
    ros::NodeHandle node_handle("~");
    traj_planner trj_pln(std::ref(node_handle));

    // run the navigation node and get the trajectory    
    int nav_func_checker = trj_pln.run_navigation_node();

    if (nav_func_checker == 0) ROS_INFO("Navigation succesfully");
    else if (nav_func_checker == -1 ){
        ROS_ERROR("Navigation error");
        return -1;
    }     
    
    while(ros::ok()){
        
        trj_pln.send_vel_commands();

        ros::Duration(trj_pln.sampling_interval).sleep();
    }
    
    


    return 0;

}


