#pragma once

#include <cmath>

namespace directioner {
    struct Quaternion {
        double x, y, z, w;
    };

    struct EulerAngles {
        double roll, pitch, yaw;
    };

    class EulerAnglesConverter {
        public:
            static EulerAngles ToEulerAngles(Quaternion);

        private:
            EulerAnglesConverter();
            ~EulerAnglesConverter();
    };
}