#pragma once

#include <string>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

namespace directioner {
    class Rotate {
        public:
            static void startRotating();
            static void stopRotating();

        private:
            Rotate();
            ~Rotate();

            static void publish();
            static void callback(const ros::SingleSubscriberPublisher&);
    };
}