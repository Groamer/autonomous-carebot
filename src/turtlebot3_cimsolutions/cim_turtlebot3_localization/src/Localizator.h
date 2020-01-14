#pragma once
#include <iostream>
#include <sstream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>
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
            static void mapFileCallback(const std_msgs::String::ConstPtr&);
            static void odomCallback(const nav_msgs::Odometry::ConstPtr&);
            static void launchAMCL(const nav_msgs::OccupancyGrid::ConstPtr&);
            static bool compareFreeSpot(Vector2D, Vector2D);
            static bool inPosition(Vector2D);
    };
}