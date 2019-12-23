#include "MapPublisher.h"

using namespace mapper;

// Frequency in Herz.
static const int FREQUENCY = 1;
static const int QUEUE_SIZE = 1;
static const std::string TOPIC = "cim_turtlebot3_mapping_mapFile";

MapPublisher::MapPublisher() {

}

MapPublisher::~MapPublisher() {
    
}

void MapPublisher::publish() {
    ros::NodeHandle nodeHandle;
    ros::Publisher publisher = nodeHandle.advertise<std_msgs::String>(TOPIC, QUEUE_SIZE);
    ros::Rate rate(FREQUENCY);

    while(ros::ok()) {
        std_msgs::String message;
        message.data = MapIO::loadMap().c_str();
        publisher.publish(message);
        ros::spinOnce();
        rate.sleep();
    }
}