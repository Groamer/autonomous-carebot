#include "MapListener.h"

using namespace mapper;

MapListener::MapListener() {
    listen();
}

MapListener::~MapListener() {
    
}

void MapListener::callback(const std_msgs::String::ConstPtr& message) {
    std::string data = message->data.c_str();

    if(data.compare("exploration_done") == 0) {
        MapIO::saveMap();
	ros::shutdown();
    }
}

void MapListener::listen() {
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("exploreState", 1000, callback);
    ros::spin();
}
