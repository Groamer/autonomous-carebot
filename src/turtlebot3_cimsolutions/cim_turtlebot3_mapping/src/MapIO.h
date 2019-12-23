#pragma once

#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace mapper {
    class MapIO {
        public:
            static void saveMap();
            static std::string loadMap();

        private:
            MapIO();
            ~MapIO();

            static std::string getFolderPath();
            static std::string getFilePath();
            static void checkDirectory();
    };
}