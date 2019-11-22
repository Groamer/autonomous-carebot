#include "DegreesConverter.h"

using namespace directioner;

DegreesConverter::DegreesConverter() {

}

DegreesConverter::~DegreesConverter() {
    
}

// Convert Radians to Degrees
double DegreesConverter::ToDegrees(double radians) {
    return radians * 180 / M_PI;
}