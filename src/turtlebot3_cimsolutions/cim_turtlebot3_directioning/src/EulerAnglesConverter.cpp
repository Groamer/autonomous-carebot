#include "EulerAnglesConverter.h"

using namespace directioner;

EulerAnglesConverter::EulerAnglesConverter() {

}

EulerAnglesConverter::~EulerAnglesConverter() {
    
}

EulerAngles EulerAnglesConverter::ToEulerAngles(Quaternion quaternion) {
    EulerAngles angles;

    // roll (x-axis rotation)
    double sinr_cosp = 2 * (quaternion.w * quaternion.x + quaternion.y * quaternion.z);
    double cosr_cosp = 1 - 2 * (quaternion.x * quaternion.x + quaternion.y * quaternion.y);
    angles.roll = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = 2 * (quaternion.w * quaternion.y - quaternion.z * quaternion.x);
    if (std::abs(sinp) >= 1)
        angles.pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        angles.pitch = asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (quaternion.w * quaternion.z + quaternion.x * quaternion.y);
    double cosy_cosp = 1 - 2 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
    angles.yaw = atan2(siny_cosp, cosy_cosp);

    std::cout << "BRUH: " << angles.yaw << std::endl;

    return angles;
}