#include "JointInfoStructs.hpp"

#ifndef ANGLE_TRANSFORMER
#define ANGLE_TRANSFORMER

class AngleTransformer
{
public:
    AngleTransformer(JointAngleInfo givenAngleInfo);
    uint16_t transfromAngle(uint16_t angle);
private:
    const uint8_t minLegalAngle;
    const uint8_t maxLegalAngle;
    const int16_t offset;
    const bool isInverted;

    uint16_t  applyOffset(uint16_t angle);
    uint16_t boundAngle(uint16_t angle);
    uint16_t invertAngle(uint16_t angle);
};

#endif