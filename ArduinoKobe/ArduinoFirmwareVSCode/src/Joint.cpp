#include "Joint.hpp"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#define PULSE_ON 15
#define INCREMENT_DELAY_USECS 0

Joint::Joint(String name, uint8_t startAngle, uint16_t pulseMin, uint16_t pulseMax, uint8_t channel, Adafruit_PWMServoDriver *pwmObject) :
    jointName(name),
    currentPulseWidth(calculatePulseWidth(startAngle)),
    targetPulseWidth(calculatePulseWidth(startAngle)),
    jointChannel(channel),
    minPulseWidth(pulseMin),
    maxPulseWidth(pulseMax),
    pwm(pwmObject)
{
}

String Joint::setTargetAngle(int givenAngle)
{
    targetPulseWidth = calculatePulseWidth(givenAngle);
    return "\n" + jointName + " target angle set to " + String(givenAngle);
}

void Joint::incrementPosition()
{
    if (currentPulseWidth != targetPulseWidth)
    {
        if (currentPulseWidth < targetPulseWidth) ++currentPulseWidth;
        if (currentPulseWidth > targetPulseWidth) --currentPulseWidth;
        pwm->setPWM(jointChannel, PULSE_ON, currentPulseWidth);
        delay(INCREMENT_DELAY_USECS);
    }
}

int Joint::calculatePulseWidth(uint16_t angle)
{
    return map(angle, 0, 180, minPulseWidth, maxPulseWidth);
}