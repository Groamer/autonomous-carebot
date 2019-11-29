#include "Rotate.h"

#include <iostream>

using namespace directioner;

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

//EDIT THIS TO PUBLISHER MEEP MEEP
/*void Odometry::listen() {
    ros::NodeHandle nodeHandle;

    while(ros::ok() && !isConnected) {
        ros::Rate rate(frequenty);

        ros::Subscriber subscriber = nodeHandle.subscribe("imu", 1, callback);
        std::cout << "trying to connect with: " << frequenty << std::endl;
        frequenty = frequenty / 10;
        ros::spinOnce();
        rate.sleep();
    }
}*/

void Rotate::publish() {
    const std::string TOPIC_NAME = "cmd_vel";
    // Amount of messsages allowed in queue before being dropped
    const int QUEUE = 1;

    ros::NodeHandle nodeHandle;
    ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>(TOPIC_NAME, QUEUE,
        (ros::SubscriberStatusCallback)connectCallback);
    ros::spin();

    std::cout << "ENDING" << std::endl;
}

void Rotate::connectCallback(const ros::SingleSubscriberPublisher& publisher) {
    geometry_msgs::Twist message;
    message.angular.z = rotationSpeed;
    publisher.publish(message);
    //ros::shutdown();
}