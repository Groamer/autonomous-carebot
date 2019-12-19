#pragma once

#include <vector>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include "DimensionVectors.h"
#include "CoordinateSystemConverter.h"

namespace localizer {
    class Mover {
        public:
            Mover();
            ~Mover();

            void moveToPosition(Vector2D, Vector2D);
            bool getIsMoving();

        private:
            std::vector<double> calculateTranslation(double, double, double, double);
            Vector2D getTranslation(Vector2D, Vector2D);
            Vector2D getMapOffset(Vector2D, Vector2D);
    };
}