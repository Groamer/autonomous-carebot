#pragma once

#include <ros/ros.h>
#include <string>

template<typename PublishT, typename SubscribeT>
class PublisherSubscriber {
    public:
        PublisherSubscriber();
        PublisherSubscriber(std::string publishTopicName, std::string subscribeTopicName, int queueSize) {
            publisherObject = nodeHandle.advertise<PublishT>(publishTopicName, queueSize);
            subscriberObject = nodeHandle.subscribe<SubscribeT>(subscribeTopicName, queueSize,
                &PublisherSubscriber::subscriberCallback, this);
        }

        void subscriberCallback(const typename SubscribeT::ConstPtr& receivedMessage);

    protected:
        ros::Subscriber subscriberObject;
        ros::Publisher publisherObject;
        ros::NodeHandle nodeHandle;
};