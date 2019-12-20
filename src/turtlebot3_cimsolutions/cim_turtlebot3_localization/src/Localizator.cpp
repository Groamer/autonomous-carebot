#include "Localizator.h"

using namespace localizer;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

static bool foundFreeSpot = false;
static Vector2D freeSpot;
static MapCalculator mapCalculator;
static Mover mover;

Localizator::Localizator() {

}

Localizator::~Localizator() {
    
}

void Localizator::locate() {
  ros::NodeHandle nodeHandle;
  ros::Subscriber mapSubscriber = nodeHandle.subscribe("map", 1, mapCallback);
  ros::Subscriber odomSubscriber = nodeHandle.subscribe("odom", 1, odomCallback);
  ros::spin();
}

void Localizator::mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& message) {
  // Make sure previous move task has been completed before processing a new one.
  if(!foundFreeSpot && !mover.getIsMoving()) {
    if(compareVector2D(freeSpot, mapCalculator.getFreeSpot(message))) {
      foundFreeSpot = true;
    } else {
      // Move robot 5 meter upwards and 5 meter to the right.
      Vector2D goal = {5.0, 5.0};
      mover.moveRelative(goal);
    }

    freeSpot = mapCalculator.getFreeSpot(message);
 }

  ros::Rate rate(10);
  rate.sleep();
}

void Localizator::odomCallback(const nav_msgs::Odometry::ConstPtr& message) {
  if(foundFreeSpot && !mover.getIsMoving()) {
    Vector2D axesROS = {message->pose.pose.position.x, message->pose.pose.position.y};
    Vector2D current = CoordinateSystemConverter::convertROSToStandard(axesROS);

    if(!isPositioned(current)) {
      mover.moveAbsolute(current, freeSpot);
    } else {
      // OPEN EXISTING MAP AND FIND TOPRIGHT SPOT THERE
      // THEN SET COORDINATES AND RELOAD GMAPPING BLYAT
    }  
  }

  ros::Rate rate(10);
  rate.sleep();
}

// Compare two Vector2D objects.
bool Localizator::compareVector2D(Vector2D vectorA, Vector2D vectorB) {
  if(vectorA.x == vectorB.x && vectorA.y == vectorB.y) {
    return true;
  }

  return false;
}

// Check if robot is in calculated free spot.
bool Localizator::isPositioned(Vector2D position) {
  // Set tolerance to 10 cm.
  const double tolerance = 0.01;

  if(freeSpot.x > (position.x - tolerance) && freeSpot.x < (position.x + tolerance)) {
    if(freeSpot.y > (position.y - tolerance) && freeSpot.y < (position.y + tolerance)) {
      return true;
    }
  }

  return false;
}