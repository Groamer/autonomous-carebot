#include <ros/ros.h>
#include "MapLauncher.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "cim_turtlebot3_mapping_launcher");

  mapper::MapLauncher::launch();

  return 0;
}