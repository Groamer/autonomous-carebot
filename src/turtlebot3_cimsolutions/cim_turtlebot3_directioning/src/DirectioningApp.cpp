#include <ros/ros.h>

#include "SensorListener.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "filter_velocity");

  directioner::SensorListener::listen();

  return 0;
}