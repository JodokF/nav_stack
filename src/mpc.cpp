#include <casadi/casadi.hpp>
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <nav_msgs/Odometry.h>

// for the camera tf frame transformation:
#include <tf2_ros/transform_listener.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

using namespace casadi;

class mpc{

    private:

        void poseCallback_nav_msg_odom(const nav_msgs::Odometry::ConstPtr& msg);
        void poseCallback_geomtry_msg_pose(const geometry_msgs::PoseStamped::ConstPtr& msg);
        void vel_cmd_cb(const geometry_msgs::Twist::ConstPtr& msg);
        void pose_cmd_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);

        ros::Subscriber vel_cmd_sub;
        ros::Subscriber pose_cmd_sub;
        ros::Subscriber pose_sub_nav_msg_odom;
        ros::Subscriber pose_sub_geomtry_msg_pose;
        ros::Publisher cmd_vel_unstmpd_pub;

        nav_msgs::Odometry curr_pose_sim;
        geometry_msgs::PoseStamped curr_pose, curr_pose_temp;
        std::vector<geometry_msgs::PoseStamped> traj_vec;
        std::vector<geometry_msgs::Twist> vel_vec;

        geometry_msgs::Twist vel_cmd_in, vel_cmd_send;
        geometry_msgs::PoseStamped pose_cmd_in;

        // for the camera tf frame transformation:
        geometry_msgs::TransformStamped tf_odom_to_camera;
        tf2_ros::Buffer tf_buffer;
        tf2_ros::TransformListener tf_listener; 
        std::string target_frame, source_frame;

        /************************* MPC STUFF *************************/

        void assign_values();
        
        int pred_horz = 5;
        int mpc_iter_cntr;
        double dt, vel_threshold_lin, vel_threshold_ang; // = sampling interval from traj_generation.cpp

        std::vector<MX> x_ref;
        std::vector<MX> x_prd;
        std::vector<MX> veloc;
        DM x_ref_value;
        DM v_ref_value;
        DM x_init; // x, y, z, yaw
        DM x_constr; // -^- 
        DM v_constr; // v_x, v_y, v_z, v_yaw

        MX Q;
        MX R;
        MX opti_func;
        MX stage_cost;
        MX traj_error;
        Dict opts;
        

    public:
        void model_predictive_control();
        void send_vel_cmds_to_drone();
        bool tracking_camera, vel_cmd_received, pose_cmd_received, drone_pose_received, vel_anomalie_detected;

        mpc(ros::NodeHandle& nh);
        ~mpc();

};

mpc::mpc(ros::NodeHandle& nh)
        : tf_listener(tf_buffer, nh) 
{

    cmd_vel_unstmpd_pub = nh.advertise<geometry_msgs::Twist>
        ("/mavros/setpoint_velocity/cmd_vel_unstamped", 10);
    vel_cmd_sub = nh.subscribe<geometry_msgs::Twist>
        ("/vel_cmd_2_drone", 10, &mpc::vel_cmd_cb, this);
    pose_cmd_sub = nh.subscribe<geometry_msgs::PoseStamped>
        ("/pose_cmd_2_drone", 10, &mpc::pose_cmd_cb, this); // 19.2 Hz
    pose_sub_nav_msg_odom = nh.subscribe<nav_msgs::Odometry> 
        ("/mavros/odometry/out", 10, &mpc::poseCallback_nav_msg_odom, this);  // 19.2 Hz
        //("/camera/odom/sample_throttled", 10, &mpc::sim_pose_cb, this);  // = tracking cam
    pose_sub_geomtry_msg_pose = nh.subscribe<geometry_msgs::PoseStamped>
        ("/optitrack/pose", 10, &mpc::poseCallback_geomtry_msg_pose, this);  
        // ("/mavros/vision_pose/pose", 10, &mpc::real_pose_cb, this);  

        
        /************************* MPC STUFF *************************/
        dt = 0.2; 
        x_ref_value = DM(4, 1);
        v_ref_value = DM(4, 1);
        x_init = DM({1.0, 2.0, 3.0, 4.0});
        x_constr = DM({10, 10, 10, 99999});
        v_constr = DM({0.5, 0.5, 0.5, 0.5});
        Q = MX::eye(4);
        R = MX::eye(4);
        stage_cost = MX(0);
        traj_error = MX(0);
        mpc_iter_cntr = 0;
        opts["ipopt.print_level"] = 0; // Suppress Ipopt output

        pose_cmd_received = false;
        drone_pose_received = false;
        vel_cmd_received = false;
        tracking_camera = false;
        vel_anomalie_detected = false;

        // for debugging much to high...
        vel_threshold_lin = 50.0;
        vel_threshold_ang = 50.0;

    
}

mpc::~mpc()
{
    // To-Do
}

