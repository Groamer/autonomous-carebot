#include "ros/ros.h"
#include <iostream>

int main(int argc, char **argv) {
    ros::init(argc, argv, "test");

    std::cout << "Hello world!" << std::endl;

    return 0;
}
