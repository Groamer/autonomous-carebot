#pragma once
#include <string>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "MapIO.h"

namespace mapper {
    class MapPublisher {
        public:
            static void publish();

        private:
            MapPublisher();
            ~MapPublisher();
    };
}