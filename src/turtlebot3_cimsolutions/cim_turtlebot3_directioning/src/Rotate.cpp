#include "Rotate.h"

using namespace directioner;

// Refresh rate in Herz
static const int REFRESH_RATE = 10;
// Amount of messsages allowed in queue before being dropped
static const int QUEUE = 10;
static const std::string TOPIC_NAME = "cmd_vel";

bool isRotating = false;

Rotate::Rotate() {
    
}

Rotate::~Rotate() {
    
}

void Rotate::startRotating() {
    ros::NodeHandle nodeHandle;
    ros::Rate rate(REFRESH_RATE);

    // Keep trying to connect until publisher is subscribed
    while(ros::ok()) {
        ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>(TOPIC_NAME, QUEUE);
        rate.sleep();

        // Send message when publisher is subscribed and close loop
        if (publisher.getNumSubscribers() > 0) {
            geometry_msgs::Twist message;
            message.angular.z = 0.5;

            publisher.publish(message);
            isRotating = true;
            break;
        }
        ros::spinOnce();
    }
}

void Rotate::stopRotating() {
    ros::NodeHandle nodeHandle;
    ros::Rate rate(REFRESH_RATE);

    // Keep trying to connect until publisher is subscribed
    while(ros::ok()) {
        ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>(TOPIC_NAME, QUEUE);
        rate.sleep();

        // Send message when publisher is subscribed and close loop
        if (publisher.getNumSubscribers() > 0) {
            geometry_msgs::Twist message;
            message.angular.z = 0.0;

            publisher.publish(message);
            isRotating = false;
            break;
        }
        ros::spinOnce();
    }
}

bool Rotate::getIsRotating() {
    return isRotating;
}