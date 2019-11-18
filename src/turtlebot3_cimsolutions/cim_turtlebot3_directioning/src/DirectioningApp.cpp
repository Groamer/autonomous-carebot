#include "ros/ros.h"
#include "EulerAnglesConverter.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "cim_turtlebot3_directioning");

    directioner::EulerAnglesConverter converter;

    directioner::Quaternion sample = {2.0, 2.0, 2.0, 2.0};

    converter.ToEulerAngles(sample);

    return 0;
}