#include <Arduino.h>

#ifndef JOINT_INFO_STRUCTS
#define JOINT_INFO_STRUCTS

struct JointAngleInfo
{
    const uint8_t startAngle;
    const uint8_t minLegalAngle;
    const uint8_t maxLegalAngle;
    const int16_t offset;
    const bool isInverted;
};

struct JointPulseWidthInfo
{
    uint16_t minPulseWidth;
    uint16_t maxPulseWidth;
};

#endif
