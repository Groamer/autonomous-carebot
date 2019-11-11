#pragma once

#include <stdlib.h>
#include <string>

namespace mapper {
    class MapIO {
        public:
            MapIO();
            ~MapIO();

            static void saveMap(std::string);
            static void loadMap();

        private:
    };
}