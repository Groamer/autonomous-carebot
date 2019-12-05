#pragma once

#include <string>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <geometry_msgs/Twist.h>

#include "PublisherSubscriber.h"
#include "Orientation.h"
#include "MagneticField.h"

namespace directioner {
    class SensorListener {
        public:
            static void listen();

        private:
            SensorListener();
            ~SensorListener();
            
            static void magnetometerCallback(const sensor_msgs::MagneticField::ConstPtr&);
    };
}