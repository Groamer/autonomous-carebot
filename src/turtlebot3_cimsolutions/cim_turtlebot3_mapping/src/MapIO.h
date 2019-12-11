#pragma once

#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <cstdlib>

namespace mapper {
    class MapIO {
        public:
            static void saveMap();
            static std::vector<std::string> loadMap();
            static std::string getFilePath(std::string);

        private:
            MapIO();
            ~MapIO();

            static std::string getPath();
            static void checkDirectory();
    };
}