#pragma once

#include <iostream>
#include <nav_msgs/OccupancyGrid.h>

namespace localizer {
    class MapCalculator {
        public:
            MapCalculator();
            ~MapCalculator();

            void getFreeSpot(const nav_msgs::OccupancyGrid::ConstPtr&);
            void getCoordinates(int, int, const nav_msgs::OccupancyGrid::ConstPtr&);
            
        private:
            double convertToAxis(int, int, double);
            int convertToLine(double, int, double);
    };
}