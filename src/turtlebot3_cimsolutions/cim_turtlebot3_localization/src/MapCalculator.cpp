#include "MapCalculator.h"

using namespace localizer;

MapCalculator::MapCalculator() {

}

MapCalculator::~MapCalculator() {

}

Vector2D MapCalculator::getFreeSpot(const nav_msgs::OccupancyGrid::ConstPtr& message) {
    const int width = message->info.width;
    const int height = message->info.height;

    Vector2D coordinates;

    // Iterate over Y-axis from top to bottom
    for(int y = height - 1; y >= 0; y --) {
        // Iterate over X-axis from right to left
        for(int x = width - 1; x >= 0; x --) {
            // Get pixel value at given index
            if(getPixelValue(x, y, message) == 0) {
                if(isFreeSpot(x, y, message)) {
                    coordinates.x = (convertToAxis(x, width, message->info.resolution));
                    coordinates.y = (convertToAxis(y, height, message->info.resolution));

                    return coordinates;
                }
            }
        }
    }

    return coordinates;
}

int MapCalculator::getPixelValue(int xPixel, int yPixel, const nav_msgs::OccupancyGrid::ConstPtr& message) {
    const int width = message->info.width;
    const int index = xPixel + width * yPixel;

    return message->data[index];
}

bool MapCalculator::isFreeSpot(int xPixel, int yPixel, const nav_msgs::OccupancyGrid::ConstPtr& message) {
    // Amount of pixels per meter
    const int ppm = ceil((double)1 / message->info.resolution);
    const int radius = ceil(ppm / 2.5);

    // Iterate over Y-axis within radius
    for(double y = yPixel + radius; y >= yPixel - radius; y --) {
        // Iterate over X-axis within radius
        for(double x = xPixel + radius; x >= xPixel - radius; x --) {
            if(getPixelValue(x, y, message) != 0) {
                return false;
            }
        }
    }

    return true;
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
    const double ppm = (double)1 / resolution;
    // Calculate halfway value of pixels
    const double halfway = (double)maxPixel / (double)2;
    // Convert to linear value using pixels as quantity
    return ceil((curPosition * ppm) + halfway);
}