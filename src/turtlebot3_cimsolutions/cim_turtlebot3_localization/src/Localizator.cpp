#include "Localizator.h"

using namespace localizer;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

const static int QUEUE = 1;
// Frequency in hertz.
const static int MAP_FREQUENCY = 10;
const static int MAP_FILE_FREQUENCY = 1;
const static int ODOM_FREQUENCY = 1;
// Sensor error tolerance in meters.
const static double POSITION_TOLERANCE = 0.5;
const static double FREESPOT_TOLERANCE = 0.01;
const static std::string MAP_TOPIC = "map";
const static std::string MAP_FILE_TOPIC = "cim_turtlebot3_mapping_mapFile";
const static std::string ODOM_TOPIC = "odom";

static bool foundFreeSpot = false;
static bool foundTopRight = false;
static std::string mapFile;
static Vector2D freeSpot;
static MapCalculator mapCalculator;
static Mover mover;

Localizator::Localizator() {

}

Localizator::~Localizator() {
    
}

void Localizator::locate() {
  ros::NodeHandle nodeHandle;
  ros::Subscriber mapSubscriber = nodeHandle.subscribe(MAP_TOPIC, QUEUE, mapCallback);
  ros::Subscriber mapFileSubscriber = nodeHandle.subscribe(MAP_FILE_TOPIC, QUEUE, mapFileCallback);
  ros::Subscriber odomSubscriber = nodeHandle.subscribe(ODOM_TOPIC, QUEUE, odomCallback);
  ros::spin();
}

void Localizator::mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& message) {
  // Make sure previous move task has been completed before processing a new one.
  if(!foundFreeSpot) {
    if(compareFreeSpot(freeSpot, mapCalculator.getFreeSpot(message))) {
      foundFreeSpot = true;
    }

    freeSpot = mapCalculator.getFreeSpot(message);
 }

  //FOR LATER
 if(foundTopRight) {
   setPosition(mapCalculator.getFreeSpot(message));
 }

  ros::Rate rate(MAP_FREQUENCY);
  rate.sleep();
}

void Localizator::mapFileCallback(const std_msgs::String::ConstPtr& message) {
  mapFile = message->data;

  ros::Rate rate(MAP_FILE_FREQUENCY);
  rate.sleep();
}

void Localizator::odomCallback(const nav_msgs::Odometry::ConstPtr& message) {
  if(foundFreeSpot) {
    Vector2D axesROS = {message->pose.pose.position.x, message->pose.pose.position.y};
    Vector2D current = CoordinateSystemConverter::convertROSToStandard(axesROS);

    if(!isPositioned(current)) {
      mover.moveAbsolute(current, freeSpot);
    } else {
      foundTopRight = true;
    }  
  } else {
    // Move robot 3.5 meter upwards and 3.5 meter to the right.
    Vector2D goal = {3.5, 3.5};
    mover.moveRelative(goal);
  }

  ros::Rate rate(ODOM_FREQUENCY);
  rate.sleep();
}

// Set global parameters used by AMCL.
void Localizator::setPosition(Vector2D topRight) {
  // Shutdown GMapping.
  system("rosnode kill /turtlebot3_slam_gmapping");

  std::ostringstream stream;
  std::string xPosition;
  std::string yPosition;

  stream << topRight.x;
  xPosition = stream.str();
  // Clear stream.
  stream.str(std::string());
  stream << topRight.y;
  yPosition = stream.str();

  std::string command = "roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:="
    +mapFile;
  system(command.c_str());

  ros::shutdown();
}

// Compare two Vector2D objects with a small error tolerance.
bool Localizator::compareFreeSpot(Vector2D vectorA, Vector2D vectorB) {
  if((vectorA.x + FREESPOT_TOLERANCE) > vectorB.x && (vectorA.x - FREESPOT_TOLERANCE) < vectorB.x) {
    if((vectorA.y + FREESPOT_TOLERANCE) > vectorB.y && (vectorA.y - FREESPOT_TOLERANCE) < vectorB.y) {
      return true;
    }
  }
  
  return false;
}

// Check if robot is in calculated free spot.
bool Localizator::isPositioned(Vector2D position) {
  if((freeSpot.x + POSITION_TOLERANCE) > position.x && (freeSpot.x - POSITION_TOLERANCE) < position.x) {
    if((freeSpot.y + POSITION_TOLERANCE) > position.y && (freeSpot.y - POSITION_TOLERANCE) < position.y) {
      return true;
    }
  }

  return false;
}