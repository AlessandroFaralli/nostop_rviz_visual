#include <ros/ros.h>
#include <nostop_rviz_visual/marker_positionConfig.h>
#include <dynamic_reconfigure/server.h>
#include <dynamic_reconfigure/Reconfigure.h>
#include <dynamic_reconfigure/Config.h>
#include "visualization_msgs/Marker.h"
#include <cv.h>

visualization_msgs::Marker marker;
bool marker_ready(false);

void positioning_callback(nostop_rviz_visual::marker_positionConfig  &config, uint32_t level)
{
	marker.header.frame_id = "blue_red/odom";
	marker.header.stamp = ros::Time::now();
	marker.ns = "marker";
	marker.id = config.ID;
	marker.type = visualization_msgs::Marker::CUBE;
	marker.action = visualization_msgs::Marker::ADD;
	marker.pose.position.x = config.xW;
	marker.pose.position.y = config.yW;
	marker.pose.position.z = 0;
	marker.pose.orientation.w = 1;
	marker.pose.orientation.x = 0;
	marker.pose.orientation.y = 0;
	marker.pose.orientation.z = 0;
	//marker.lifetime = 0;
	marker.scale.x = 0.1;
	marker.scale.y = 0.1;
	marker.scale.z = 0.1;
	marker.color.a = 1.0; // Don't forget to set the alpha!
	marker.color.r = 0.5;
	marker.color.g = 0.5;
	marker.color.b = 0.5;
	if(config.positionated == 1)
	{	
		marker_ready = true;
	}
}


int main(int argc,char **argv)
{

	ros::init(argc, argv, "rviz_marker_node"); 
	ROS_INFO("FIXED MARKER: ON");
	//DINAMYC RECONFIGURE
	dynamic_reconfigure::Server<nostop_rviz_visual::marker_positionConfig> marker_position;
	dynamic_reconfigure::Server<nostop_rviz_visual::marker_positionConfig>::CallbackType callback;
	callback = boost::bind(&positioning_callback,_1,_2);
	marker_position.setCallback(callback);	

	ros::NodeHandle n("~");
	std::string robot_name;
	ros::Publisher pub;
	n.getParam("robot_name",robot_name);
	pub = n.advertise<visualization_msgs::Marker>("/markers",2);
	ros::Rate r(50);


	std::vector<cv::Point2f> v;
	cv::Point2f p;
	p.x = 0;
	p.y = 0;
	v.push_back(p);
	p.x = 2;
	p.y = 0;
	v.push_back(p);
	p.x = 2;
	p.y = 1.5;
	v.push_back(p);
	p.x = 0;
	p.y = 1.5;
	v.push_back(p);
	
	while(ros::ok())
	{
	for (int i = 0;i<4;++i)
	{
		//ROS_INFO("Publishing marker %d",i+1);
		marker.header.frame_id = robot_name+"/odom";
		marker.header.stamp = ros::Time::now();
		marker.ns = "marker";
		marker.id = i;
		marker.type = visualization_msgs::Marker::CUBE;
		marker.action = visualization_msgs::Marker::ADD;
		marker.pose.position.x = v.at(i).x;
		marker.pose.position.y = v.at(i).y;
		marker.pose.position.z = 0;
		marker.pose.orientation.w = 1;
		marker.pose.orientation.x = 0;
		marker.pose.orientation.y = 0;
		marker.pose.orientation.z = 0;
		//marker.lifetime = 0;
		marker.scale.x = 0.1;
		marker.scale.y = 0.1;
		marker.scale.z = 0.1;
		marker.color.a = 1.0; // Don't forget to set the alpha!
		marker.color.r = 0.5;
		marker.color.g = 0.5;
		marker.color.b = 0.5;
		pub.publish(marker);
	}
}
	ros::spin();
//	while(ros::ok())
//	{
//		if(marker_ready)
//		{
//			pub.publish(marker);
//			marker_ready = false;
//			nostop_rviz_visual::marker_positionConfig configuration;
//			configuration.xW = 0;
//			configuration.yW = 0;
//			configuration.ID = marker.id+1;
//			configuration.positionated = 0;
//			marker_position.updateConfig(configuration);	
//		}
//		pub.publish(marker);
//		r.sleep();
//	}

}