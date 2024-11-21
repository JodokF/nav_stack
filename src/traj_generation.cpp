#include <traj_generation.h>

/******************** Constructors ******************/

poly_traj_plan::poly_traj_plan(ros::NodeHandle& nh)
                : tf_listener(tf_buffer, nh) 
{    

    //odom_topic = "/mavros/odometry/out";
    // pose_nav_msg_odom_msg_topic = "/optitrack/pose"; // = cine_mpc drone pose (when the optitrack launch file is executed)
    goal_topic = "/vrpn_client_node/goal_optitrack/pose";

    nh.param("/planner_service", planner_service, std::string("/voxblox_rrt_planner/plan"));
    nh.getParam("/drone_connection_node/tracking_camera", tracking_camera); // check if tracking camera is used
    nh.getParam("/drone_connection_node/vxblx_active", vxblx_active);

    nmbr_of_states = 0;
    curr_state = 0;
    waypoint_cntr = 0;
    marker_cntr = 0;


    vel_pub = nh.advertise<geometry_msgs::Twist>
                ("/vel_cmd_2_drone",10);
    pose_pub = nh.advertise<geometry_msgs::PoseStamped>
                ("/pose_cmd_2_drone", 10);
    mav_traj_markers_pub = nh.advertise<visualization_msgs::MarkerArray>
                ("/trajectory_markers", 0);
    marker_pub = nh.advertise<visualization_msgs::MarkerArray>
                ("/waypoint_markers", 10);
    pose_sub_geomtry_msg_pose = nh.subscribe<geometry_msgs::PoseStamped>
                ("/optitrack/pose",10,&poly_traj_plan::poseCallback_geomtry_msg_pose,this);
    pose_sub_nav_msg_odom = nh.subscribe<nav_msgs::Odometry>
                ("/mavros/odometry/out",10,&poly_traj_plan::poseCallback_nav_msg_odom,this);
    goal_sub = nh.subscribe<geometry_msgs::PoseStamped>
                (goal_topic,10,&poly_traj_plan::goalCallback,this);
    plan_sub = nh.subscribe<geometry_msgs::PoseArray>
                ("/waypoint_list",10,&poly_traj_plan::planCallback,this);
    path_plan_client = nh.serviceClient<std_srvs::Empty>
                ("/voxblox_rrt_planner/publish_path");
    // motor_enable_service = nh.serviceClient<hector_uav_msgs::EnableMotors>
    //             ("/enable_motors");

    waypoints_received = false;
    odom_received = false;
    planner_service_called = false;

    if(vxblx_active == true) goal_recieved = false;

    else if (vxblx_active == false){
        // for the hard coded trajectory: (when no optitrack goal is detected)
        altitude_factor = 1.0; // to *reduce* the hight of the flying ocho -> if it is 0 flying high is between 1 and 3 m -> start & goal at 2 m
        x_offset = 1.0; // to move the trajectory in x
        goal.pose.position.x = 0 - x_offset; 
        goal.pose.position.y = 0; 
        goal.pose.position.z = 2 - altitude_factor; 
        goal_recieved = true;
    }

    target_frame = "odom";
    source_frame = "base_link";
    temp_pose.pose.orientation.w = 1.0;
    odom_info_geo_msg.pose.orientation.w = 1.0;
}

/******************** Functions ******************/


void poly_traj_plan::planCallback(const geometry_msgs::PoseArray::ConstPtr& msg){
    
    vxblx_waypoints = *msg;
    ROS_INFO("RRT Planner waypoints received.");
    waypoints_received = true;
    
}

void poly_traj_plan::goalCallback(const geometry_msgs::PoseStamped::ConstPtr &msg){

    goal = *msg;
    goal.pose.position.z = 1.2; // so it's not on the floor...
    if (goal_recieved == false) ROS_INFO("Goal pose received from optitrack ");
    
    goal_recieved = true;

}

