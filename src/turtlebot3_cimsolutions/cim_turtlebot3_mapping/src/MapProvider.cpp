#include "MapProvider.h"

using namespace mapper;

//TEMP
#include <iostream>

MapProvider::MapProvider() {

}

MapProvider::~MapProvider() {
    
}

void MapProvider::newMap() {
    std::cout << "Creating new map..." << std::endl;
    system("roslaunch explore_lite explore.launch");
}

void MapProvider::existingMap() {
    std::cout << "Loading existing map..." << std::endl;
}

void MapProvider::provide() {
    if(MapIO::loadMap().empty()) {
        newMap();
    } else {
        existingMap();
    }
}