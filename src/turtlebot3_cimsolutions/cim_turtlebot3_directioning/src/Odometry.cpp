#include "Odometry.h"

using namespace directioner;

static const int LISTEN_FREQUENCY = 10;
static const int QUEUE_SIZE = 1;

static bool isConnected = false;
static std::vector<double> orientations;

Odometry::Odometry() {
    listen();
}

Odometry::~Odometry() {

}

void Odometry::listen() {
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("imu", QUEUE_SIZE, callback);   
    ros::spin();
}

//ToDo: For now we read the default imu sensor data. Change this to magnetometer later.
void Odometry::callback(const sensor_msgs::Imu::ConstPtr& message) {
    ros::Rate rate(LISTEN_FREQUENCY);

    Quaternion quaternion = {
        message->orientation.x,
        message->orientation.y,
        message->orientation.z,
        message->orientation.w
    };
    addOrientation(quaternion);

    if(isConnected) {
        verifyRotation();
    } else {
        isConnected = true;
        Rotate::startRotating();
    }

    rate.sleep();
}

void Odometry::verifyRotation() {
    // Start verifying after 10 measurements
    if(orientations.size() >= 10) {
        double startOrientation = orientations[0];
        double lastOrientation = orientations[orientations.size() - 1];

        // Count a full 360 degrees turn if last known orientation is within 10 degrees of start rotation
        if(lastOrientation < startOrientation + 5 && lastOrientation > startOrientation - 5) {
            Rotate::stopRotating();
        }
    }
}

void Odometry::addOrientation(Quaternion quaternion) {
    EulerAngles eulerAngles = EulerAnglesConverter::ToEulerAngles(quaternion);
    double orientation = DegreesConverter::ToDegrees(eulerAngles.yaw);
    orientations.push_back(orientation);
}