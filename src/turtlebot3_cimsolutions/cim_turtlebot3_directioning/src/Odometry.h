#pragma once

#include "Rotate.h"
#include "EulerAnglesConverter.h"
#include "DegreesConverter.h"

#include <iostream>
#include <string>
#include <vector>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>

namespace directioner {
    class Odometry {
        public:
            Odometry();
            ~Odometry();

        private:
            void listen();
            static void orientationCallback(const sensor_msgs::Imu::ConstPtr&);
            static void magnetometerCallback(const sensor_msgs::MagneticField::ConstPtr&);
            static void beginRotation(Quaternion);
            static void endRotation(Quaternion);
            static void verifyRotation(Quaternion);
            static void locateMagneticField();
            static double calculateOrientation(Quaternion);
    };
}