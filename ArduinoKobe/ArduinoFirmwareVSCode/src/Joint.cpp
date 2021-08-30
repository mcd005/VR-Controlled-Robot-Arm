#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include "Joint.hpp"
#include "JointInfoStructs.hpp"

#define PULSE_ON 15
#define INCREMENT_DELAY_USECS 10000

Joint::Joint(String name, JointAngleInfo givenAngleInfo, JointPulseWidthInfo givenPulseWidthInfo, uint8_t channel, Adafruit_PWMServoDriver *pwmObject) :
    jointName(name),
    angleTransformer(givenAngleInfo),
    currentPulseWidth(calculatePulseWidth(givenAngleInfo.startAngle)),
    targetPulseWidth(calculatePulseWidth(givenAngleInfo.startAngle)),
    minPulseWidth(givenPulseWidthInfo.minPulseWidth),
    maxPulseWidth(givenPulseWidthInfo.maxPulseWidth),
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
    if (isTimeToMove() && (currentPulseWidth != targetPulseWidth))
    {
        if (currentPulseWidth < targetPulseWidth) ++currentPulseWidth;
        if (currentPulseWidth > targetPulseWidth) --currentPulseWidth;
        pwm->setPWM(jointChannel, PULSE_ON, currentPulseWidth);
    }
}

int Joint::calculatePulseWidth(uint16_t angle)
{
    return map(angleTransformer.transfromAngle(angle), 0, 180, minPulseWidth, maxPulseWidth);
}

bool Joint::isTimeToMove()
{
    unsigned long currentTime = micros(); // Be careful, this will overflow after 70 mins
    if (currentTime - previousTimeJointWasIncremented > INCREMENT_DELAY_USECS)
    {
        previousTimeJointWasIncremented = currentTime;
        return true;
    }
    return false;
}