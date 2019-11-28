#include "OdometryListener.h"

using namespace directioner;

OdometryListener::OdometryListener() {

}

OdometryListener::~OdometryListener() {

}

//ToDo: For now we read the default imu sensor data. Change this to magnetometer later.
void OdometryListener::callback(const sensor_msgs::Imu::ConstPtr& message) {
    ROS_INFO("Imu Seq: [%d]", message->header.seq);
    ROS_INFO("Imu Orientation x: [%f], y: [%f], z: [%f], w: [%f]",message->orientation.x,message->orientation.y,message->orientation.z,message->orientation.w);
}

void OdometryListener::listen() {


    
        ros::NodeHandle nodeHandle;
        ros::Subscriber subscriber = nodeHandle.subscribe("imu", 1000, callback);
        ros::spin();


}