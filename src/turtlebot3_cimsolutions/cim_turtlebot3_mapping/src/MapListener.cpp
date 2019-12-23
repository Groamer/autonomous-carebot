#include "MapListener.h"

// Frequency in Herz.
const static int LISTEN_FREQUENCY = 1;
const static int QUEUE_SIZE = 1;
const static std::string TOPIC = "cim_turtlebot3_mapping_hasExplored";

using namespace mapper;

MapListener::MapListener() {

}

MapListener::~MapListener() {
    
}

void MapListener::listen() {
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe(TOPIC, QUEUE_SIZE, callback);
    ros::spin();
}

void MapListener::callback(const std_msgs::Bool::ConstPtr& message) {
    if(message->data) {
        MapIO::saveMap();
    }

    ros::Rate rate(LISTEN_FREQUENCY);
    rate.sleep();
}