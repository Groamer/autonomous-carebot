#include "Odometry.h"

using namespace directioner;

static const int QUEUE_SIZE = 1000;
static const int LISTEN_FREQUENCY = 10;
static const std::string IMU_TOPIC = "imu";
static const std::string MAGNETOMETER_TOPIC = "magnetic_field";

static bool isRotating = false;
static bool isMeasuring = false;
static bool isLocating = false;
static bool isShuttingDown = false;
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
    ros::Subscriber orientation = nodeHandle.subscribe(IMU_TOPIC, QUEUE_SIZE,
        orientationCallback);
    ros::Subscriber angularVelocity = nodeHandle.subscribe(IMU_TOPIC, QUEUE_SIZE,
        angularVelocityCallback);
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
    } else if(!isShuttingDown) {
        beginRotation(quaternion);
    }

    rate.sleep();
}

// Make sure robot has come to a complete stop before shutting down node
void Odometry::angularVelocityCallback(const sensor_msgs::Imu::ConstPtr& message) {
    ros::Rate rate(LISTEN_FREQUENCY);

    double rotationSpeed = message->angular_velocity.z;

    std::cout << "rotationSpeed: " << rotationSpeed << std::endl;
    std::cout << "isShuttingDown: " << isShuttingDown << std::endl;

    if(isShuttingDown) {
        Rotate::stopRotating();
        std::cout << "STAHP" << std::endl;

        if(rotationSpeed < 0.1) {
            std::cout << "IK WIL AFSLUITEN VERDOMME" << std::endl;
            ros::shutdown();
        }
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

// Choose to shutdown immediately or to wait for a full rotation
void Odometry::shutdown(Quaternion quaternion, bool isInstantly) {
    isMeasuring = false;
    isLocating = false;

    if(isInstantly) {
        isRotating = false;
        isShuttingDown = true;
    } else {
        double orientation = calculateOrientation(quaternion);

        if(orientation > 340) {
            isRotating = false;
            isShuttingDown = true;
        }
    }
}

// Check current status and count amount of rotations
void Odometry::verifyRotation(Quaternion quaternion) {
    currentOrientation = calculateOrientation(quaternion);

    if(isRotated(currentOrientation, previousOrientation) && !isShuttingDown) {
        rotations ++;

        std::cout << "ROTATION ++ WHOOP" << std::endl;
        std::cout << currentOrientation << std::endl;
        std::cout << previousOrientation << std::endl;
        std::cout << std::endl;

        switch(rotations) {
            /*case 1:
                std::cout << "measuring magnetic fields" << std::endl;
                isMeasuring = true;
                break;
            case 2:
                std::cout << "locating magnetic field" << std::endl;
                isLocating = true;
                break;*/
            default:
                shutdown(quaternion, true);
                //break;
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

// Check if robot has passed 360 degrees of rotation
bool Odometry::isRotated(double currentOrientation, double previousOrientation) {
    if(currentOrientation < previousOrientation) {
        double difference = previousOrientation - currentOrientation;

        // Ignore sensor errors
        if(difference > 10) {
            return true;
        }
    }

    return false;
}