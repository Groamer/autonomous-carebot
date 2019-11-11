#include "ros/ros.h"
#include "std_msgs/String.h"

#include <iostream>

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
    std::string topic = "exploreState";
    std::cout << "Hello, I am listening to topic '" << topic << "'." << std::endl;

    ros::init(argc, argv, "topicTester");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe(topic, 1000, chatterCallback);

    ros::spin();

    return 0;
}
