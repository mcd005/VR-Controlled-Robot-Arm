#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>

class Joint
{
private:
    String jointName;
    uint16_t currentPulseWidth;
    uint16_t targetPulseWidth;
    uint16_t jointChannel;
    uint16_t minPulseWidth;
    uint16_t maxPulseWidth;
    Adafruit_PWMServoDriver* pwm;

    int calculatePulseWidth(uint16_t angle);
public:
    Joint(String name, uint8_t startAngle, uint16_t minPulse, uint16_t maxPulse, uint8_t channel, Adafruit_PWMServoDriver* pwmObject); 
    String setTargetAngle(int givenAngle); 
    void incrementPosition(); 
};

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