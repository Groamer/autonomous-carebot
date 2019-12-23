#include <ros/ros.h>
#include "MapPublisher.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "cim_turtlebot3_mapping_publisher");

    mapper::MapPublisher::publish();

    return 0;
}