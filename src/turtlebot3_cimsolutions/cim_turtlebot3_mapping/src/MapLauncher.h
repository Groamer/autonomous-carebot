#pragma once
#include <string>
#include <ros/ros.h>
#include <std_msgs/String.h>

namespace mapper {
    class MapLauncher {
        public:
            static void launch();

        private:
            MapLauncher();
            ~MapLauncher();

            static void callback(const std_msgs::String::ConstPtr&);
            static bool hasMap(const std_msgs::String::ConstPtr&);
    };
}