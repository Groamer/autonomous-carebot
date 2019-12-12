#include <iostream>
#include <ros/ros.h>
#include <costmap_2d/costmap_2d.h>
#include <geometry_msgs/Twist.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <nav_msgs/GridCells.h>
#include <nav_msgs/MapMetaData.h>
#include <nav_msgs/OccupancyGrid.h>
#include <std_msgs/Header.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

static void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg){
  int x = msg->info.width;
  int y = msg->info.height;

  while(x > 0 || y > 0) {
    int index = x + msg->info.width * y;
    int value = msg->data[index];

    if(value == 0) {
      //vrije spot gevonden
      //navigeer hiernaartoe
    }

    x --;
    y --;
  }

  std::cout << "CYKA!" << std::endl;
}

void checkerdecheck() {
  /*costmap_2d::Costmap2D map();

  char bruh = costmap_2d::costLookUp(1, 1, 1, 1);

  ROS_INFO("kek!");*/

  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("map", 1, mapCallback);
  ros::spin();
}

int main(int argc, char** argv){
  ros::init(argc, argv, "cim_turtlebot3_localization");

  checkerdecheck();

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = 20.0;
  goal.target_pose.pose.position.y = -20.0;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");

  return 0;
}