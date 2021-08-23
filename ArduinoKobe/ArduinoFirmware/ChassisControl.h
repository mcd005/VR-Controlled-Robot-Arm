#pragma once

#include "HBridgeDriver.h"

class ChassisControl
{

public:
    ChassisControl(HBridgeDriver* FrontHbridge,HBridgeDriver* BackHBridge);

    ~ChassisControl();

    void begin();

    void Forward();
    void Backward();
    void Left();
    void Right();
    void RotateRight();
    void RotateLeft();
    void Stop();

private:

    HBridgeDriver* _FrontHbridge;
    HBridgeDriver* _BackHBridge;
};


