#pragma once
#include <string>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include "MapIO.h"

namespace mapper {
    class MapListener {
        public:
            static void listen();

        private:
            MapListener();
            ~MapListener();
            
            static void callback(const std_msgs::Bool::ConstPtr&);
    };
}