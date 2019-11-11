#include "MapIO.h"

using namespace mapper;

const static std::string location = "cim_turtlebot3_mapping/";

MapIO::MapIO() {
    
}

MapIO::~MapIO() {

}

void MapIO::saveMap(std::string mapName) {
    //Create folder if it does not already exist
    std::string folderCommand = "mkdir -p " + location;
    system(folderCommand.c_str());

    //Save map
    std::string saveCommand = "rosrun map_server map_saver -f " + location
        + mapName;
    system(saveCommand.c_str());
}

void MapIO::loadMap() {

}