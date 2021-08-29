#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>

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

class Joint
{
private:
    String jointName;
    uint16_t currentPulseWidth;
    uint16_t targetPulseWidth;
    uint16_t minPulseWidth;
    uint16_t maxPulseWidth;
    uint16_t jointChannel;
    Adafruit_PWMServoDriver* pwm;

    int calculatePulseWidth(uint16_t angle);
public:
    Joint(String name, JointAngleInfo angleInfo, JointPulseWidthInfo pulseWidthInfo, uint8_t channel, Adafruit_PWMServoDriver* pwmObject); 
    String setTargetAngle(int givenAngle); 
    void incrementPosition(); 
};