void mpc::poseCallback_nav_msg_odom(const nav_msgs::Odometry::ConstPtr& msg){
    
    if(tracking_camera == false){
        drone_pose_received = true;
        curr_pose_sim = *msg;
        curr_pose.header = curr_pose_sim.header;
        curr_pose.pose = curr_pose_sim.pose.pose;
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
            tf2::doTransform(curr_pose_temp, curr_pose, tf_odom_to_camera);
            drone_pose_received = true;    
        }
        else {
        ROS_WARN("Transform not available yet, waiting...");
        ros::Duration(1).sleep();
        }
    }
}

void mpc::poseCallback_geomtry_msg_pose(const geometry_msgs::PoseStamped::ConstPtr& msg){
    curr_pose = *msg;
    drone_pose_received = true;
}

void mpc::pose_cmd_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_cmd_in = *msg;
    traj_vec.push_back(pose_cmd_in);
    if(!pose_cmd_received) std::cout <<  
        "*************************************\n" <<
        "* Trajectory recived and reading... *\n" <<
        "*************************************\n";
    
    pose_cmd_received = true;  
}

void mpc::vel_cmd_cb(const geometry_msgs::Twist::ConstPtr& msg){
    vel_cmd_in = *msg;
    vel_vec.push_back(vel_cmd_in);

    vel_cmd_received = true;
}

void mpc::assign_values()
{
    // asign init 
    x_init(0) = curr_pose.pose.position.x;
    x_init(1) = curr_pose.pose.position.y;
    x_init(2) = curr_pose.pose.position.z;
    x_init(3) = 0.0; // I'll do this yaw shit later...

    // for debugging:
    /*
    pose_cmd_in.pose.position.x = 1.2;
    pose_cmd_in.pose.position.y = 1;
    pose_cmd_in.pose.position.z = 5;
    traj_vec.push_back(pose_cmd_in);    
    
    pose_cmd_in.pose.position.x = 1.3;
    pose_cmd_in.pose.position.y = 1;
    pose_cmd_in.pose.position.z = 5;
    traj_vec.push_back(pose_cmd_in);  
    
    pose_cmd_in.pose.position.x = 1.4;
    pose_cmd_in.pose.position.y = 1;
    pose_cmd_in.pose.position.z = 5;
    traj_vec.push_back(pose_cmd_in);  
    
    pose_cmd_in.pose.position.x = 1.5;
    pose_cmd_in.pose.position.y = 1;
    pose_cmd_in.pose.position.z = 5;
    traj_vec.push_back(pose_cmd_in);  

    pose_cmd_in.pose.position.x = 1.6;
    pose_cmd_in.pose.position.y = 1;
    pose_cmd_in.pose.position.z = 5;
    traj_vec.push_back(pose_cmd_in);  
    */

}

