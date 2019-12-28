#include <ros/ros.h>
#include "Localizator.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "cim_turtlebot3_localization");

  localizer::Localizator::locate();

  // launch amcl with saved map
  // scan saved map for free spot
  // set free spot as starting position

  return 0;
}