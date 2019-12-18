#include <iostream>
#include <vector>
#include <ros/ros.h>
#include <costmap_2d/costmap_2d.h>
#include <geometry_msgs/Twist.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <nav_msgs/GridCells.h>
#include <nav_msgs/MapMetaData.h>
#include <nav_msgs/OccupancyGrid.h>
#include <std_msgs/Header.h>
#include <nav_msgs/Odometry.h>

#include "MapCalculator.h"
#include "Mover.h"
#include "CoordinateSystemConverter.h"

using namespace localizer;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

static int findIterator = 0;
static std::vector<double> topRight;
static MapCalculator mapCalculator;
static Mover mover;

static void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg) {
  // Make sure previous update has been completed before processing a new one.
  if(!mapCalculator.getIsUpdating()) {
    std::vector<double> coordinates = mapCalculator.getFreeSpot(msg);
  }
}

static void odomCallback(const nav_msgs::Odometry::ConstPtr& message) {
  Axes axesROS;
  axesROS.x = message->pose.pose.position.x;
  axesROS.y = message->pose.pose.position.y;

  Axes axesStandard = CoordinateSystemConverter::convertROS(axesROS);
  std::cout << "X: " << axesStandard.x << std::endl;
  std::cout << "Y: " << axesStandard.y << std::endl;
  std::cout << std::endl;

  mover.setGoal(0, 0, 0, 0.5);

  if(!mover.getIsMoving()) {
    /*double xPosition = message->pose.pose.position.x;
    double yPosition = message->pose.pose.position.y;
    std::vector<double> coordinates = mover.convertCoordinates(xPosition, yPosition);

    std::cout << "X: " << coordinates[0] << std::endl;
    std::cout << "Y: " << coordinates[1] << std::endl;*/

    switch(findIterator) {
      case 0:
        //ga naar pos max
        /*double mapMin;
        double mapMax;

        ros::param::get("/gmapping_min", mapMin);
        ros::param::get("/gmapping_max", mapMax);*/

        //mover.setGoal(coordinates[0], coordinates[1], 20, 20);

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
}

void findTopRight() {
  ros::NodeHandle nodeHandle;
  ros::Subscriber odomSubscriber = nodeHandle.subscribe("odom", 1, odomCallback);
  ros::Subscriber mapSubscriber = nodeHandle.subscribe("map", 1, mapCallback);
  ros::spin();
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "cim_turtlebot3_localization");

  findTopRight();

  double test = 0.0;
  ros::param::get("/gmapping_min", test);
  std::cout << test << std::endl;

  return 0;
}