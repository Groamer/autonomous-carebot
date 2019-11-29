#pragma once

#include "Rotate.h"
#include "EulerAnglesConverter.h"
#include "DegreesConverter.h"

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <iostream>
#include <vector>

namespace directioner {
    class Odometry {
        public:
            Odometry();
            ~Odometry();

        private:
            void listen();
            static void callback(const sensor_msgs::Imu::ConstPtr&);
            static void verifyRotation();
            static void addOrientation(Quaternion);
    };
}