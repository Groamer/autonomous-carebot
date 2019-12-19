#include "Mover.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace localizer;

static bool isMoving = false;

Mover::Mover() {

}

Mover::~Mover() {

}

// Move to a position on the X and Y axis.
void Mover::moveToPosition(Vector2D start, Vector2D goal) {
    isMoving = true;
    // Tell the action client that we want to spin a thread by default.
    MoveBaseClient moveClient("move_base", true);
    // Wait for the action server to come up.
    while(!moveClient.waitForServer(ros::Duration(1.0))) {

    }

    Vector2D translation = getTranslation(start, goal);
    Vector2D axesROS = CoordinateSystemConverter::convertStandardToROS(translation);

    Vector2D goalROSTEMP = CoordinateSystemConverter::convertStandardToROS(goal);
    std::cout << "ROSGOAL X" << goalROSTEMP.x << std::endl;
    std::cout << "ROSGOAL Y" << goalROSTEMP.y << std::endl;
    std::cout << std::endl;


    move_base_msgs::MoveBaseGoal moveGoal;
    moveGoal.target_pose.header.frame_id = "base_link";
    moveGoal.target_pose.header.stamp = ros::Time::now();
    moveGoal.target_pose.pose.position.x = axesROS.x;
    moveGoal.target_pose.pose.position.y = axesROS.y;
    moveGoal.target_pose.pose.orientation.w = 1.0;

    moveClient.sendGoal(moveGoal);
    moveClient.waitForResult();

    if(moveClient.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        // Could be expanded in the future.
    }

    isMoving = false;
}

bool Mover::getIsMoving() {
    return isMoving;
}

// Calculate moving goal's relative coordinates for moving the robot.
Vector2D Mover::getTranslation(Vector2D start, Vector2D goal) {
    Vector2D translation;
    translation.x = goal.x - start.x;
    translation.y = goal.y - start.y;

    return translation;
}

// Calculate map's offset relative to the robot's starting position.
Vector2D Mover::getMapOffset(Vector2D start, Vector2D topRight) {
    
}