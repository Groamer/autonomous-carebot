#include "MapLauncher.h"

using namespace mapper;

// Frequency in Herz.
const static int FREQUENCY = 10;
const static int QUEUE = 1;
const static std::string TOPIC = "cim_turtlebot3_mapping_mapFile";

MapLauncher::MapLauncher() {

}

MapLauncher::~MapLauncher() {
    
}

void MapLauncher::launch() {
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe(TOPIC, QUEUE, callback);
    ros::spin();
}

void MapLauncher::callback(const std_msgs::String::ConstPtr& message) {
    if(hasMap(message)) {
	ros::shutdown();
        // A map exists, so find robot's position in the map.
        system("roslaunch cim_turtlebot3_mapping cim_turtlebot3_mapping_existing.launch");
    } else {
	ros::shutdown();
        // No map exists, so create a new one.
        system("roslaunch cim_turtlebot3_mapping cim_turtlebot3_mapping_new.launch");
    }

    ros::Rate rate(FREQUENCY);
    rate.sleep();
}

// Check if message contains a map.
bool MapLauncher::hasMap(const std_msgs::String::ConstPtr& message) {
    std::string data = message->data.c_str();

    if(data.compare("") == 0) {
        return false;
    } else {
        return true;
    }
}
