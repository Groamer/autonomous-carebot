#include "SensorListener.h"

using namespace directioner;

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

// Publish Twist messages and listen to Imu messages
template<>
void PublisherSubscriber<geometry_msgs::Twist, sensor_msgs::Imu>::subscriberCallback(
        const sensor_msgs::Imu::ConstPtr& receivedMessage) {
    double sensorSpeed = receivedMessage->angular_velocity.z;
    
    if(sensorSpeed > 0.01 || rotationSpeed > 0) {
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
                    isMeasuring = false;
                    isLocating = false;
            }
        }
        orientationBuffer = orientation;

        geometry_msgs::Twist message;
        message.angular.z = rotationSpeed;
        publisherObject.publish(message);
    } else {
        // Close this node so that all Imu messages are available for other nodes
        ros::shutdown();
    }
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
    if(isMeasuring) {
        magneticField.measure(message);
    }

    if(isLocating) {
        if(magneticField.isAlligned(message)) {
            rotationSpeed = 0;
            isMeasuring = false;
            isLocating = false;
        }
    }
}
