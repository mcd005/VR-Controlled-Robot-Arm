// Robot control library
#pragma once

#include "BigArm.h"
#include "SmallArm.h"
#include "ChassisControl.h"

enum class ChassisDirection
{
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT,
    ROTATE_RIGHT,
    ROTATE_LEFT,
    STOP
}

enum class SmallArmData
{
    UP = 0,
    DOWN
}

class RobotControl
{
    public:
        RobotControl(BigArm bigArmControl, SmallArm smallArmControl, ChassisControl chassisControl);

        void handleControl(DynamicJsonDocument jsonData);

    private:
        int bigArmWristFlexor;
        int bigArmClaw;
        int bigArmWristRotator;
        int bigArmElbow;
        int bigArmShoulder;
        int chassisDirection;
        int smallArmDirection;

        BigArm bigArm;
        SmallArm smallArm;
        ChassisControl chassis;

        
        void parseData(DynamicJsonDocument jsonData);
        void handleChassisData();
        void handleSmallArmData();
        void handleBigArmData();
};
