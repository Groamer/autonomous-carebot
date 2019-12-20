#pragma once

#include <vector>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <std_msgs/Header.h>
#include <nav_msgs/Odometry.h>

#include "PublisherSubscriber.h"
#include "MapCalculator.h"
#include "Mover.h"
#include "DimensionVectors.h"
#include "CoordinateSystemConverter.h"

namespace localizer {
    class Localizator {
        public:
            static void locate();

        private:
            Localizator();
            ~Localizator();

            static void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr&);
            static void odomCallback(const nav_msgs::Odometry::ConstPtr&);
            static bool compareVector2D(Vector2D, Vector2D);
    };
}