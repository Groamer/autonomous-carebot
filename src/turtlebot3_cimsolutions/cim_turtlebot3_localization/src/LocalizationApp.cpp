#include <iostream>
#include <vector>
#include <ros/ros.h>
#include <costmap_2d/costmap_2d.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <nav_msgs/GridCells.h>
#include <nav_msgs/MapMetaData.h>
#include <nav_msgs/OccupancyGrid.h>
#include <std_msgs/Header.h>
#include <nav_msgs/Odometry.h>

#include "CoordinateSystemConverter.h"
#include "PublisherSubscriber.h"
#include "MapCalculator.h"
#include "Mover.h"
#include "Localizator.h"

using namespace localizer;

int main(int argc, char** argv) {
  ros::init(argc, argv, "cim_turtlebot3_localization");

  Localizator::locate();

  return 0;
}

/*typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

static int findIterator = 0;
static double mapWidth = 0;
static std::vector<double> topRight;
static std::vector<double> estimatedTopRight;
static MapCalculator mapCalculator;
static Mover mover;

// Publish Pose messages and listen to Odometry messages
template<>
void PublisherSubscriber<nav_msgs::Odometry, geometry_msgs::Pose>::subscriberCallback(
        const geometry_msgs::Pose::ConstPtr& receivedMessage) {
    receivedMessage->pose.pose.position.x;
}

static void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg) {
  // Make sure previous update has been completed before processing a new one.
  if(!mapCalculator.getIsUpdating()) {
    std::vector<double> coordinates = mapCalculator.getFreeSpot(msg);
    estimatedTopRight = mapCalculator.getTopRight(msg);

    std::cout << "TOP RIGHT WHEEEEEEE 1: " << estimatedTopRight[0] << std::endl;
    std::cout << "TOP RIGHT WHEEEEEEE 2: " << estimatedTopRight[1] << std::endl;
  }
}

static void odomCallback(const nav_msgs::Odometry::ConstPtr& message) {

  if(!mover.getIsMoving()) {
    Axes axesROS = {message->pose.pose.position.x, message->pose.pose.position.y};
    Axes axesStandard = CoordinateSystemConverter::convertROS(axesROS);

    switch(findIterator) {
      case 0:
        //ga naar pos max
        /*double mapMin;
        double mapMax;

        ros::param::get("/gmapping_min", mapMin);
        ros::param::get("/gmapping_max", mapMax);*/

        /*mover.setGoal(axesStandard.x, axesStandard.y, 0.5, 0.5);
        //mover.setGoal(0, 0, 22.3, 22.3);
        //mover.setGoal(0, 0, 22.25, 24.25);

        //SET ROBOT POSE TO BOTTOM LEFT POSITION AND THEN NAV TO TOP RIGHT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  
        //HOLD AN ERROR RATE OF 2 METER IN ACCOUNT

        findIterator ++;
        break;
      case 1:
        //ga naar eerst gevonden pos max
        findIterator ++;
        break;
      case 2:
        //ga naar pos max
        findIterator ++;
        break;
      case 3:
        //ga naar tweede gevonden pos (zou toppunt moeten zijn)
        findIterator ++;
        break;
    }
  }

  /*isFinding = true;
  
  double xPosition = message->pose.pose.position.x;
  double yPosition = message->pose.pose.position.y;
  
  if(!mover.isMoving()) {
    // Find far top right
    mover.setGoal(0.0, 0.0)


    mover.setGoal(xPosition, yPosition, 0.0, 20.0);
  }*/
//}

/*void findTopRight() {
  ros::NodeHandle nodeHandle;
  ros::Subscriber odomSubscriber = nodeHandle.subscribe("odom", 1, odomCallback);
  ros::Subscriber mapSubscriber = nodeHandle.subscribe("map", 1, mapCallback);
  ros::spin();
}*/