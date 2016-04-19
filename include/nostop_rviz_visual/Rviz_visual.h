////////////////////////////////////////////////////////////
//	Rviz_visual.h
//	Created on:	23-Mar-16
//	Original author: Niko Giovannini Alessandro Faralli
////////////////////////////////////////////////////////////
#ifndef RVIZ_VISUAL_H
#define RVIZ_VISUAL_H
#pragma once

#include "ros/ros.h"
#include <Threads.h>
#include <nav_msgs/Odometry.h>
#include "visualization_msgs/Marker.h"
#include <std_msgs/Float64.h>



namespace Robotics 
{	
	namespace GameTheory
	{
		class Rviz_visual
		{
			ros::NodeHandle m_rviz_node;
			ros::Subscriber m_rviz_odom_sub,m_rviz_yaw_sub;
			ros::Publisher m_rviz_pub;
            Mutex m_mutex;
			bool m_odom_marker,m_yaw_marker;
			std::string m_robot_name,m_world_frame_id;
			std::vector<double> m_scale_factor,m_color_value;
			ros::Duration m_lifetime;
			nav_msgs::Odometry m_odometry;
			visualization_msgs::Marker m_marker;

		public:
			Rviz_visual(); 
			void initialize(std::string& robot_name,ros::Duration& lifetime, 
					std::vector<double>& scale_factor,std::vector<double>& arrow_color,
					std::string& w_frame_id);
			void marker_odom_setting(const nav_msgs::Odometry::ConstPtr& msg);
			void marker_yaw_setting(const std_msgs::Float64::ConstPtr& msg);
			void marker_publisher();
			~Rviz_visual(); 
		};

	}
}


#endif // RVIZ_VISUAL_H