// Robot control library
#pragma once

#include "BigArm.h"
#include "SmallArm.h"
#include "ChassisControl.h"

class RobotControl
{
    public:
        RobotControl(BigArm* bigArmControl, SmallArm* smallArmControl, ChassisControl* chassisControl);

        void handleControl(string* jsonData);

    private:
        string jsonDic;

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

        void parseData(string* jsonData);
        void handleChassisData();
        void handleSmallArmData();
        void handleBigArmData();
};