#include "DegreesConverter.h"

using namespace directioner;

DegreesConverter::DegreesConverter() {

}

DegreesConverter::~DegreesConverter() {
    
}

// Convert Radians to Degrees
double DegreesConverter::ToDegrees(double radians) {
    if(radians >= (double)0) {
        return radians * 180 / M_PI;
    } else {
        return radians * 180 / M_PI + 360;
    }
    
}