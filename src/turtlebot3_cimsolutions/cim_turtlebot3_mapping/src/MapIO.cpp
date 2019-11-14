#include "MapIO.h"

using namespace mapper;

const static std::string filename = "cim_turtlebot3_mapping_map";
const static std::string directory = "cim_turtlebot3_mapping/";

MapIO::MapIO() {
    
}

MapIO::~MapIO() {

}

std::string MapIO::getPath() {
    //Get absolute path to user directory
    std::string const home = std::getenv("HOME") ? std::getenv("HOME") : ".";
    std::string const ros = "/.ros/";
    
    return home + ros + directory;
}

void MapIO::checkDirectory() {
    //Create directory if it does not already exist
    std::string directoryCommand = "mkdir -p " + getPath();
    system(directoryCommand.c_str());
}

void MapIO::saveMap() {
    checkDirectory();

    //Save map
    std::string saveCommand = "rosrun map_server map_saver -f " + getPath()
        + filename;
    system(saveCommand.c_str());
}

std::vector<std::string> MapIO::loadMap() {
    std::vector<std::string> files;

    checkDirectory();

    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(getPath().data())) != NULL) {
        //Search files in directory
        while((ent = readdir(dir)) != NULL) {
            //Ignore unrelated files
            if(std::string(ent->d_name).find(filename) != std::string::npos) {
                files.push_back(getPath() + ent->d_name);
            }
        }
        closedir(dir);
    }

    return files;
}
