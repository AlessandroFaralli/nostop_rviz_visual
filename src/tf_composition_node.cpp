#include "ros/ros.h"
#include "Tf_composition.h"


int main(int argc,char **argv)
{
	ROS_INFO("TF composition : ON");
	
	ros::init(argc, argv, "tf_composition_node"); 
	ros::NodeHandle n("~");
	std::string robot_name("robot_name_unsetted");
	n.getParam("robot_name",robot_name);
	Robotics::GameTheory::Tf_composition tf_composition(robot_name);
	ros::spin();
}