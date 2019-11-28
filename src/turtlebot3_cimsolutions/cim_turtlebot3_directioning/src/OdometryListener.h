#pragma once

#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include <iostream>

namespace directioner {
    class OdometryListener {
        public:
            static void listen();

        private:
            OdometryListener();
            ~OdometryListener();

            static void callback(const sensor_msgs::Imu::ConstPtr&);
    };
}