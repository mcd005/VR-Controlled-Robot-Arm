#include <Arduino.h>
#include "JointInfoStructs.hpp"
#include "AngleTransformer.hpp"

AngleTransformer::AngleTransformer(JointAngleInfo givenAngleInfo) :
    minLegalAngle(givenAngleInfo.minLegalAngle),
    maxLegalAngle(givenAngleInfo.maxLegalAngle),
    offset(givenAngleInfo.offset),
    isInverted(givenAngleInfo.isInverted)
{
}

uint16_t AngleTransformer::transfromAngle(uint16_t angle)
{
    if (isInverted)
    {
        angle = invertAngle(angle);
    }
    return boundAngle(applyOffset(angle));
}

uint16_t AngleTransformer::applyOffset(uint16_t angle)
{
    return angle + offset;
}

uint16_t AngleTransformer::boundAngle(uint16_t angle)
{
    if (angle < minLegalAngle) return minLegalAngle;
    else if (angle > maxLegalAngle) return maxLegalAngle;
    else return angle;
}

uint16_t AngleTransformer::invertAngle(uint16_t angle)
{
    return 180 - angle;
}