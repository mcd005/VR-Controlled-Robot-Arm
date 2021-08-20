#include "ChasisControl.h"

ChasisControl::ChasisControl(HBridgeDriver* frontHbridge,HBridgeDriver* backHBridge)
{
    _FrontHbridge = frontHbridge;
    _BackHBridge = backHBridge;
}

ChasisControl::~ChasisControl()
{
}

void ChasisControl::begin()
{
    _FrontHbridge->begin();
    _BackHBridge->begin();
}

void ChasisControl::Forward()
{
    _FrontHbridge->moveForward();
    _BackHBridge->moveForward();
}

void ChasisControl::Backward()
{
    _FrontHbridge->moveBackward();
    _BackHBridge->moveBackward();
}

void ChasisControl::Left()
{
    _FrontHbridge->turnLeft();
    _BackHBridge->turnRight();
}

void ChasisControl::Right()
{
    _FrontHbridge->turnRight();
    _BackHBridge->turnLeft();
}

void ChasisControl::Stop()
{
    _FrontHbridge->stop();
    _BackHBridge->stop();
}