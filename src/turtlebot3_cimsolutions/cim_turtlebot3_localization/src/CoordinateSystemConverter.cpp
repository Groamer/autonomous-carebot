#include "CoordinateSystemConverter.h"

using namespace localizer;

CoordinateSystemConverter::CoordinateSystemConverter() {

}

CoordinateSystemConverter::~CoordinateSystemConverter() {

}

Vector2D CoordinateSystemConverter::convertROSToStandard(Vector2D ROS) {
    Vector2D standard;
    standard.x = -ROS.y;
    standard.y = ROS.x;

    return standard;
}

Vector2D CoordinateSystemConverter::convertStandardToROS(Vector2D standard) {
    Vector2D ROS;
    ROS.x = standard.y;
    ROS.y = -standard.x;

    return ROS;
}