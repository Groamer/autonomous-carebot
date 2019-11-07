#include "MapListener.h"
#include "ros/ros.h"

#include <iostream>

int main(int argc, char **argv) {
  ros::init(argc, argv, "cim_turtlebot3_mapping");

  mapper::MapListener mapListener;

  return 0;
}
