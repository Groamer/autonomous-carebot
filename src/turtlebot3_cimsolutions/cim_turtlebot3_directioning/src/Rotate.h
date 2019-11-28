#pragma once

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <string>

namespace directioner {
    class Rotate {
        public:
            static void startRotating();
            static void stopRotating();
            static bool getIsRotating();

        private:
            Rotate();
            ~Rotate();
    };
}