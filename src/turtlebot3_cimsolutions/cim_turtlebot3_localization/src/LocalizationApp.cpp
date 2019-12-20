#include <ros/ros.h>
#include "Localizator.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "cim_turtlebot3_localization");

  localizer::Localizator::locate();

  return 0;
}