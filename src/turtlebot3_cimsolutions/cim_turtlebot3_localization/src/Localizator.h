#pragma once
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>
#include "MapCalculator.h"
#include "Mover.h"
#include "DimensionVectors.h"
#include "CoordinateSystemConverter.h"

//TEMP
#include <iostream>

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
            static bool isPositioned(Vector2D);
    };
}