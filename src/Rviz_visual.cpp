#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include "Rviz_visual.h"


using namespace std;
using namespace Robotics;
using namespace Robotics::GameTheory;



Rviz_visual::Rviz_visual(){}


Rviz_visual::~Rviz_visual(){}

void Rviz_visual::initialize(std::string& robot_name,ros::Duration& lifetime,
			     std::vector<double>& scale_factor,std::vector<double>& arrow_color,std::string& frame_id)
{	
	m_robot_name = robot_name.c_str();
	m_lifetime = lifetime;
	m_world_frame_id = frame_id;
	m_color_value = arrow_color;
	m_scale_factor = scale_factor;
	m_rviz_odom_sub = m_rviz_node.subscribe<nav_msgs::Odometry>("/"+m_robot_name+"/localizer/integrated/odometry",10,&Rviz_visual::marker_odom_setting,this);
	m_rviz_pub = m_rviz_node.advertise<visualization_msgs::Marker>("/"+m_robot_name+"/rviz_marker", 10 );
}


void Rviz_visual::marker_odom_setting(const nav_msgs::Odometry::ConstPtr& msg)
{	
	Lock l_lock(m_mutex);
	m_marker.header.frame_id = m_world_frame_id;
	m_marker.header.stamp = ros::Time::now();
	m_marker.ns = m_robot_name;
	m_marker.id = ros::Time::now().toNSec();
	m_marker.type = visualization_msgs::Marker::ARROW;
	m_marker.action = visualization_msgs::Marker::ADD;
	m_marker.pose.position.x = msg->pose.pose.position.x;
	m_marker.pose.position.y = msg->pose.pose.position.y;
	m_marker.pose.position.z = msg->pose.pose.position.z;
	m_marker.pose.orientation.w = msg->pose.pose.orientation.w;
	m_marker.pose.orientation.x = msg->pose.pose.orientation.x;
	m_marker.pose.orientation.y = msg->pose.pose.orientation.y;
	m_marker.pose.orientation.z = msg->pose.pose.orientation.z;
	m_marker.lifetime = m_lifetime;
	m_marker.scale.x = m_scale_factor.at(0);
	m_marker.scale.y = m_scale_factor.at(1);
	m_marker.scale.z = m_scale_factor.at(2);
	m_marker.color.a = 1.0; // Don't forget to set the alpha!
	m_marker.color.r = m_color_value.at(0);
	m_marker.color.g = m_color_value.at(1);
	m_marker.color.b = m_color_value.at(2);
	//only if using a MESH_RESOURCE marker type:
// 	m_marker.mesh_resource = "package://nostop_launch_files/urdf/roomba.dae";
// 	m_odom_marker = true;
}

// void Rviz_visual::marker_yaw_setting(const std_msgs::Float64::ConstPtr& msg)
// {	
// 	Lock l_lock(m_mutex);
// 	geometry_msgs::Quaternion l_quat;
// 	l_quat = tf::createQuaternionMsgFromYaw(msg->data);
// 	m_marker.pose.orientation.w = l_quat.w;
// 	m_marker.pose.orientation.x = l_quat.x;
// 	m_marker.pose.orientation.y = l_quat.y;
// 	m_marker.pose.orientation.z = l_quat.z;
// 	m_yaw_marker = true;
// }



void Rviz_visual::marker_publisher()
{
    Lock l_lock(m_mutex);
    m_rviz_pub.publish(m_marker);
   
}