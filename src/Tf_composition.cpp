#include "Tf_composition.h"

using namespace std;
using namespace Robotics;
using namespace Robotics::GameTheory;

Tf_composition::Tf_composition(std::string& robot_name):
m_robot_name(robot_name)
{
  m_robot_pose = m_tf_node.advertise<geometry_msgs::PoseWithCovariance>("/"+robot_name+"/localizer/integrated/pose",2);
  m_robot_twist = m_tf_node.advertise<geometry_msgs::TwistWithCovariance>("/"+robot_name+"/localizer/integrated/twist",2);
  m_robot_odometry_right_orientated = m_tf_node.advertise<nav_msgs::Odometry>("/"+robot_name+"/localizer/integrated/odometry",2);
  m_robot_odometry_final = m_tf_node.subscribe("/"+robot_name+"/localizer/odometry/final",10,&Tf_composition::odometry_subscribe,this);
}

Tf_composition::~Tf_composition()
{}

nav_msgs::Odometry Tf_composition::filtered_odometry_creation(const nav_msgs::Odometry::ConstPtr& msg,double& yaw)
{
	nav_msgs::Odometry output;
	output.child_frame_id = msg->child_frame_id;
	output.header.frame_id = msg->header.frame_id;
	output.header.stamp = ros::Time::now();
	output.pose = msg->pose;
	output.twist = msg->twist;
	tf::Quaternion quat;
	quat = tf::createQuaternionFromYaw(yaw);
	output.pose.pose.orientation.x = quat.x();
	output.pose.pose.orientation.y = quat.y();
	output.pose.pose.orientation.z = quat.z();
	output.pose.pose.orientation.w = quat.w();
	return output;
}



/////////////////////////////////////////////////////
void Tf_composition::odometry_subscribe(const nav_msgs::Odometry::ConstPtr& msg)
{
	try{
		m_listener_world2odom.lookupTransform("map", m_robot_name+"/odom", ros::Time(0), m_transform_world2odom);
		m_listener_odom2base_link.lookupTransform(m_robot_name+"/odom", m_robot_name+"/base_link", ros::Time(0), m_transform_odom2base_link);
		m_listener_world2base_link.lookupTransform("map", m_robot_name+"/base_link", ros::Time(0), m_transform_world2base_link);
// 		double yaw = real_yaw_calculation(m_transform_world2odom,m_transform_odom2base_link);
		tf::Quaternion l_quaternion = m_transform_world2base_link.getRotation();
		tf::Matrix3x3 m(l_quaternion);
		double roll, pitch, yaw;
		m.getRPY(roll, pitch, yaw);
		nav_msgs::Odometry l_integrated_odometry = filtered_odometry_creation(msg,yaw); 
		m_robot_pose.publish<geometry_msgs::PoseWithCovariance>(l_integrated_odometry.pose);
		m_robot_twist.publish<geometry_msgs::TwistWithCovariance>(l_integrated_odometry.twist);
		m_robot_odometry_right_orientated.publish<nav_msgs::Odometry>(l_integrated_odometry);
	}
	catch (tf::TransformException ex){
	  ROS_ERROR("%s",ex.what());
	  ros::Duration(1).sleep();
	}
}



/////////////////////////////////////////////////////
double Tf_composition::stampedTransform2yaw(tf::StampedTransform& transform)
{
	tf::Quaternion l_quaternion = transform.getRotation();
	tf::Matrix3x3 m(l_quaternion);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
	return yaw;
}



/////////////////////////////////////////////////////
double Tf_composition::real_yaw_calculation(tf::StampedTransform& world2odom, tf::StampedTransform& odom2base_link)
{
	double yaw_w_o = stampedTransform2yaw(world2odom);
	double yaw_o_bl = stampedTransform2yaw(odom2base_link);
	double yaw = yaw_w_o + yaw_o_bl;
	return yaw;
}