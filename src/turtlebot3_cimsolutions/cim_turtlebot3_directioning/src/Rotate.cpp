#include "Rotate.h"

using namespace directioner;

static bool isConnected;
double rotationSpeed;

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
    ros::Rate rate(4);
    ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>("cmd_vel", 1,
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