#include "Joint.hpp"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#define PULSE_ON 15
#define INCREMENT_DELAY_USECS 0

Joint::Joint(String name, uint16_t startAngle, uint16_t pulseMin, uint16_t pulseMax, uint16_t channel, Adafruit_PWMServoDriver *pwmObject) :
    jointName(name),
    currentAngle(startAngle),
    minPulseWidth(pulseMin),
    maxPulseWidth(pulseMax),
    targetAngle(startAngle),
    jointChannel(channel),
    pwm(pwmObject)
{
}

String Joint::setTargetAngle(int givenAngle)
{
    targetAngle = givenAngle;
    return "\n" + jointName + " target angle set to " + String(targetAngle);
}

void Joint::incrementPosition()
{
    if (currentAngle != targetAngle)
    {
        if (currentAngle < targetAngle) ++currentAngle;
        if (currentAngle > targetAngle) --currentAngle;
        pwm->setPWM(jointChannel, PULSE_ON, calculatePulseWidth(currentAngle));
        delay(INCREMENT_DELAY_USECS);
    }
}

int Joint::calculatePulseWidth(uint16_t angle)
{
    return map(angle, 0, 180, minPulseWidth, maxPulseWidth);
}