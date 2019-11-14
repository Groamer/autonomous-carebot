#pragma once

#include "MapIO.h"

namespace mapper {
    class MapProvider {
        public:
            static void provide();

        private:
            MapProvider();
            ~MapProvider();

            static void newMap();
            static void existingMap();
    };
}