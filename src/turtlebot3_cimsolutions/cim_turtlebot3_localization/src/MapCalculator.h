#pragma once

#include <iostream>
#include <vector>
#include <nav_msgs/OccupancyGrid.h>

namespace localizer {
    class MapCalculator {
        public:
            MapCalculator();
            ~MapCalculator();

            std::vector<double> getFreeSpot(const nav_msgs::OccupancyGrid::ConstPtr&);
            
        private:
            int getPixelValue(int, int, const nav_msgs::OccupancyGrid::ConstPtr&);
            bool isFreeSpot(int, int, const nav_msgs::OccupancyGrid::ConstPtr&);
            void getCoordinates(int, int, const nav_msgs::OccupancyGrid::ConstPtr&);
            double convertToAxis(int, int, double);
            int convertToLine(double, int, double);
    };
}