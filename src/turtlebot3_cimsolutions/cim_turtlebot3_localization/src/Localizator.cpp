#include "Localizator.h"

using namespace localizer;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

static bool hasTopRight = false;
static bool isPositioned = false;
static std::string mapFile;
static Vector2D freeSpot;
static MapCalculator mapCalculator;
static Mover mover;

Localizator::Localizator() {

}

Localizator::~Localizator() {
    
}

void Localizator::locate() {
  const int QUEUE = 1;
  const std::string MAP_TOPIC = "map";
  const std::string MAP_FILE_TOPIC = "cim_turtlebot3_mapping_mapFile";
  const std::string ODOM_TOPIC = "odom";

  ros::NodeHandle nodeHandle;
  ros::Subscriber odomSubscriber = nodeHandle.subscribe(ODOM_TOPIC, QUEUE, odomCallback);
  ros::Subscriber mapSubscriber = nodeHandle.subscribe(MAP_TOPIC, QUEUE, mapCallback);
  ros::Subscriber mapFileSubscriber = nodeHandle.subscribe(MAP_FILE_TOPIC, QUEUE, mapFileCallback);
  ros::spin();
}

void Localizator::mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& message) {
  std::cout << std::endl;
  std::cout << "BRUUUUUH" << std::endl;
  std::cout << std::endl;
  if(!isPositioned) {
    if(compareFreeSpot(freeSpot, mapCalculator.getFreeSpot(message))) {
      hasTopRight = true;
    }

    freeSpot = mapCalculator.getFreeSpot(message);
  } else {
    //launchAMCL(message);
  }
}

void Localizator::mapFileCallback(const std_msgs::String::ConstPtr& message) {
  mapFile = message->data;
}

void Localizator::odomCallback(const nav_msgs::Odometry::ConstPtr& message) {
  if(!isPositioned) {
    Vector2D axesROS = {message->pose.pose.position.x, message->pose.pose.position.y};
    Vector2D current = CoordinateSystemConverter::convertROSToStandard(axesROS);

    if(hasTopRight) {
      if(!inPosition(current)) {
        mover.moveAbsolute(current, freeSpot);
      }
      else {
        isPositioned = true;
      }
    } else {
      Vector2D goal = {3.5, 3.5};
      mover.moveRelative(goal);
    }
  }
}

// Set global parameters used by AMCL.
void Localizator::launchAMCL(const nav_msgs::OccupancyGrid::ConstPtr& message) {
  // Shutdown GMapping.
  system("rosnode kill /turtlebot3_slam_gmapping");

  std::string mapCommand = "rosrun map_server map_server " + mapFile;
  system(mapCommand.c_str());

  Vector2D spot = mapCalculator.getFreeSpot(message);

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "FREESPOT-X: " << freeSpot.x << std::endl;
  std::cout << "FREESPOT-Y: " << freeSpot.y << std::endl;
  std::cout << "SPOT-X: " << spot.x << std::endl;
  std::cout << "SPOT-Y: " << spot.y << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  /*std::ostringstream stream;
  std::string xPosition;
  std::string yPosition;

  stream << topRight.x;
  xPosition = stream.str();
  // Clear stream.
  stream.str(std::string());
  stream << topRight.y;
  yPosition = stream.str();*/

  std::string command = "roslaunch turtlebot3_navigation amcl.launch map_file:="
    + mapFile + " initial_pose_x:=10 initial_pose_y:=10";
  system(command.c_str());

  ros::shutdown();
}

// Compare two Vector2D objects with a small error tolerance.
bool Localizator::compareFreeSpot(Vector2D vectorA, Vector2D vectorB) {
  // Sensor error tolerance in meters.
  const double FREESPOT_TOLERANCE = 0.05;

  if((vectorA.x + FREESPOT_TOLERANCE) > vectorB.x && (vectorA.x - FREESPOT_TOLERANCE) < vectorB.x) {
    if((vectorA.y + FREESPOT_TOLERANCE) > vectorB.y && (vectorA.y - FREESPOT_TOLERANCE) < vectorB.y) {
      return true;
    }
  }
  
  return false;
}

// Check if robot is in calculated free spot.
bool Localizator::inPosition(Vector2D position) {
  // Sensor error tolerance in meters.
  const double POSITION_TOLERANCE = 0.5;

  if((freeSpot.x + POSITION_TOLERANCE) > position.x && (freeSpot.x - POSITION_TOLERANCE) < position.x) {
    if((freeSpot.y + POSITION_TOLERANCE) > position.y && (freeSpot.y - POSITION_TOLERANCE) < position.y) {
      return true;
    }
  }

  return false;
}