#include <Arduino.h>
#include "Joint.hpp"

#define MIN_PULSE_USEC 500
#define MAX_PULSE_USEC 2500
#define FREQUENCY 50

Joint::Joint(String name, uint16_t startAngle, uint16_t channel) :
    jointName(name),
    currentAngle(startAngle),
    targetAngle(startAngle),
    jointChannel(channel)
{
}

String Joint::setTargetAngle(int givenAngle)
{
    targetAngle = givenAngle;
    return jointName + " target angle set to " + String(targetAngle);
}
    
void Joint::incrementPosition()
{
    if (currentAngle != targetAngle)
    {
        if (currentAngle < targetAngle) ++currentAngle;
        if (currentAngle > targetAngle) --currentAngle;
        // pwm.setPWM(jointChannel, 0, calculatePulseWidth(currentAngle));
    }
}

int Joint::calculatePulseWidth(uint16_t angle)
{
    int pulseDurationUsec, pulse_width;
    pulseDurationUsec = map(angle, 0, 180, MIN_PULSE_USEC, MAX_PULSE_USEC);
    pulse_width = int(float(pulseDurationUsec) / 1000000 * FREQUENCY * 4096);
}