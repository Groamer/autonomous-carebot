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
  ros::Subscriber odomSubscriber = nodeHandle.subscribe("odom", 1, odomCallback);
  ros::Subscriber mapSubscriber = nodeHandle.subscribe("map", 1, mapCallback);
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
}

void Localizator::odomCallback(const nav_msgs::Odometry::ConstPtr& message) {
  if(foundFreeSpot && !mover.getIsMoving()) {
    Vector2D axesROS = {message->pose.pose.position.x, message->pose.pose.position.y};
    Vector2D current = CoordinateSystemConverter::convertROSToStandard(axesROS);

    std::cout << "freespotx: " << freeSpot.x << std::endl;
    std::cout << "freespoty: " << freeSpot.y << std::endl;

    mover.moveAbsolute(current, freeSpot);
  }

  /*
  NIEUWE OPLOSSING:
  LAAT DE ROBOT STEEDS 5 OMHOOG EN 5 NAAR RECHTS RIJDEN
  VERGELIJK DAN DE NIEUWE FREESPOT
  INDIEN DE FREESPOT NIET MEER VERANDERT WEET JE DAT DE TOP IS BEREIKT
  */
}

// Compare two Vector2D objects.
bool Localizator::compareVector2D(Vector2D vectorA, Vector2D vectorB) {
  if(vectorA.x == vectorB.x && vectorA.y == vectorB.y) {
    return true;
  }

  return false;
}