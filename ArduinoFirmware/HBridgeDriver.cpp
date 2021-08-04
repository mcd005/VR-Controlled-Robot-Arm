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

HBridgeDriver::begin()
{
    pinMode(_ENA,OUTPUT);
    pinMode(_IN1,OUTPUT);
    pinMode(_IN2,OUTPUT);
    pinMode(_IN3,OUTPUT);
    pinMode(_IN4,OUTPUT);
    pinMode(_ENB,OUTPUT);
}


HBridgeDriver::~HBridgeDriver()
{

}

HBridgeDriver::moveForward()
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

HBridgeDriver::moveBackward()
{

}

HBridgeDriver::turnLeft()
{

}

HBridgeDriver::turnRight()
{

}

