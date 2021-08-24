#pragma once

#include "HBridgeDriver.h"
#include "Joint.hpp"

class SmallArm
{

public:
    SmallArm(Joint* baseServo, Joint* bendServo);

    ~SmallArm();

    Joint* _baseServo;
    Joint* _bendServo;

    void UP();
    void DOWN();

};