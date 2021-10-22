cmake_minimum_required(VERSION 3.0.2)
project(joy_to_twist)

find_package(catkin REQUIRED
    geometry_msgs
    roscpp
    sensor_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES joy_to_twist
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(joy_to_twist src/joy_to_twist.cpp)
target_link_libraries(joy_to_twist ${catkin_LIBRARIES})

add_executable(safety src/safety.cpp)
target_link_libraries(safety ${catkin_LIBRARIES})