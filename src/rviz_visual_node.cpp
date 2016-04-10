#include "ros/ros.h"
#include <urdf/model.h>
#include "Rviz_visual.h"
#include "time.h"


// #include <collada_urdf/collada_urdf.h>
// #include <collada_parser/collada_parser.h>
//  #include <collada_parser/collada_parser_plugin.h>
//  
 
using namespace std;
using namespace Robotics;
using namespace Robotics::GameTheory;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "rviz_visual");
	ros::NodeHandle l_node("~");
	
	
	////TEST
// 	boost::shared_ptr<DAE> dom;
// 	if (!collada_urdf::colladaFromUrdfFile("/home/niko/catkin_ws/src/nostop/nostop_launch_files/urdf/model.urdf", dom)) {
// 	    ROS_ERROR("Failed to construct COLLADA DOM");
// 	    return false;
// 	}
// 	collada_urdf::colladaToFile(dom, "~/filename.dae");
// 
// 	

	// param settings
        std::string robot_name,world_frame_id;
	int frequency;
	double duration,x_scale_factor,y_scale_factor,z_scale_factor,R_color,G_color,B_color;
	std::vector<double> scale_factor, arrow_color;
	l_node.param<int>("frequency",frequency,5);
	l_node.param<std::string>("robot_name",robot_name,"robot_name");
	l_node.param<std::string>("world_frame_id",world_frame_id,"map");
	l_node.param<double>("arrow_lifetime",duration,10);
	l_node.param<double>("x_scale_factor",x_scale_factor,0.5);
	scale_factor.push_back(x_scale_factor);
	l_node.param<double>("y_scale_factor",y_scale_factor,0.05);
	scale_factor.push_back(y_scale_factor);
	l_node.param<double>("z_scale_factor",z_scale_factor,0.05);
	scale_factor.push_back(z_scale_factor);
	l_node.param<double>("R_color_value",R_color,0.5);
	arrow_color.push_back(R_color);
	l_node.param<double>("G_color_value",G_color,0.5);
	arrow_color.push_back(G_color);
	l_node.param<double>("B_color_value",B_color,0.5);
	arrow_color.push_back(B_color);
	ros::Duration lifetime(duration);
	
	// visual object
	Robotics::GameTheory::Rviz_visual rviz_visual;
	rviz_visual.initialize(robot_name,lifetime,scale_factor,arrow_color,world_frame_id);
	ros::Rate r(frequency);
	while(l_node.ok())
	{
	  rviz_visual.marker_publisher();
	  ros::spinOnce();
	  r.sleep();
	}
	return 0;
}