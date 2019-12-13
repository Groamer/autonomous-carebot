#include "MapCalculator.h"

using namespace localizer;

MapCalculator::MapCalculator() {

}

MapCalculator::~MapCalculator() {

}

void MapCalculator::getFreeSpot(const nav_msgs::OccupancyGrid::ConstPtr& msg) {
    const int width = msg->info.width;
    const int height = msg->info.height;

    // Iterate over Y-axis
    for(int y = height - 1; y >= 0; y --) {
        // Iterate over X-axis
        for(int x = width - 1; x >= 0; x --) {
            // Get pixel value at given index
            int index = x + width * y;
            int value = msg->data[index];

            if(value == 0) {
                // vrije spot gevonden.
                //controlleer of deze groot genoeg is voor de robot
                //getCoordinates(x, y, msg);

                getCoordinates(x, y, msg);
            }
        }
    }
}

void MapCalculator::getCoordinates(int x, int y, const nav_msgs::OccupancyGrid::ConstPtr& msg) {
    double xAxis = convertToAxis(x, msg->info.width, msg->info.resolution);
    double yAxis = convertToAxis(y, msg->info.height, msg->info.resolution);

    int xLine = convertToLine(xAxis, msg->info.width, msg->info.resolution);
    int yLine = convertToLine(yAxis, msg->info.height, msg->info.resolution);
}

double MapCalculator::convertToAxis(int curPixel, int maxPixel, double resolution) {
    // Amount of pixels per meter
    double ppm = (double)1 / resolution;
    // Calculate halfway value of pixels
    double halfway = (double)maxPixel / (double)2;
    // Convert to axis using meters as quantity
    return ((double)curPixel - halfway) / ppm;
}

int MapCalculator::convertToLine(double curPosition, int maxPixel, double resolution) {
    // Amount of pixels per meter
    double ppm = (double)1 / resolution;
    // Calculate halfway value of pixels
    double halfway = (double)maxPixel / (double)2;
    // Convert to linear value using pixels as quantity
    return ceil((curPosition * ppm) + halfway);
}