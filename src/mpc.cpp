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

        nav_msgs::Odometry curr_pose_sim;
        geometry_msgs::PoseStamped curr_pose, curr_pose_temp;
        std::vector<geometry_msgs::PoseStamped> traj_vec;

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
        double dt = 0.1;

        std::vector<MX> x_ref;
        std::vector<MX> x_prd;
        std::vector<MX> veloc;
        DM x_ref_value;
        DM x_init; // x, y, z, yaw
        DM x_constr; // -^- 
        DM v_constr; // v_x, v_y, v_z, v_yaw

        MX Q;
        MX R;
        MX opti_func;
        MX stage_cost;
        MX traj_error;
        Dict opts;
        Opti opti;
        


    public:
        void model_predictive_control();
        bool tracking_camera, vel_cmd_received, pose_cmd_received, drone_pose_received, vel_anomalie_detected;

        mpc(ros::NodeHandle& nh);
        ~mpc();

};

mpc::mpc(ros::NodeHandle& nh)
        : tf_listener(tf_buffer, nh) 
{

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
        x_ref_value = DM(4, 1);
        x_init = DM({1.0, 2.0, 3.0, 4.0});
        x_constr = DM({10, 10, 10, 99999});
        v_constr = DM({0.5, 0.5, 0.5, 0.5});
        Q = MX::eye(4);
        R = MX::eye(4);
        opti_func = MX(0);
        stage_cost = MX(0);
        traj_error = MX(0);
        mpc_iter_cntr = 0;
        opts["ipopt.print_level"] = 0; // Suppress Ipopt output
    
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
    
    pose_cmd_received = true;  
}

void mpc::vel_cmd_cb(const geometry_msgs::Twist::ConstPtr& msg){
    vel_cmd_in = *msg;
    vel_cmd_received = true;
}

void mpc::assign_values()
{
    // asign init 
    x_init(0) = 1.25;//curr_pose.pose.position.x;
    x_init(1) = 1.3;//curr_pose.pose.position.y;
    x_init(2) = 25;//curr_pose.pose.position.z;
    x_init(3) = 0.0; // I'll do this yaw shit later...

    // for debugging:

    pose_cmd_in.pose.position.x = 1.2;
    pose_cmd_in.pose.position.y = 1.2;
    pose_cmd_in.pose.position.z = 2;
    traj_vec.push_back(pose_cmd_in);    
    
    pose_cmd_in.pose.position.x = 1.3;
    pose_cmd_in.pose.position.y = 1.3;
    pose_cmd_in.pose.position.z = 2;
    traj_vec.push_back(pose_cmd_in);  
    
    pose_cmd_in.pose.position.x = 1.4;
    pose_cmd_in.pose.position.y = 1.4;
    pose_cmd_in.pose.position.z = 2;
    traj_vec.push_back(pose_cmd_in);  
    
    pose_cmd_in.pose.position.x = 1.5;
    pose_cmd_in.pose.position.y = 1.5;
    pose_cmd_in.pose.position.z = 2;
    traj_vec.push_back(pose_cmd_in);  

    pose_cmd_in.pose.position.x = 1.6;
    pose_cmd_in.pose.position.y = 1.6;
    pose_cmd_in.pose.position.z = 2;
    traj_vec.push_back(pose_cmd_in);  

}

void mpc::model_predictive_control(){

    assign_values();
    
    for (int k = 0; k < pred_horz; ++k) {
        
        x_ref_value(0, 0) = traj_vec.at(k + mpc_iter_cntr).pose.position.x; 
        x_ref_value(1, 0) = traj_vec.at(k + mpc_iter_cntr).pose.position.y; 
        x_ref_value(2, 0) = traj_vec.at(k + mpc_iter_cntr).pose.position.z; 
        x_ref_value(3, 0) = 0; // I'll do this yaw shit later...  

        x_prd.push_back(opti.variable(4, 1));  
        veloc.push_back(opti.variable(4, 1));  
        x_ref.push_back(opti.parameter(4, 1)); 

        if (k == 0) opti.set_initial(x_prd.at(k), x_init);
    
        // Define the dynamics: x_{k+1} = x_k + dt * v_k
        if (0 < k && k < pred_horz - 1) opti.subject_to(x_prd.at(k) == x_prd.at(k - 1) + dt * veloc.at(k - 1));

        // set traejctory pose reference
        opti.set_value(x_ref.at(k), x_ref_value); 
        
        traj_error = x_prd.at(k) - x_ref.at(k);
        // calculating the quadratic sum of the errors or somthing like this
        // J(x) = Sum((x(k).T)*Q*x(k)+v(k)*R*v(k))
        stage_cost = mtimes(traj_error.T(), mtimes(Q, traj_error)) + mtimes(veloc.at(k).T(), mtimes(R, veloc.at(k)));
        opti_func = opti_func + stage_cost;
        std::cout << "stage_cost size: " << stage_cost.size() <<"\n";

        // constraints
        opti.subject_to(opti.bounded(-x_constr, x_prd.at(k), x_constr));  
        opti.subject_to(opti.bounded(-v_constr, veloc.at(k), v_constr));   


    }

    std::cout << "\n***\nOptimization function size: " << opti_func.size() <<"\n";

    opti.minimize(opti_func);

    opti.solver("ipopt", opts);
        
    OptiSol sol = opti.solve();

    std::cout << "\n---\nThis is the fucking solution: " << sol.value(veloc.at(0)) << "\n---\n";

    mpc_iter_cntr += 4;

}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "model_predictive_control");

    ros::NodeHandle node_handle("~");
    ros::AsyncSpinner ich_spinne(1);
    ros::Rate rate40(40);
    ich_spinne.start();

    mpc mpc(std::ref(node_handle));

    //mpc.pose_cmd_received = true; // for debugging
    // if (mpc.pose_cmd_received == true)
    mpc.model_predictive_control();
    
    /*
    while(ros::ok()){  
            ROS_INFO("Calculating Velocities with MPC...\n");
            mpc.model_predictive_control();
            //mpc.send_vel_cmds_to_drone();
            rate40.sleep();
        }
    */

return 0;

}



