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
public:
    Joint(String name, uint16_t startAngle, uint16_t minPulse, uint16_t maxPulse, uint16_t channel, Adafruit_PWMServoDriver* pwmObject); 
    String setTargetAngle(int givenAngle); 
    void incrementPosition(); 
    void timeIncreaseAngle()
    void timeDecreaseAngle()
    int Joint::calculatePulseWidth(uint16_t angle);
};