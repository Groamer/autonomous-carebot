#include "ros/ros.h"
#include "EulerAnglesConverter.h"
#include "DegreesConverter.h"

#include <iostream>

int main(int argc, char **argv) {
    ros::init(argc, argv, "cim_turtlebot3_directioning");

    directioner::Quaternion sample = {2.0, 2.0, 2.0, 2.0};

    directioner::EulerAnglesConverter::ToEulerAngles(sample);

    std::cout << "BRUH: " << directioner::DegreesConverter::ToDegrees(1) << std::endl;

    return 0;
}