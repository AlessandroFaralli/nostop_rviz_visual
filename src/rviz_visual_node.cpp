#include "ros/ros.h"
#include "Rviz_visual.h"
#include "time.h"

using namespace std;
using namespace Robotics;
using namespace Robotics::GameTheory;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "rviz_visual");
	ros::NodeHandle l_node("~");
        std::string robot_name = "robot_name";
	l_node.getParam("robot_name",robot_name);
	Robotics::GameTheory::Rviz_visual rviz_visual;
	rviz_visual.initialize(robot_name);
	ros::spin();
	return 0;
}