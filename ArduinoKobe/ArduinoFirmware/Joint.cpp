
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#include "Joint.h"


#define PULSE_ON 15
#define INCREMENT_DELAY_USECS 0

Joint::Joint(String name, uint16_t startAngle, uint16_t pulseMin, uint16_t pulseMax, uint16_t channel, Adafruit_PWMServoDriver *pwmObject) :
    jointName(name),
    currentPulseWidth(calculatePulseWidth(startAngle)),
    minPulseWidth(pulseMin),
    maxPulseWidth(pulseMax),
    targetPulseWidth(calculatePulseWidth(startAngle)),
    jointChannel(channel),
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

/*
 NOT IMPLEMENTED IN THE BEST POSSIBLE WAY :/
 THESE METHODs should only receive a max_angle value
 and increment/decrement the angle whilst button is pressed (so no target pulse_widtho)
*/

void Joint::increaseAngle()
{   
    if (currentPulseWidth < maxPulseWidth) {
        ++currentPulseWidth;
        pwm->setPWM(jointChannel, PULSE_ON, currentPulseWidth);
        delay(INCREMENT_DELAY_USECS);
    }
}

void Joint::decreaseAngle()
{   
    if (currentPulseWidth > minPulseWidth) {
        --currentPulseWidth;
        pwm->setPWM(jointChannel, PULSE_ON, currentPulseWidth);
        delay(INCREMENT_DELAY_USECS);
    }
}
