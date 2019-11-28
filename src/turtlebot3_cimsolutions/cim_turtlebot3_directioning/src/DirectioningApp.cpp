#include <ros/ros.h>

#include "Rotate.h"


int main(int argc, char **argv) {
  ros::init(argc, argv, "filter_velocity");
  
  for(int i = 0; i < 10; i ++) {
    directioner::Rotate::startRotating();
    directioner::Rotate::stopRotating();
  }

  return 0;
}