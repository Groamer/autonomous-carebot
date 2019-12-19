#include "Localizator.h"

using namespace localizer;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

static bool foundTopRight = false;
static bool foundFreeSpot = false;
static Vector2D topRight;
static Vector2D freeSpot;
static MapCalculator mapCalculator;
static Mover mover;

Localizator::Localizator() {

}

Localizator::~Localizator() {
    
}

void Localizator::locate() {
  ros::NodeHandle nodeHandle;
  ros::Subscriber odomSubscriber = nodeHandle.subscribe("odom", 1, odomCallback);
  ros::Subscriber mapSubscriber = nodeHandle.subscribe("map", 1, mapCallback);
  ros::spin();
}

void Localizator::mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& message) {
  // This value has to be set only once
  if(!isSet(topRight)) {
    topRight = getTopRight(message);
  }

  // Make sure previous update has been completed before processing a new one.
  if(!mapCalculator.getIsUpdating()) {
    if(!isSame(topRight, mapCalculator.getFreeSpot(message))) {
      freeSpot = mapCalculator.getFreeSpot(message);

      std::cout << "FREE SPOT X: " << freeSpot.x << std::endl;
      std::cout << "FREE SPOT Y: " << freeSpot.y << std::endl;
    }
  }
}

void Localizator::odomCallback(const nav_msgs::Odometry::ConstPtr& message) {
  if(!foundTopRight && !mover.getIsMoving() && isSet(topRight)) {
    Vector2D axesROS = {message->pose.pose.position.x, message->pose.pose.position.y};
    Vector2D current = CoordinateSystemConverter::convertROSToStandard(axesROS);

    std::cout << "FINDING TOP RIGHT" << std::endl;
    mover.moveToPosition(current, topRight);
    foundTopRight = true;
  }

  if(foundTopRight && !foundFreeSpot && !mover.getIsMoving() && isSet(freeSpot)) {
    Vector2D axesROS = {message->pose.pose.position.x, message->pose.pose.position.y};
    Vector2D current = CoordinateSystemConverter::convertROSToStandard(axesROS);

    std::cout << "DRIVING TO TOP RIGHT" << std::endl;
    mover.moveToPosition(current, freeSpot);
    foundFreeSpot = true;
  }
}

// Get top right of map with a small error margin.
Vector2D Localizator::getTopRight(const nav_msgs::OccupancyGrid::ConstPtr& message) {
  Vector2D topRight = mapCalculator.getTopRight(message);
  topRight.x = topRight.x - 0.25;
  topRight.y = topRight.y - 0.25;

  return topRight;
}

bool Localizator::isSet(Vector2D location) {
  if(location.x == (double)0 && location.y == (double)0) {
    return false;
  }

  return true;
}

// Ugly fix, but it works.
bool Localizator::isSame(Vector2D vectorA, Vector2D vectorB) {
  if(vectorA.x == vectorB.x && vectorA.y == vectorB.y) {
    return true;
  }

  return false;
}