#pragma once

#include <sensor_msgs/Imu.h>
#include "EulerAnglesConverter.h"
#include "DegreesConverter.h"

namespace directioner {
    class Orientation {
        public:
            static double getOrientation(const sensor_msgs::Imu::ConstPtr&);
            static bool isRotated(double, double);

        private:
            Orientation();
            ~Orientation();
    };
}