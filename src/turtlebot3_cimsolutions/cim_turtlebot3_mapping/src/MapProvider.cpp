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
    std::cout << "Creating new map..." << std::endl;
    system("roslaunch cim_turtlebot3_mapping cim_turtlebot3_mapping_new.launch");
}

void MapProvider::existingMap() {
    //make robot drive to the upper right corner of the map
    std::cout << "Loading existing map..." << std::endl;
}