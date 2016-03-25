#include "ros/ros.h"
#include "Rviz_visual.h"
#include "time.h"
#include "../include/nostop_rviz_visual/Rviz_visual.h"

using namespace std;
using namespace Robotics;
using namespace Robotics::GameTheory;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "rviz_visual");
	ros::NodeHandle l_node("~");
        std::string robot_name;
	l_node.getParam("robot_name",robot_name);
	Robotics::GameTheory::Rviz_visual rviz_visual(std::string& robot_name);
	
	//ros::spin();
	
	while (l_node.ok())
	{
          //rviz_visual.odometry_publish();
	  ros::spinOnce();
	}
	//l_node.shutdown();
	return 0;
}