#include "MapIO.h"

using namespace mapper;

MapIO::MapIO() {

}

MapIO::~MapIO() {

}

void MapIO::saveMap(std::string mapName) {
    std::string command = "rosrun map_server map_saver -f " + mapName;
    system(command.c_str());
}

void MapIO::loadMap() {

}