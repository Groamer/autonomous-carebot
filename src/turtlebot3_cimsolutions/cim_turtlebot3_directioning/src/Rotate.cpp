#include "Rotate.h"

using namespace directioner;

static const int QUEUE_SIZE = 1;
static const int PUBLISH_FREQUENCY = 10;
static const std::string PUBLISH_TOPIC = "cmd_vel";

static bool isConnected = false;
static double rotationSpeed = 0.0;

Rotate::Rotate() {
    
}

Rotate::~Rotate() {
    
}

void Rotate::startRotating() {
    rotationSpeed = 0.5;
    publish();
}

void Rotate::stopRotating() {
    rotationSpeed = 0.0;
    publish();
}

void Rotate::publish() {
    isConnected = false;
    ros::NodeHandle nodeHandle;
    ros::Rate rate(PUBLISH_FREQUENCY);
    ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>(PUBLISH_TOPIC, QUEUE_SIZE,
        (ros::SubscriberStatusCallback)callback);

    while(ros::ok() && !isConnected) {
        rate.sleep();
        ros::spinOnce();
    }
}

void Rotate::callback(const ros::SingleSubscriberPublisher& publisher) {
    isConnected = true;
    geometry_msgs::Twist message;
    message.angular.z = rotationSpeed;
    publisher.publish(message);
}