#include "CoordinateSystemConverter.h"

using namespace localizer;

CoordinateSystemConverter::CoordinateSystemConverter() {

}

CoordinateSystemConverter::~CoordinateSystemConverter() {

}

Axes CoordinateSystemConverter::convertROS(Axes ROS) {
    Axes standard;
    standard.x = -ROS.y;
    standard.y = ROS.x;

    return standard;
}

Axes CoordinateSystemConverter::convertStandard(Axes standard) {
    Axes ROS;
    ROS.x = standard.y;
    ROS.y = -standard.x;

    return ROS;
}