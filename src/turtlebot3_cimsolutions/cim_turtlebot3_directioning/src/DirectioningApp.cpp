#include <ros/ros.h>

#include "Odometry.h"
#include "Rotate.h"

#include <iostream>


int main(int argc, char **argv) {
  ros::init(argc, argv, "filter_velocity");

  directioner::Odometry odometry;

  std::cout << "WOLLAH" << std::endl;

  return 0;
}