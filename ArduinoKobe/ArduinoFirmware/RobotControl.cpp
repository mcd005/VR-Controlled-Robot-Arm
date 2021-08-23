// class that takes care of handling smallArm, bigArm and chassisControl object movements
// has a function that returns which movement should be actuated

#include "BigArm.h"
#include "SmallArm.h"
#include "ChassisControl.h"

/*
How to prioritise between the different movements???
What if more than one is pressed simulatenously
*/

class RobotControl
{

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


    public:
        RobotControl(BigArm* bigArmControl, SmallArm* smallArmControl, ChassisControl* chassisControl) 
        {
            bigArm = bigArmControl;
            smallArm = smallArmControl;
            chassis = chassisControl;
        }

    // parse the data into the three different possible robot functionalities
    public void handleControl(string* jsonData) 
    {   
        // be able to handle if no data is sent 

        // 1. Parse the data
        parseData(&jsonData);

        // 2. Actuate the different parts
        handleBigArmData();
        handleChassisData();
        handleSmallArmData();
    }

    // parses the data
    void parseData(string* jsonData) {
        bigArmWristFlexor = jsonDic["bigArmWristFlexor"].as<int>();
        bigArmClaw = jsonDic["bigArmClaw"].as<int>();
        bigArmWristRotator = jsonDic["bigArmWristRotator"].as<int>();
        bigArmElbow = jsonDic["bigArmElbow"].as<int>();
        bigArmShoulder = jsonDic["bigArmShoulder"].as<int>();
        chassisDirection = jsonDic["chassisDirection"].as<int>();
        smallArmDirection = jsonDic["smallArmVerticalDirection"].as<int>();
    }

    void handleChassisData() {
        if(chassisDirection == 0) {
            chassis.Forward();
        }
        else if(chassisDirection == 1) {
            chassis.Backward();
        }
        else if(chassisDirection == 2) {
            chassis.Left();
        }
        else if(chassisDirection == 3) {
            chassis.Right();
        }
        else if(chassisDirection == 4) {
            chassis.RotateRight();
        }
        else if(chassisDirection == 5) {
            chassis.RotateLeft();
        }
        else if(chassisDirection == 6) {
            chassis.Stop();
        }
        else {
            Serial.println("Nothing");
        }
    }

    void handleSmallArmData() {
        if (smallArmDirection == 0 ) {
            smallArm.UP();
        } else if (smallArmDirection == 1 ) {
            smallArm.DOWN();
        } else {
            smallArm.Stop();
            Serial.println("Nothing");
        }
    }

    void handleBigArmData() {

        // set the angles for each of the Joints
        bigArm.setJointsTargetAngles(&bigArmWristFlexor, &bigArmClaw, &bigArmWristRotator, &bigArmElbow, &bigArmShoulder);

        // increment each servo to their angles
        bigArm.doJointsMovement();

    }


}