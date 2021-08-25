// class that takes care of handling smallArm, bigArm and chassisControl object movements
// has a function that returns which movement should be actuated
#include <ArduinoJson.h>

#include "BigArm.h"
#include "SmallArm.h"
#include "ChassisControl.h"
#include "RobotControl.h"

/*
How to prioritise between the different movements???
What if more than one is pressed simulatenously - I guess we need to do some brain storming
*/


RobotControl::RobotControl(BigArm* bigArmControl, SmallArm* smallArmControl, ChassisControl* chassisControl) 
{
    bigArm = bigArmControl;
    smallArm = smallArmControl;
    chassis = chassisControl;
}

// parse the data into the three different possible robot functionalities
void RobotControl::handleControl(DynamicJsonDocument jsonData) // I dont think its a json string - its a DynamicJsonDocument - this where its trickey because the library is installed in arduino
{   
    // be able to handle if no data is sent 

    // 1. Parse the data
    parseData(jsonData);

    // 2. Actuate the different parts
    handleBigArmData();
    handleChassisData();
    handleSmallArmData();
}

    // parses the data
void RobotControl::parseData(DynamicJsonDocument jsonData) 
{
    bigArmWristFlexor = jsonData["bigArmWristFlexor"].as<int>();
    bigArmClaw = jsonData["bigArmClaw"].as<int>();
    bigArmWristRotator = jsonData["bigArmWristRotator"].as<int>();
    bigArmElbow = jsonData["bigArmElbow"].as<int>();
    bigArmShoulder = jsonData["bigArmShoulder"].as<int>();
    chassisDirection = jsonData["chassisDirection"].as<int>();
    smallArmDirection = jsonData["smallArmVerticalDirection"].as<int>();
}

void RobotControl::handleChassisData() 
{ 
    // if chassis direction 
    if(static_cast<int>(ChassisDirection::FORWARD) == chassisDirection) 
    {
        chassis->Forward();
    }
    else if(static_cast<int>(ChassisDirection::BACKWARD) == chassisDirection) 
    {
        chassis->Backward();
    }
    else if(static_cast<int>(ChassisDirection::LEFT) == chassisDirection) 
    {
        chassis->Left();
    }
    else if(static_cast<int>(ChassisDirection::RIGHT) == chassisDirection) 
    {
        chassis->Right();
    }
    else if(static_cast<int>(ChassisDirection::ROTATE_RIGHT) == chassisDirection)
    {
        chassis->RotateRight();
    }
    else if(static_cast<int>(ChassisDirection::ROTATE_LEFT) == chassisDirection) 
    {
        chassis->RotateLeft();
    }
    else if(static_cast<int>(ChassisDirection::STOP) == chassisDirection) 
    {
        chassis->Stop();
    }
    else 
    {
        Serial.println("Nothing");
    }
}

void RobotControl::handleSmallArmData() 
{
    if (static_cast<int>(SmallArmData::UP) == smallArmDirection) 
    {
        smallArm->UP();
    } 
    else if (static_cast<int>(SmallArmData::DOWN) == smallArmDirection) 
    {
        smallArm->DOWN();
    }
}

void RobotControl::handleBigArmData() 
{
    // set the angles for each of the Joints
    bigArm->setJointsTargetAngles(bigArmWristFlexor, bigArmClaw, bigArmWristRotator, bigArmElbow, bigArmShoulder);

    // increment each servo to their angles
    bigArm->doJointsMovement();
}
