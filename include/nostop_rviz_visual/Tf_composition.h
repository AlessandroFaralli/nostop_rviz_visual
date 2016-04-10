////////////////////////////////////////////////////////////
//	Tf_composition.h
//	Created on:	10-Apr-2016
//	Original author: Niko Giovannini Alessandro Faralli
////////////////////////////////////////////////////////////
#ifndef TF_COMPOSITION
#define TF_COMPOSITION
#pragma once
#include <ros/node_handle.h>
#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>

namespace Robotics 
{
	namespace GameTheory
	{	
	  
	class Tf_composition
	{
		 ros::NodeHandle m_tf_node;
		 tf::TransformListener m_listener_world2odom,m_listener_odom2base_link,m_listener_world2base_link;
		 tf::StampedTransform m_transform_world2odom,m_transform_odom2base_link,m_transform_world2base_link;
		 ros::Publisher m_robot_pose,m_robot_twist,m_robot_odometry_right_orientated;
		 ros::Subscriber m_robot_odometry_final;
		 std::string m_robot_name;
		 
		
	public:
		  Tf_composition(std::string& robot_name);
		  ~Tf_composition();
		  nav_msgs::Odometry filtered_odometry_creation(const nav_msgs::Odometry::ConstPtr& msg,double& yaw);
		  void odometry_subscribe(const nav_msgs::Odometry::ConstPtr& msg);
		  double stampedTransform2yaw(tf::StampedTransform& transform);
		  double real_yaw_calculation(tf::StampedTransform& world2odom,tf::StampedTransform& odom2base_link);
		};

	}
}


#endif // TF_COMPOSITION
