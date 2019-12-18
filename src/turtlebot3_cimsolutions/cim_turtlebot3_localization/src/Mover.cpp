#include "Mover.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace localizer;

static bool isMoving = false;

Mover::Mover() {

}

Mover::~Mover() {

}

// Move to an absolute position on the X and Y axis.
void Mover::setGoal(double xPosition, double yPosition, double xGoal, double yGoal) {
    isMoving = true;
    // Tell the action client that we want to spin a thread by default.
    MoveBaseClient moveClient("move_base", true);
    // Wait for the action server to come up.
    while(!moveClient.waitForServer(ros::Duration(1.0))){

    }
    std::vector<double> translation = calculateTranslation(xPosition, yPosition, xGoal, yGoal);
    Axes axesStandard = {translation[0], translation[1]};
    Axes axesROS = CoordinateSystemConverter::convertStandard(axesStandard);

    move_base_msgs::MoveBaseGoal moveGoal;
    moveGoal.target_pose.header.frame_id = "base_link";
    moveGoal.target_pose.header.stamp = ros::Time::now();
    moveGoal.target_pose.pose.position.x = axesROS.x;
    moveGoal.target_pose.pose.position.y = axesROS.y;
    moveGoal.target_pose.pose.orientation.w = 1.0;

    moveClient.sendGoal(moveGoal);
    moveClient.waitForResult();

    if(moveClient.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        isMoving = false;
    } else {
        isMoving = false;
    }
}

bool Mover::getIsMoving() {
    return isMoving;
}

// Calculate moving goal's relative coordinates for moving the robot.
std::vector<double> Mover::calculateTranslation(double xPosition, double yPosition, double xGoal, double yGoal) {
    const double xDelta = xGoal - xPosition;
    const double yDelta = yGoal - yPosition;

    const double xTranslation = xPosition + xDelta;
    const double yTranslation = yPosition + yDelta;

    std::vector<double> translation;
    translation.push_back(xDelta);
    translation.push_back(yDelta);

    return translation;
}