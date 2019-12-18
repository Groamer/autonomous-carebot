#pragma once

#include <vector>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "CoordinateSystemConverter.h"

namespace localizer {
    class Mover {
        public:
            Mover();
            ~Mover();

            void setGoal(double, double, double, double);
            bool getIsMoving();

        private:
            std::vector<double> calculateTranslation(double, double, double, double);
    };
}