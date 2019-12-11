#include <ros/ros.h>
#include "MapProvider.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "cim_turtlebot3_mapping_provider");

    mapper::MapProvider::provide();

    return 0;
}