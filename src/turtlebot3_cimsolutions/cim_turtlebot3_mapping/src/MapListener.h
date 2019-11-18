#pragma once

#include "MapIO.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>

namespace mapper {
    class MapListener {
        public:
            MapListener();
            ~MapListener();

        private:
            static void callback(const std_msgs::String::ConstPtr&);
            void listen();
    };
}