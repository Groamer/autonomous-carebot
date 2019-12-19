#pragma once

#include <nav_msgs/OccupancyGrid.h>
#include "DimensionVectors.h"

namespace localizer {
    class MapCalculator {
        public:
            MapCalculator();
            ~MapCalculator();

            Vector2D getFreeSpot(const nav_msgs::OccupancyGrid::ConstPtr&);
            Vector2D getTopRight(const nav_msgs::OccupancyGrid::ConstPtr&);
            bool getIsUpdating();
            
        private:
            int getPixelValue(int, int, const nav_msgs::OccupancyGrid::ConstPtr&);
            bool isFreeSpot(int, int, const nav_msgs::OccupancyGrid::ConstPtr&);
            double convertToAxis(int, int, double);
            int convertToLine(double, int, double);
    };
}