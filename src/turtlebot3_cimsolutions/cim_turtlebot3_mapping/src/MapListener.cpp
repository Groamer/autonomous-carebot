#include "MapListener.h"

const static int QUEUE_SIZE = 1;
const static std::string TOPIC = "exploreState";

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

void MapListener::callback(const std_msgs::String::ConstPtr& message) {
    std::string data = message->data.c_str();

    if(data.compare("exploration_done") == 0) {
        MapIO::saveMap();
    }
}