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

            void moveAbsolute(Vector2D, Vector2D);
            void moveRelative(Vector2D);
            bool getIsMoving();

        private:
            Vector2D getTranslation(Vector2D, Vector2D);
    };
}