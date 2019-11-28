/*#include "ros/ros.h"
#include "EulerAnglesConverter.h"
#include "DegreesConverter.h"

#include <iostream>

int main(int argc, char **argv) {
    ros::init(argc, argv, "cim_turtlebot3_directioning");

    directioner::Quaternion sample = {2.0, 2.0, 2.0, 2.0};

    directioner::EulerAnglesConverter::ToEulerAngles(sample);

    std::cout << "BRUH: " << directioner::DegreesConverter::ToDegrees(1) << std::endl;

    return 0;
}*/

#include <iostream>
#include <unistd.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include "OdometryListener.h"
#include "Rotate.h"

void test() {
  ros::NodeHandle nodeHandle;
  ros::Rate rate(1);

  bool isRotating = false;

  while(ros::ok()) {
    //directioner::Rotate::startRotating(nodeHandle);

    /*if(isRotating) {
      directioner::Rotate::stopRotating(nodeHandle);
      isRotating = !isRotating;
    } else {
      directioner::Rotate::startRotating(nodeHandle);
      isRotating = !isRotating;
    }*/

    rate.sleep();

    directioner::Rotate::startRotating();

    rate.sleep();

    directioner::Rotate::stopRotating();

    ros::spinOnce();
  }

  //directioner::Rotate::startRotating(nodeHandle);
  //ros::spin();
}


int main(int argc, char **argv) {

  ros::init(argc, argv, "filter_velocity");

  test();

  //directioner::OdometryListener::listen();

  /*ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Rate rate(10);

  while(ros::ok()){
     geometry_msgs::Twist msg;
     msg.angular.z = 1.0;

     pub.publish(msg);

     /*if() {
         msg.angular.z = 0.0;

        pub.publish(msg);
         break;
     }*/

     //rate.sleep();
     //ros::spinOnce();

 // }

  return 0;
}