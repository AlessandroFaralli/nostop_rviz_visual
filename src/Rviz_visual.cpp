#include <ros/ros.h>
#include "Rviz_visual.h"
#include "visualization_msgs/Marker.h"


using namespace std;
using namespace Robotics;
using namespace Robotics::GameTheory;



Rviz_visual::Rviz_visual(){}


Rviz_visual::~Rviz_visual(){}

void Rviz_visual::initialize(std::string& robot_name)
{	
	m_robot_name = robot_name.c_str();
	m_rviz_sub = m_rviz_node.subscribe<nav_msgs::Odometry>("/"+m_robot_name+"/localizer/odometry/final",10,&Rviz_visual::final_odometry_readed,this);
// 	m_rviz_pub = m_rviz_node.advertise<nav_msgs::Odometry>("/"+robot_name+"/rviz_data",10);
	m_rviz_pub = m_rviz_node.advertise<visualization_msgs::Marker>("/"+m_robot_name+"/rviz_marker", 10 );
}

void Rviz_visual::final_odometry_readed(const nav_msgs::Odometry::ConstPtr& msg)
{
  Lock l_lock(m_mutex);
  //m_odometry.header.frame_id=msg.header.frame_id;
  marker_visualizer(msg);
//   m_rviz_pub.publish<nav_msgs::Odometry>();
}

void Rviz_visual::marker_visualizer(const nav_msgs::Odometry::ConstPtr& msg)
{	
	visualization_msgs::Marker marker;
	marker.header.frame_id = m_robot_name+"/base_link";
	marker.header.stamp = ros::Time::now();
	marker.ns = m_robot_name;
	marker.id = 0;
	marker.type = visualization_msgs::Marker::ARROW;
	marker.action = visualization_msgs::Marker::ADD;
	marker.pose.position = msg->pose.pose.position;
	marker.pose.orientation = msg->pose.pose.orientation;
	marker.scale.x = 1;
	marker.scale.y = 0.1;
	marker.scale.z = 0.1;
	marker.color.a = 1.0; // Don't forget to set the alpha!
	marker.color.r = 0.0;
	marker.color.g = 1.0;
	marker.color.b = 0.0;
	//only if using a MESH_RESOURCE marker type:
// 	marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
	m_rviz_pub.publish( marker );
}



// void Rviz_visual::odometry_publish(std::string& robot_name)
// {
//   m_rviz_pub.publish<nav_msgs::Odometry>(m_odometry);
// }