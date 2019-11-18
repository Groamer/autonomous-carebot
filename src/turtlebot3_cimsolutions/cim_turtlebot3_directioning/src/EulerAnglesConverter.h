#pragma once

#include <cmath>
#include <iostream>

namespace directioner {
    struct Quaternion {
        double x, y, z, w;
    };

    struct EulerAngles {
        double roll, pitch, yaw;
    };

    class EulerAnglesConverter {
        public:
            EulerAnglesConverter();
            ~EulerAnglesConverter();

            EulerAngles ToEulerAngles(Quaternion);

        private:

    };
}