#include "HBridgeDriver.h"
#include "Arduino.h"

HBridgeDriver::HBridgeDriver(int ENA,
                            int IN1,
                            int IN2,
                            int IN3,
                            int IN4,
                            int ENB)
{
    _ENA = ENA;
    _IN1 = IN1;
    _IN2 = IN2;
    _IN3 = IN3;
    _IN4 = IN4;
    _ENB = ENB;
}

HBridgeDriver::~HBridgeDriver()
{

}

void HBridgeDriver::begin()
{
    pinMode(_ENA,OUTPUT);
    pinMode(_IN1,OUTPUT);
    pinMode(_IN2,OUTPUT);
    pinMode(_IN3,OUTPUT);
    pinMode(_IN4,OUTPUT);
    pinMode(_ENB,OUTPUT);
}




void HBridgeDriver::moveForward()
{
    //front left motor
    digitalWrite(_IN1, HIGH);
    digitalWrite(_IN2, LOW);

    //front right motor
    digitalWrite(_IN3, HIGH);
    digitalWrite(_IN4, LOW);

    digitalWrite(_ENA, HIGH);
    digitalWrite(_ENB, HIGH);
}

void HBridgeDriver::moveBackward()
{
    //front left motor
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);

    //front right motor
    digitalWrite(_IN3, LOW);
    digitalWrite(_IN4, HIGH);

    digitalWrite(_ENA, HIGH);
    digitalWrite(_ENB, HIGH);
}

void HBridgeDriver::turnLeft()
{
    //front left motor forward
    digitalWrite(_IN1, HIGH);
    digitalWrite(_IN2, LOW);
    // front left motor backward
    digitalWrite(_IN3, LOW);
    digitalWrite(_IN4, HIGH);
}

void HBridgeDriver::turnRight()
{
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
    // front left motor backward
    digitalWrite(_IN3, HIGH);
    digitalWrite(_IN4, LOW);
}

void HBridgeDriver::stop()
{
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, LOW);
    digitalWrite(_IN3, LOW);
    digitalWrite(_IN4, LOW); 
}
