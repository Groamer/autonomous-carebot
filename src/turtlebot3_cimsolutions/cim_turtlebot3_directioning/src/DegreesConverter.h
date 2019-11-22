#pragma once

#include <math.h>

namespace directioner {
    class DegreesConverter {
        public:
            static double ToDegrees(double);

        private:
            DegreesConverter();
            ~DegreesConverter();
    };
}