#include "MapListener.h"

using namespace mapper;

// Frequency in Herz.
const static int FREQUENCY = 1;
const static int QUEUE = 1;
const static std::string TOPIC = "cim_turtlebot3_mapping_hasExplored";

MapListener::MapListener() {

}

MapListener::~MapListener() {
    
}

void MapListener::listen() {
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe(TOPIC, QUEUE, callback);
    ros::spin();
}

void MapListener::callback(const std_msgs::Bool::ConstPtr& message) {
    if(message->data) {
        MapIO::saveMap();
    }

    ros::Rate rate(FREQUENCY);
    rate.sleep();
}