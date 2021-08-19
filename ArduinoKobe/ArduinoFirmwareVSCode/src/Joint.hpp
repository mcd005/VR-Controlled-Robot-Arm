#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>

class Joint
{
private:
    String jointName;
    uint16_t currentAngle;
    uint16_t targetAngle;
    uint16_t jointChannel;
    Adafruit_PWMServoDriver* pwm;
public:
    Joint(String name, uint16_t startAngle, uint16_t channel, Adafruit_PWMServoDriver* pwmObject); 
    String setTargetAngle(int givenAngle); 
    void incrementPosition(); 
    int Joint::calculatePulseWidth(uint16_t angle);
};