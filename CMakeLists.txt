cmake_minimum_required(VERSION 3.0.2)
project(nav_stack)

find_package(Eigen3 REQUIRED)
find_package(catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_msgs
    tf2
    tf2_ros
    nav_msgs
)

catkin_package( 
                CATKIN_DEPENDS 
                roscpp 
                std_msgs 
                geometry_msgs
                # hector_uav_msgs
                
)

# Add include directories
include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include   # Add this line to include the directory containing traj_gen.h
    # Add any other include directories here
)

add_executable(traj_generation src/traj_generation.cpp)
add_dependencies(traj_generation ${catkin_EXPORTED_TARGETS})
target_link_libraries(traj_generation ${catkin_LIBRARIES})# Eigen3::Eigen)


add_executable(drone_connection src/drone_connection.cpp)
# add_dependencies(drone_connection ${catkin_EXPORTED_TARGETS})
target_link_libraries(drone_connection ${catkin_LIBRARIES})# Eigen3::Eigen)

