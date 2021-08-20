// class that takes care of handling smallArm, bigArm and chassisControl object movements

#include "ChassisControl.h"

class RobotControl
{
    ChassisControl chassisControl;
    SmallArm smallArmControl;
    BigArm bigArmControl;


    public:
        RobotControl(ChassisControl chassis, SmallArm smallArm, BigArm bigArm) 
        {
            chassisControl = chassis;
            smallArmControl = smallArm;
            bigArmControl = bigArm;
        }

    void handleChassis() {

    }

    void handleSmallArm() {

    }

    void handleBigArm() {

    }
}