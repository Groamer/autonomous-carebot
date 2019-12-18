#pragma once

#include <vector>

namespace localizer {
    struct Axes {
        double x, y;
    };

    class CoordinateSystemConverter {
        public:
            static Axes convertROS(Axes);
            static Axes convertStandard(Axes);

        private:
            CoordinateSystemConverter();
            ~CoordinateSystemConverter();
    };
}