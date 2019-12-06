#include <ros/ros.h>
#include "MapListener.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "cim_turtlebot3_mapping_listener");

  mapper::MapListener::listen();

  return 0;
}