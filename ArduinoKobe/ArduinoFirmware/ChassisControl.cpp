#include "ChassisControl.h"

ChassisControl::ChassisControl(HBridgeDriver* frontHbridge,HBridgeDriver* backHBridge)
{
    _FrontHbridge = frontHbridge;
    _BackHBridge = backHBridge;
}

ChassisControl::~ChassisControl()
{
}

void ChassisControl::begin()
{
    _FrontHbridge->begin();
    _BackHBridge->begin();
}

/*
* Unit test: https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
*/

void ChassisControl::Forward()
{
    _FrontHbridge->moveForward();
    _BackHBridge->moveForward();
}

void ChassisControl::Backward()
{
    _FrontHbridge->moveBackward();
    _BackHBridge->moveBackward();
}

void ChassisControl::Left()
{
    _FrontHbridge->turnLeft();
    _BackHBridge->turnRight();
}

void ChassisControl::Right()
{
    _FrontHbridge->turnRight();
    _BackHBridge->turnLeft();
}

void ChassisControl::RotateLeft()
{
     _FrontHbridge->turnRight();
      _BackHBridge->turnRight();
}

void ChassisControl::RotateRight()
{
     _FrontHbridge->turnLeft();
     _BackHBridge->turnLeft();
}

void ChassisControl::Stop()
{
    _FrontHbridge->stop();
    _BackHBridge->stop();
}
