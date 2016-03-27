#include <ros/ros.h>
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
	m_rviz_sub = m_rviz_node.subscribe<nav_msgs::Odometry>("/"+m_robot_name+"/localizer/odometry/final",10,&Rviz_visual::marker_visualizer,this);
	m_rviz_pub = m_rviz_node.advertise<visualization_msgs::Marker>("/"+m_robot_name+"/rviz_marker", 10 );
}


void Rviz_visual::marker_visualizer(const nav_msgs::Odometry::ConstPtr& msg)
{	
	Lock l_lock(m_mutex);
	m_marker.header.frame_id = m_world_frame_id;
	m_marker.header.stamp = ros::Time::now();
	m_marker.ns = m_robot_name;
	m_marker.id = ros::Time::now().toNSec();
	m_marker.type = visualization_msgs::Marker::ARROW;
	m_marker.action = visualization_msgs::Marker::ADD;
	m_marker.pose.orientation = msg->pose.pose.orientation;
	m_marker.lifetime = m_lifetime;
	m_marker.scale.x = m_scale_factor.at(0);
	m_marker.scale.y = m_scale_factor.at(1);
	m_marker.scale.z = m_scale_factor.at(2);
	m_marker.color.a = 1.0; // Don't forget to set the alpha!
	m_marker.color.r = m_color_value.at(0);
	m_marker.color.g = m_color_value.at(1);
	m_marker.color.b = m_color_value.at(2);
	//only if using a MESH_RESOURCE marker type:
// 	marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
	m_rviz_pub.publish( m_marker );
}
