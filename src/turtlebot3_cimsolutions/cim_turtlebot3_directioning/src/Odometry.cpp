#include "Odometry.h"

using namespace directioner;

static const int QUEUE_SIZE = 1;
static const int LISTEN_FREQUENCY = 10;
static const std::string ORIENTATION_TOPIC = "imu";
static const std::string MAGNETOMETER_TOPIC = "magnetic_field";

static bool isRotating = false;
static bool isMeasuring = false;
static bool isLocating = false;
static bool isResetting = false;
static int rotations = 0;
static double currentOrientation = 0;
static double previousOrientation = 0;
static std::vector<double> measurements;

Odometry::Odometry() {
    listen();
}

Odometry::~Odometry() {

}

void Odometry::listen() {
    ros::NodeHandle nodeHandle;
    ros::Subscriber orientation = nodeHandle.subscribe(ORIENTATION_TOPIC, QUEUE_SIZE,
        orientationCallback);
    ros::Subscriber magnetometer = nodeHandle.subscribe(MAGNETOMETER_TOPIC, QUEUE_SIZE,
        magnetometerCallback);
    ros::spin();
}

void Odometry::orientationCallback(const sensor_msgs::Imu::ConstPtr& message) {
    ros::Rate rate(LISTEN_FREQUENCY);

    Quaternion quaternion = {
        message->orientation.x,
        message->orientation.y,
        message->orientation.z,
        message->orientation.w
    };

    if(isRotating) {
        verifyRotation(quaternion);
    } else if(!isResetting) {
        beginRotation(quaternion);
    }

    if(isResetting) {
        endRotation(quaternion);
    }

    rate.sleep();
}

void Odometry::magnetometerCallback(const sensor_msgs::MagneticField::ConstPtr& message) {
    ros::Rate rate(LISTEN_FREQUENCY);

    if(isMeasuring) {
        std::cout << "Magnetic sensor: " << message << std::endl;
    }

    if(isLocating) {
        locateMagneticField();
    }

    rate.sleep();
}

void Odometry::beginRotation(Quaternion quaternion) {
    isRotating = true;
    Rotate::startRotating();
}

void Odometry::endRotation(Quaternion quaternion) {
    double orientation = calculateOrientation(quaternion);

    std::cout << orientation << std::endl;

    if(orientation > 345) {
        isRotating = false;
        Rotate::stopRotating();
    }
}

void Odometry::verifyRotation(Quaternion quaternion) {
    currentOrientation = calculateOrientation(quaternion);

    if(currentOrientation < previousOrientation) {
        rotations ++;

        switch(rotations) {
            case 1:
                std::cout << "measuring magnetic fields" << std::endl;
                isMeasuring = true;
                break;
            case 2:
                std::cout << "locating magnetic field" << std::endl;
                isLocating = true;
                break;
            default:
                isMeasuring = false;
                isLocating = false;
                isResetting = true;
                std::cout << "could not find magnetic fields" << std::endl;
        }
    }

    previousOrientation = currentOrientation;
}

void Odometry::locateMagneticField() {

}

double Odometry::calculateOrientation(Quaternion quaternion) {
    EulerAngles eulerAngles = EulerAnglesConverter::ToEulerAngles(quaternion);
    return DegreesConverter::ToDegrees(eulerAngles.yaw);
}