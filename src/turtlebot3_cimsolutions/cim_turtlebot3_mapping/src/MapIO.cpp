#include "MapIO.h"

using namespace mapper;

const static std::string FILENAME = "cim_turtlebot3_mapping_map";
const static std::string DIRECTORY = "cim_turtlebot3_mapping/";

MapIO::MapIO() {
    
}

MapIO::~MapIO() {

}

std::string MapIO::getFolderPath() {
    // Get absolute path to user directory.
    std::string const home = std::getenv("HOME") ? std::getenv("HOME") : ".";
    std::string const ros = "/.ros/";
    
    return home + ros + DIRECTORY;
}

std::string MapIO::getFilePath() {
    return getFolderPath() + FILENAME;
}

// Create directory if it does not exist already.
void MapIO::checkDirectory() {
    std::string directoryCommand = "mkdir -p " + getFolderPath();
    system(directoryCommand.c_str());
}

void MapIO::saveMap() {
    checkDirectory();

    std::string saveCommand = "rosrun map_server map_saver -f " + getFolderPath()
        + FILENAME;
    system(saveCommand.c_str());
}

// Load map file with .yaml file extension.
std::string MapIO::loadMap() {
    const std::string fileExtension = ".yaml";
    std::string mapFile;

    checkDirectory();

    // Check if files are present in preconfigured path.
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(getFolderPath().data())) != NULL) {
        // Search files in directory.
        while((ent = readdir(dir)) != NULL) {
            // Check if map file is present.
            if(std::string(ent->d_name).find(FILENAME + fileExtension) != std::string::npos) {
                mapFile = getFilePath() + fileExtension;
            }
        }
        closedir(dir);
    }

    return mapFile;
}