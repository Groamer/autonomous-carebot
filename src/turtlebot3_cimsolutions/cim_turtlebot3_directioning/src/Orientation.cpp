#include "Orientation.h"

using namespace directioner;

Orientation::Orientation() {

}

Orientation::~Orientation() {
    
}

double Orientation::getOrientation(const sensor_msgs::Imu::ConstPtr& message) {
    Quaternion quaternion = {
        message->orientation.x,
        message->orientation.y,
        message->orientation.z,
        message->orientation.w
    };

    EulerAngles eulerAngles = EulerAnglesConverter::ToEulerAngles(quaternion);
    return DegreesConverter::ToDegrees(eulerAngles.yaw);
}

bool Orientation::isRotated(double oldOrientation, double newOrientation) {
    if(oldOrientation > newOrientation) {
        double difference = oldOrientation - newOrientation;

        // Tolerate sensor errors
        if(difference > 5) {
            return true;
        }
    }

    return false;
}