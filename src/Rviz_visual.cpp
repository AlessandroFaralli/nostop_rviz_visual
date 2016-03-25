#include <ros/ros.h>
#include "Rviz_visual.h"



using namespace std;
using namespace Robotics;
using namespace Robotics::GameTheory;



Rviz_visual::Rviz_visual(std::string& robot_name)
{
	m_rviz_sub = m_rviz_node.subscribe<nav_msgs::Odometry>("/"+robot_name+"/localizer/odometry/final",10,&Rviz_visual::final_odometry_readed,this);
	m_rviz_pub = m_rviz_node.advertise<nav_msgs::Odometry>("/"+robot_name+"/rviz_data",10);
}


Rviz_visual::~Rviz_visual(){}



void Rviz_visual::final_odometry_readed(nav_msgs::Odometry msg)
{
  Lock l_lock(m_mutex);
  //m_odometry.header.frame_id=msg.header.frame_id;
  m_rviz_pub.publish<nav_msgs::Odometry>(msg);
}

// void Rviz_visual::odometry_publish(std::string& robot_name)
// {
//   m_rviz_pub.publish<nav_msgs::Odometry>(m_odometry);
// }