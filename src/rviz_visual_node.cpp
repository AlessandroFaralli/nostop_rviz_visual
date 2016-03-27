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
	
	// param settings
        std::string robot_name,world_frame_id;
	double duration,x_scale_factor,y_scale_factor,z_scale_factor,R_color,G_color,B_color;
	std::vector<double> scale_factor, arrow_color;
	l_node.param<std::string>("robot_name",robot_name,"robot_name");
	l_node.param<std::string>("world_frame_id",world_frame_id,"SR_world");
	l_node.param<double>("arrow_lifetime",duration,10);
	l_node.param<double>("x_scale_factor",x_scale_factor,0.5);
	scale_factor.push_back(x_scale_factor);
	l_node.param<double>("y_scale_factor",y_scale_factor,0.05);
	scale_factor.push_back(y_scale_factor);
	l_node.param<double>("z_scale_factor",z_scale_factor,0.05);
	scale_factor.push_back(z_scale_factor);
	l_node.param<double>("R_color",R_color,0.5);
	arrow_color.push_back(R_color);
	l_node.param<double>("G_color",G_color,0.5);
	arrow_color.push_back(G_color);
	l_node.param<double>("B_color",B_color,0.5);
	arrow_color.push_back(B_color);
	ros::Duration lifetime(duration);
	
	// visual object
	Robotics::GameTheory::Rviz_visual rviz_visual;
	rviz_visual.initialize(robot_name,lifetime,scale_factor,arrow_color,world_frame_id);
	
	ros::spin();
	return 0;
}