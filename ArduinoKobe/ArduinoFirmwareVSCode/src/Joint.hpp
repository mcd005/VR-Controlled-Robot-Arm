#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>
#include "JointInfoStructs.hpp"
#include "AngleTransformer.hpp"

class Joint
{
private:
    String jointName;
    AngleTransformer angleTransformer;
    uint16_t currentPulseWidth;
    uint16_t targetPulseWidth;
    const uint16_t minPulseWidth;
    const uint16_t maxPulseWidth;
    const uint16_t jointChannel;
    Adafruit_PWMServoDriver* pwm;
    unsigned long previousTimeJointWasIncremented = 0;

    int calculatePulseWidth(uint16_t angle);
    bool isTimeToMove();
public:
    Joint(String name, JointAngleInfo angleInfo, JointPulseWidthInfo pulseWidthInfo, uint8_t channel, Adafruit_PWMServoDriver* pwmObject); 
    String setTargetAngle(int givenAngle); 
    void incrementPosition(); 
};