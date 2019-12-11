#include "MapProvider.h"

using namespace mapper;

MapProvider::MapProvider() {

}

MapProvider::~MapProvider() {
    
}

void MapProvider::provide() {
    if(MapIO::loadMap().empty()) {
        newMap();
    } else {
        existingMap();
    }
}

void MapProvider::newMap() {
    system("roslaunch cim_turtlebot3_mapping cim_turtlebot3_mapping_new.launch");
}

void MapProvider::existingMap() {
    std::string mapFile = MapIO::getFilePath(".yaml");

    // LAUNCH CODE TO DRIVE ROBOT TO UPPER RIGHT POSITION OF THE MAP
    //std::string command = "roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=" + mapFile;
    //system(command.c_str());
}