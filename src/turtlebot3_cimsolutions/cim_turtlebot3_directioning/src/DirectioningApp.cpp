#include <iostream>
#include <ros/ros.h>

#include "SensorListener.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "filter_velocity");

  // Calibrate robot's magnetic sensor and point robot to the Earth's south pole
  directioner::SensorListener::listen();

  system("roslaunch cim_turtlebot3_mapping cim_turtlebot3_mapping.launch");

  return 0;
}