#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>



nav_msgs::Odometry odometry_msg_creation(std::string& robot_name)
{
  nav_msgs::Odometry msg;
  msg.header.stamp = ros::Time::now();
  msg.header.frame_id = "SR_world";
  msg.child_frame_id = robot_name+"/base_link";
  msg.pose.pose.position.x = sin(ros::Time::now().toSec());
  msg.pose.pose.position.y = cos(ros::Time::now().toSec());
  tf::Quaternion l_quat = tf::createQuaternionFromYaw(atan2(msg.pose.pose.position.y,msg.pose.pose.position.x));
  msg.pose.pose.orientation.w = l_quat.getW();
  msg.pose.pose.orientation.x = l_quat.getX();
  msg.pose.pose.orientation.y = l_quat.getY();
  msg.pose.pose.orientation.z = l_quat.getZ();
  return msg;
}

void tf_publishing(geometry_msgs::TransformStamped& marker_tf,tf::TransformBroadcaster& tf_broadcasters,nav_msgs::Odometry msg,std::string robot_name)
{

      // publish over /tf
      marker_tf.header.stamp = ros::Time::now();
      marker_tf.header.frame_id = "SR_world";
      marker_tf.child_frame_id = robot_name+"/base_link";
      marker_tf.transform.translation.x = 0.0;
      marker_tf.transform.translation.y = 0.0;
      marker_tf.transform.translation.z = 0.5;
      marker_tf.transform.rotation.w = msg.pose.pose.orientation.w;
      marker_tf.transform.rotation.x = msg.pose.pose.orientation.x;
      marker_tf.transform.rotation.y = msg.pose.pose.orientation.y;
      marker_tf.transform.rotation.z = msg.pose.pose.orientation.z;
      tf_broadcasters.sendTransform(marker_tf);
}

int main(int argc,char **argv)
{
  ros::init(argc,argv,"test_node");
  geometry_msgs::TransformStamped marker_tf;
  tf::TransformBroadcaster tf_broadcasters;
  ros::Publisher odometry_pub;
  ros::NodeHandle test_node("~");
  std::string robot_name;
  robot_name = "robot_name";
  test_node.getParam("robot_name",robot_name);
  odometry_pub = test_node.advertise<nav_msgs::Odometry>("/"+robot_name+"/localizer/odometry/final",10);
  ROS_INFO("TEST ON");
  ros::Rate r(50);
  while (ros::ok())
  {
	nav_msgs::Odometry msg = odometry_msg_creation(robot_name);
	tf_publishing(marker_tf,tf_broadcasters, msg,robot_name);
	odometry_pub.publish<nav_msgs::Odometry>(msg);
	ros::spinOnce();
	r.sleep();
  }
  return 0;

}