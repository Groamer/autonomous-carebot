#include "SensorListener.h"

using namespace directioner;

const static int LISTEN_FREQUENCY = 10;
const static int QUEUE_SIZE = 1;
const static std::string TOPIC_IMU = "imu";
const static std::string TOPIC_TWIST = "cmd_vel";
const static std::string TOPIC_MAGNETOMETER = "magnetic_field";

static bool isMeasuring = false;
static bool isLocating = false;
static int rotations = 0;
static double rotationSpeed = 0.5;
static double orientationBuffer = 0.0;
static MagneticField magneticField;

// Publish Imu messages and listen to Twist messages
template<>
void PublisherSubscriber<geometry_msgs::Twist, sensor_msgs::Imu>::subscriberCallback(
        const sensor_msgs::Imu::ConstPtr& receivedMessage) {

    // Close node when done with measuring
    if(rotationSpeed == 0 && receivedMessage->angular_velocity.z < 0.1) {
        ros::shutdown();
    }

    double orientation = Orientation::getOrientation(receivedMessage);
    if(Orientation::isRotated(orientationBuffer, orientation)) {
        rotations ++;

        switch(rotations) {
            case 1: 
                isMeasuring = true;
                break;
            case 2:
                isLocating = true;
                break;
            default:
                rotationSpeed = 0;
        }
    }
    orientationBuffer = orientation;

    geometry_msgs::Twist message;
    message.angular.z = rotationSpeed;
    publisherObject.publish(message);
}

SensorListener::SensorListener() {

}

SensorListener::~SensorListener() {

}

void SensorListener::listen() {
    ros::NodeHandle nodeHandle;
    PublisherSubscriber<geometry_msgs::Twist, sensor_msgs::Imu> twistImu(
        TOPIC_TWIST, TOPIC_IMU, QUEUE_SIZE);
    ros::Subscriber magnetometer = nodeHandle.subscribe(
        TOPIC_MAGNETOMETER, QUEUE_SIZE, magnetometerCallback);
    ros::spin();
}

void SensorListener::magnetometerCallback(const sensor_msgs::MagneticField::ConstPtr& message) {
    ros::Rate rate(LISTEN_FREQUENCY);

    if(isMeasuring) {
        magneticField.measure(message);
    }

    if(isLocating) {
        if(magneticField.isAlligned(message)) {
            rotationSpeed = 0;
        }
    }

    rate.sleep();
}