void mpc::model_predictive_control(){

    // initialize this hear so it gets cleared bevore every iteration...
    Opti opti; 
    opti_func = MX(0);

    assign_values();

    std::cout << "Number of recived traj. wp.: " << traj_vec.size() << " <<<\n";
    
    for (int k = 0; k < pred_horz; ++k) {
        
        x_prd.push_back(opti.variable(4, 1));  
        veloc.push_back(opti.variable(4, 1));  
        x_ref.push_back(opti.parameter(4, 1)); 
        
        x_ref_value(0, 0) = traj_vec.at(k + mpc_iter_cntr).pose.position.x; 
        x_ref_value(1, 0) = traj_vec.at(k + mpc_iter_cntr).pose.position.y; 
        x_ref_value(2, 0) = traj_vec.at(k + mpc_iter_cntr).pose.position.z; 
        x_ref_value(3, 0) = 0; // I'll do this yaw shit later...  
        // set traejctory pose reference
        opti.set_value(x_ref.at(k), x_ref_value); 

        // uncomment later to simplify things...
        //v_ref_value(0, 0) = vel_vec.at(k + mpc_iter_cntr).linear.x;
        //v_ref_value(1, 0) = vel_vec.at(k + mpc_iter_cntr).linear.y;
        //v_ref_value(2, 0) = vel_vec.at(k + mpc_iter_cntr).linear.z;
        //v_ref_value(3, 0) = 0; // I'll do this yaw shit later...  
        // set initial guess for the velocity
        //opti.set_initial(veloc.at(k), v_ref_value);

        // Enforce initial condition
        if (k == 0) opti.subject_to(x_prd.at(k) == x_init);  

        // Define the dynamics: x_{k+1} = x_k + dt * v_k
        if (0 < k && k < pred_horz) opti.subject_to(x_prd.at(k) == x_prd.at(k - 1) + dt * veloc.at(k - 1));

        traj_error = x_prd.at(k) - x_ref.at(k);

        // calculating the quadratic sum of the errors or somthing like this
        // J(x) = Sum((x(k).T)*Q*x(k)+v(k)*R*v(k))
        stage_cost = mtimes(traj_error.T(), mtimes(Q, traj_error)) + mtimes(veloc.at(k).T(), mtimes(R, veloc.at(k)));
        opti_func = opti_func + stage_cost;
        // std::cout << "stage_cost size: " << stage_cost.size() <<"\n";

        // constraints (for debugging commented)
        //opti.subject_to(opti.bounded(-x_constr, x_prd.at(k), x_constr));  
        //opti.subject_to(opti.bounded(-v_constr, veloc.at(k), v_constr));   

    }

    opti.minimize(opti_func);

    opti.solver("ipopt", opts);
        
    OptiSol sol = opti.solve();

    std::cout << std::fixed << std::showpoint << std::setprecision(3);
    std::cout << "\n---\nThis is the fucking velocity: " << sol.value(veloc.at(0));
    std::cout << "\nThis is the fucking reference: " << sol.value(x_ref.at(0));
    std::cout << "\nThis is the fucking position: " << sol.value(x_prd.at(0)) << "\n---\n";

    vel_cmd_send.linear.x = static_cast<double>(sol.value(veloc.at(0)(0, 0)));
    vel_cmd_send.linear.y = static_cast<double>(sol.value(veloc.at(0)(1, 0)));
    vel_cmd_send.linear.z = static_cast<double>(sol.value(veloc.at(0)(2, 0)));
    vel_cmd_send.angular.z = 0; // static_cast<double>(sol.value(veloc.at(0)(3, 0)));
    
    std::cout << "\nValue send: " << vel_cmd_send << "\n---\n";
    


    // to cycle through the whole trajectory reference vector as the mpc continues 
    mpc_iter_cntr++;

    // clearing the vectors for the next run
    x_prd.clear();
    veloc.clear();
    x_ref.clear();

}

 void mpc::send_vel_cmds_to_drone(){
/*
    std::cout << std::fixed << std::showpoint << std::setprecision(5);
    std::cout   << "Vel. send lin. & yaw: (" 
                << vel_cmd_send.linear.x << ", "
                << vel_cmd_send.linear.y << ", "
                << vel_cmd_send.linear.z << ") - "
                << vel_cmd_send.angular.z;
*/   

    // if the calculatet velocity is under the vel_threshold -> publish it
    // if not -> change all velocities to zero and publish it
    if (vel_cmd_send.linear.x >  vel_threshold_lin ||
        vel_cmd_send.linear.x < -vel_threshold_lin ||
        vel_cmd_send.linear.y >  vel_threshold_lin ||
        vel_cmd_send.linear.y < -vel_threshold_lin ||
        vel_cmd_send.linear.z >  vel_threshold_lin ||
        vel_cmd_send.linear.z < -vel_threshold_lin ||
        vel_cmd_send.angular.x >  vel_threshold_ang ||
        vel_cmd_send.angular.x < -vel_threshold_ang ||
        vel_cmd_send.angular.y >  vel_threshold_ang || // actually this should be always zero, right?
        vel_cmd_send.angular.y < -vel_threshold_ang || // actually this should be always zero, right?
        vel_cmd_send.angular.z >  vel_threshold_ang || // actually this should be always zero, right?
        vel_cmd_send.angular.z < -vel_threshold_ang || // actually this should be always zero, right?
        vel_anomalie_detected == true)
    {
            ROS_ERROR("Velocitie anomalie detected! Sending Velocity ZERO!\n");
            vel_anomalie_detected = true;
            vel_cmd_send.linear.x = 0.0;
            vel_cmd_send.linear.y = 0.0;
            vel_cmd_send.linear.z = 0.0;
            vel_cmd_send.angular.x = 0.0;
            vel_cmd_send.angular.y = 0.0;
            vel_cmd_send.angular.z = 0.0;
    }
    
    cmd_vel_unstmpd_pub.publish(vel_cmd_send);

}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "model_predictive_control");

    ros::NodeHandle node_handle("~");
    ros::AsyncSpinner ich_spinne(1);
    ros::Rate rate40(40);
    ros::Rate rate3(3);
    ich_spinne.start();

    mpc mpc(std::ref(node_handle));

    //mpc.pose_cmd_received = true; // for debugging
    while(ros::ok()){
        if (mpc.pose_cmd_received && mpc.drone_pose_received){
            // std::cout << "Press Enter to continue..." << std::endl;
            // std::cin.get();  // Waits for the user to press Enter
            // std::cout << "Continuing execution..." << std::endl;

            while(ros::ok()){  
                    ROS_INFO("Calculating Velocities with MPC...\n");
                    mpc.model_predictive_control();
                    mpc.send_vel_cmds_to_drone();
                    rate40.sleep();
            }
        }
        else rate3.sleep();
        ROS_INFO("Waiting for drone pose and command...\n");
    }


return 0;

}