void poly_traj_plan::poseCallback_nav_msg_odom(const nav_msgs::Odometry::ConstPtr &msg){    
    
    if (tracking_camera == false){
        odom_info = *msg;
        odom_received = true;
    }

    // The following is necessary because the tracking camera publishes only a topic in respect to the camera_odom_frame 
    // but since this frame is at (0.16, 0, 0.205) at start up and not (0, 0, 0) we need the pose of the cam
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

void poly_traj_plan::poseCallback_geomtry_msg_pose(const geometry_msgs::PoseStamped::ConstPtr &msg){
    
    odom_info.header = msg->header;
    odom_info.pose.pose = msg->pose;    

    odom_received = true;
}

geometry_msgs::Pose poly_traj_plan::calculateMidpoint(const geometry_msgs::Pose& pose1, const geometry_msgs::Pose& pose2) {
    geometry_msgs::Pose midpoint;

    midpoint.position.x = (pose1.position.x + pose2.position.x) / 2;
    midpoint.position.y = (pose1.position.y + pose2.position.y) / 2;
    midpoint.position.z = (pose1.position.z + pose2.position.z) / 2;

    return midpoint;
}

void poly_traj_plan::drawMarkerArray(std::vector<nav_msgs::Odometry> waypoints, int color, int offset){
     
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
        marker.scale.x = 0.2;  // Increase the length of the arrow
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
            marker.color.r = 0.0;
            marker.color.g = 0.0; 
            marker.color.b = 1.0; 
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


int poly_traj_plan::run_navigation_node(){

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


bool poly_traj_plan::generate_trajectory() 
{
    ROS_INFO("Starting trajectory generation!");
    
    bool success = false;
    // get static odom:
    nav_msgs::Odometry odom_static; // -> to fly away from the drones current position
    odom_static.pose.pose.position.x = odom_info.pose.pose.position.x;
    odom_static.pose.pose.position.y = odom_info.pose.pose.position.y;
    odom_static.pose.pose.position.z = odom_info.pose.pose.position.z;
    odom_static.pose.pose.orientation.x = odom_info.pose.pose.orientation.x;
    odom_static.pose.pose.orientation.y = odom_info.pose.pose.orientation.y;
    odom_static.pose.pose.orientation.z = odom_info.pose.pose.orientation.z;
    odom_static.pose.pose.orientation.w = odom_info.pose.pose.orientation.w;

    // a=Kurve(1.5 sin(t),1.5 cos(t),0.1 t,t,-0,100)

    
    double fac = 0.05;
    int cntr = 0;

    while(cntr < 500)
    {
        
        // odom_static; -> to fly away from the drones current position
        traj_wp.pose.pose.position.x = 1.5 * sin(cntr * fac) + odom_static.pose.pose.position.x;
        traj_wp.pose.pose.position.y = 1.5 * cos(cntr * fac) + odom_static.pose.pose.position.y; 
        traj_wp.pose.pose.position.z = 0.1 * cntr * fac + odom_static.pose.pose.position.z;
        

        //Transform yaw from helix to Quaternions:
        tf2::Quaternion quaternion;
        quaternion.setRPY(0, 0, atan2(-1.5 * (sin(cntr * fac)), 1.5 * cos(cntr * fac)));

        traj_wp.pose.pose.orientation.x = quaternion.getX() + odom_static.pose.pose.orientation.x;
        traj_wp.pose.pose.orientation.y = quaternion.getY() + odom_static.pose.pose.orientation.y;
        traj_wp.pose.pose.orientation.z = quaternion.getZ() + odom_static.pose.pose.orientation.z;
        traj_wp.pose.pose.orientation.w = quaternion.getW() + odom_static.pose.pose.orientation.w;

        traj_vec.push_back(traj_wp);    
        cntr++;    
    }



 

    drawMarkerArray(traj_vec, 2, 0);
    // drawMAVTrajectoryMarkers();


    success = true; // for debugging
    return success;

}

void poly_traj_plan::send_vel_commands() {
    
    if(curr_state + 1 <= traj_vec.size()){  // + 1 because if not it sends one 0 0 0 pose...
        /* 
        cmd_vel.linear.x = traj_states[curr_state].velocity_W.x();
        cmd_vel.linear.y = traj_states[curr_state].velocity_W.y();
        cmd_vel.linear.z = traj_states[curr_state].velocity_W.z();
        cmd_vel.angular.x = traj_states[curr_state].angular_velocity_W.x();
        cmd_vel.angular.y = traj_states[curr_state].angular_velocity_W.y();
        cmd_vel.angular.z = traj_states[curr_state].angular_velocity_W.z();
        */

        cmd_pose.pose.position.x = traj_vec.at(curr_state).pose.pose.position.x;
        cmd_pose.pose.position.y = traj_vec.at(curr_state).pose.pose.position.y;
        cmd_pose.pose.position.z = traj_vec.at(curr_state).pose.pose.position.z;
        cmd_pose.pose.orientation.x = traj_vec.at(curr_state).pose.pose.orientation.x;
        cmd_pose.pose.orientation.y = traj_vec.at(curr_state).pose.pose.orientation.y;
        cmd_pose.pose.orientation.z = traj_vec.at(curr_state).pose.pose.orientation.z;
        cmd_pose.pose.orientation.w = traj_vec.at(curr_state).pose.pose.orientation.w;


        // Publish the command
        pose_pub.publish(cmd_pose);
        // vel_pub.publish(cmd_vel);


    }else{
        cmd_vel.linear.x = 0.0;
        cmd_vel.linear.y = 0.0;
        cmd_vel.linear.z = 0.0;
        cmd_vel.angular.x = 0.0;
        cmd_vel.angular.y = 0.0;
        cmd_vel.angular.z = 0.0;

        cmd_pose.pose.position.x = traj_states[traj_states.size()-1].position_W.x();
        cmd_pose.pose.position.y = traj_states[traj_states.size()-1].position_W.y();
        cmd_pose.pose.position.z = traj_states[traj_states.size()-1].position_W.z();
        cmd_pose.pose.orientation.x = traj_states[traj_states.size()-1].orientation_W_B.x();
        cmd_pose.pose.orientation.y = traj_states[traj_states.size()-1].orientation_W_B.y();
        cmd_pose.pose.orientation.z = traj_states[traj_states.size()-1].orientation_W_B.z();
        cmd_pose.pose.orientation.w = traj_states[traj_states.size()-1].orientation_W_B.w();

        pose_pub.publish(cmd_pose);
        // vel_pub.publish(cmd_vel);
        
    }
        curr_state++;
}


/******************** main() ******************/


int main(int argc, char** argv){
    
    ros::init(argc, argv, "traj_generator");
    ros::AsyncSpinner ich_spinne(1);
    ich_spinne.start();
    ros::NodeHandle node_handle("~");
    poly_traj_plan ptp(std::ref(node_handle));

    // run the navigation node and get the trajectory    
    int nav_func_checker = ptp.run_navigation_node();

    if (nav_func_checker == 0) ROS_INFO("Navigation succesfully");
    else if (nav_func_checker == -1 ){
        ROS_ERROR("Navigation error");
        return -1;
    }     
    
    ptp.sampling_interval = 0.5;
    while(ros::ok()){
        
        ptp.send_vel_commands();

        ros::Duration(ptp.sampling_interval).sleep();
    }
    
    


    return 0;

}


