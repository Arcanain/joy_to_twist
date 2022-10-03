#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class JoyToTwist
{
private:
  ros::NodeHandle nh;
  ros::Publisher vel_pub;
  ros::Subscriber joy_sub;

public:
  JoyToTwist();
  void joyCallback(const sensor_msgs::Joy& joy);
};

JoyToTwist::JoyToTwist()
{
    joy_sub = nh.subscribe("/joy", 100, &JoyToTwist::joyCallback, this);
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_joystick", 100);
}

void JoyToTwist::joyCallback(const sensor_msgs::Joy& msg)
{
  if (msg.axes.size() != 8) {
    return;
  }
  
  geometry_msgs::Twist cmd_vel_joystick;

  cmd_vel_joystick.linear.x = msg.axes[1] * 0.25;
  // 無線の時
  //cmd_vel_joystick.angular.z = msg.axes[2] * 1.0;
  // 有線の時
  cmd_vel_joystick.angular.z = msg.axes[3] * 0.5;

  vel_pub.publish(cmd_vel_joystick);
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "joy_to_twist");
  JoyToTwist joytotwist;

  ros::spin();
}