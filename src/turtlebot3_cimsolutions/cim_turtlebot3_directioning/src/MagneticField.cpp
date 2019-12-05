#include "MagneticField.h"

using namespace directioner;

const static double TOLERANCE = 0.00005;

static double highestMeasurement = 0.0;

MagneticField::MagneticField() {

}

MagneticField::~MagneticField() {
    
}

void MagneticField::measure(const sensor_msgs::MagneticField::ConstPtr& message) {
    double measurement = getMeasurement(message);

    if(measurement > highestMeasurement) {
        highestMeasurement = measurement;
    }
}

bool MagneticField::isAlligned(const sensor_msgs::MagneticField::ConstPtr& message) {
    double measurement = getMeasurement(message);
    double lowTolerance = measurement - TOLERANCE;
    double highTolerance = measurement + TOLERANCE;

    if(measurement < highTolerance && measurement > lowTolerance) {
        return true;
    }

    return false;
}

double MagneticField::getMeasurement(const sensor_msgs::MagneticField::ConstPtr& message) {
    return message->magnetic_field.x;
}