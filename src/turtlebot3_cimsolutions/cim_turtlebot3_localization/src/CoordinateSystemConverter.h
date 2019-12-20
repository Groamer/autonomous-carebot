#pragma once
#include <vector>
#include "DimensionVectors.h"

namespace localizer {
    class CoordinateSystemConverter {
        public:
            static Vector2D convertROSToStandard(Vector2D);
            static Vector2D convertStandardToROS(Vector2D);

        private:
            CoordinateSystemConverter();
            ~CoordinateSystemConverter();
    };
}