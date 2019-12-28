#include "Mover.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace localizer;

static bool isMoving = false;

Mover::Mover() {

}

Mover::~Mover() {

}

// Move to an absolute position on the X and Y axis.
void Mover::moveAbsolute(Vector2D start, Vector2D goal) {
    isMoving = true;
    // Tell the action client that we want to spin a thread by default.
    MoveBaseClient moveClient("move_base", true);
    // Wait for the action server to come up.
    while(!moveClient.waitForServer(ros::Duration(1.0))) {

    }

    Vector2D translation = getTranslation(start, goal);
    move_base_msgs::MoveBaseGoal moveGoal;
    moveGoal.target_pose.header.frame_id = "base_link";
    moveGoal.target_pose.header.stamp = ros::Time::now();
    moveGoal.target_pose.pose.position.x = translation.x;
    moveGoal.target_pose.pose.position.y = translation.y;
    moveGoal.target_pose.pose.orientation.w = 1.0;

    moveClient.sendGoal(moveGoal);
    moveClient.waitForResult();

    if(moveClient.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        // Could be expanded in the future.
    }

    isMoving = false;
}

// Move to a position relative to the robot's position.
void Mover::moveRelative(Vector2D goal) {
    Vector2D start = {0.0, 0.0};
    moveAbsolute(start, goal);
}

// Calculate moving goal's relative coordinates for moving the robot.
Vector2D Mover::getTranslation(Vector2D start, Vector2D goal) {
    Vector2D startROS = CoordinateSystemConverter::convertStandardToROS(start);
    Vector2D goalROS = CoordinateSystemConverter::convertStandardToROS(goal);

    Vector2D translation;
    translation.x = goalROS.x - startROS.x;
    translation.y = goalROS.y - startROS.y;

    return translation;
}