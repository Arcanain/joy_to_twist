/*
 * ********************************************************************************
 * SYSTEM            | obstacle aboidance
 * Publisher         | cmd_vel_pub
 * Subscriber        | state_sub
 *                   | cmd_vel_joystick_sub
 *                   | cmd_vel_obstacle_avoidance_sub
 * ********************************************************************************
*/
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_datatypes.h>
#include <std_msgs/Int8.h>

ros::Publisher cmd_vel_pub;
ros::Subscriber state_sub;
ros::Subscriber cmd_vel_joystick_sub;
ros::Subscriber cmd_vel_obstacle_avoidance_sub;

geometry_msgs::Twist cmd_vel;
geometry_msgs::Twist cmd_vel_joystick;
geometry_msgs::Twist cmd_vel_obstacle_avoidance;

void cmd_vel_joystick_callback(const geometry_msgs::Twist::ConstPtr &cmd_vel)
{
    cmd_vel_joystick = *cmd_vel;
}

void cmd_vel_obstacle_avoidance_callback(const geometry_msgs::Twist::ConstPtr &cmd_vel)
{
    cmd_vel_obstacle_avoidance = *cmd_vel;
}

void state_obstacle_avoidance_callback(const std_msgs::Int8::ConstPtr &state)
{
    /* 
       state = 0 right obstacle
       state = 1 left obstracle
       state = 2 no obstracle detection
    */
    if (state->data == 0) {
        cmd_vel.linear.x  = cmd_vel_obstacle_avoidance.linear.x;
		cmd_vel.angular.z = cmd_vel_obstacle_avoidance.angular.z;
    } else if (state->data == 1) {
        cmd_vel.linear.x  = cmd_vel_obstacle_avoidance.linear.x;
		cmd_vel.angular.z = cmd_vel_obstacle_avoidance.angular.z;
    } else if (state->data == 2) {
        cmd_vel.linear.x  = cmd_vel_joystick.linear.x;
		cmd_vel.angular.z = cmd_vel_joystick.angular.z;
    }

    cmd_vel_pub.publish(cmd_vel);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "safety");

    ros::NodeHandle nh;
    state_sub                      = nh.subscribe("/state_obstacle_avoidance", 10, state_obstacle_avoidance_callback);
    cmd_vel_joystick_sub           = nh.subscribe("/cmd_vel_joystick", 100, cmd_vel_joystick_callback);
    cmd_vel_obstacle_avoidance_sub = nh.subscribe("/cmd_vel_obstacle_avoidance", 100, cmd_vel_obstacle_avoidance_callback);

    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    ros::spin();

    return 0;
}