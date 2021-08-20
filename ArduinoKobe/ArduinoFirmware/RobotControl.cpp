// class that takes care of handling smallArm, bigArm and chassisControl object movements
// has a function that returns which movement should be actuated
#include <map>

#include "BigArm.h"
#include "ChassisControl.h"

/*
How to prioritise between the different movements???
What if more than one is pressed simulatenously
*/

class RobotControl
{

    string jsonDic;

    int WristFlexor;
    int bigArmClaw;
    int bigArmWristRotator;
    int bigArmElbow;
    int bigArmShoulder;
    int chassisDirection;
    int smallArmDirection;
    
    // dictionary that holds the movements that robot should do at this time:
    std::map<std::string, std::string> movementsNeeded;
    movementsNeeded["chassis"] = 6;
    movemensNeeded["smallArm"] = 2;
    movementNeeded["bigArm"] = std::map<std::string, std::int>;


    public:
        RobotControl(string* jsonData) 
        {
            jsonDic = jsonData;
        }

    // parse the data into the three different possible robot functionalities
    string handleControl() 
    {
        // will return which data has
        WristFlexor = jsonDic["bigArmWristFlexor"].as<int>();
        bigArmClaw = jsonDic["bigArmClaw"].as<int>();
        bigArmWristRotator = jsonDic["bigArmWristRotator"].as<int>();
        bigArmElbow = jsonDic["bigArmElbow"].as<int>();
        bigArmShoulder = jsonDic["bigArmShoulder"].as<int>();
        chassisDirection = jsonDic["chassisDirection"].as<int>();
        smallArmDirection = jsonDic["smallArmVerticalDirection"].as<int>();

        return "(chassis, forward)"
        return movementNeeded;
    }

    void handleChassisData() {
        if(chassisDirection == 0) {
          chassisControl.Forward();
        }
        else if(chassisDirection == 1) {
            chassisControl.Backward();
        }
        else if(chassisDirection == 2) {
            chassisControl.Left();
        }
        else if(chassisDirection == 3) {
            chassisControl.Right();
        }
        else if(chassisDirection == 4) {
            chassisControl.RotateRight();
        }
        else if(chassisDirection == 5) {
            chassisControl.RotateLeft();
        }
        else if(chassisDirection ==6) {
            chassisControl.Stop();
        }
        else {
            Serial.println("Nothing");
        }
    }

    void handleSmallArmData() {
        if (smallArmDirection == 0 ) {
            smallArmControl.UP();
        } else if (smallArmDirection == 1 ) {
            smallArmControl.DOWN();
        } else {
            Serial.println("Nothing");
        }
    }

    void handleBigArmData() {
        // Joints data ... 
    }


}