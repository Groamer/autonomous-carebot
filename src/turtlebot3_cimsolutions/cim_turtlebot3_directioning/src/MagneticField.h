#pragma once

#include <sensor_msgs/MagneticField.h>

namespace directioner {
    class MagneticField {
        public:
            MagneticField();
            ~MagneticField();

            void measure(const sensor_msgs::MagneticField::ConstPtr&);
            bool isAlligned(const sensor_msgs::MagneticField::ConstPtr&);

        private:
            double getMeasurement(const sensor_msgs::MagneticField::ConstPtr&);
    };
}