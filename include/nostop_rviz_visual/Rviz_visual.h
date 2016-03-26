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


namespace Robotics 
{	
	namespace GameTheory
	{
		class Rviz_visual
		{
			ros::NodeHandle m_rviz_node;
			ros::Subscriber m_rviz_sub;
			ros::Publisher m_rviz_pub;
                        Mutex m_mutex;
			std::string m_robot_name;
			nav_msgs::Odometry m_odometry;

		public:
			Rviz_visual(); 
			void final_odometry_readed(const nav_msgs::Odometry::ConstPtr& msg);
			void odometry_publish();
			void initialize(std::string& robot_name);
			void marker_visualizer(const nav_msgs::Odometry::ConstPtr& msg);
			~Rviz_visual(); 
		};

	}
}


#endif // RVIZ_VISUAL_H