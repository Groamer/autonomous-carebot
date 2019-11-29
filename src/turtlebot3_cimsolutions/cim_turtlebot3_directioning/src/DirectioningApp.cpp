#include <ros/ros.h>

#include "Odometry.h"
#include "Rotate.h"

#include <iostream>


int main(int argc, char **argv) {
  ros::init(argc, argv, "filter_velocity");

  /*ros::NodeHandle nodeHandle;
  ros::Rate rate(10);
  while(ros::ok()) {
    directioner::Odometry::getPosition();
    
    rate.sleep();
    ros::spinOnce();
  }*/

  directioner::Rotate::startRotating();

  directioner::Odometry odometry;

  std::cout << "WOLLAH" << std::endl;

  /*ros::AsyncSpinner spinner(4);
  std::cout << "WOLLAH" << std::endl;
  spinner.start();
  ros::waitForShutdown();*/

  return 0;
}