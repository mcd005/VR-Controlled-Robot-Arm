#include <ArduinoJson.h>

#include "ChassisControl.h"
#include "HBridgeDriver.h"
#include "Arm.h"
#include "SmallArm.h"
#include "BigArm.h"

#define DEBUG
#define PiSerial Serial2
#define Debug Serial

#define H1_ENA 35
#define H1_IN1 32
#define H1_IN2 34
#define H1_IN3 36
#define H1_IN4 38
#define H1_ENB 37


#define H2_ENA 25
#define H2_IN1 22
#define H2_IN2 24
#define H2_IN3 26
#define H2_IN4 28
#define H2_ENB 27


HBridgeDriver frontHbridge(H1_ENA,
                          H1_IN1,
                          H1_IN2,
                          H1_IN3,
                          H1_IN4,
                          H1_ENB);

HBridgeDriver backHBridge(H2_ENA,
                          H2_IN1,
                          H2_IN2,
                          H2_IN3,
                          H2_IN4,
                          H2_ENB);


ChassisControl chassisControl(&frontHbridge,&backHBridge);

// there should be two of these 
Arm armControl("need to add PWM driver here")
SmallArm smallArmControl()
BigArm bigArmControl()

RobotControl robotControl(&chasisControl,&smallArmControl, &bigArmControl);

void setup() 
{

DynamicJsonDocument controlDataJson(1024);

void setup() 
{
  Debug.begin(9600);
  PiSerial.begin(9600);

  chassisControl.begin();
}

void loop() 
{

  if (PiSerial.available() > 0)
  {   
      DeserializationError error = deserializeJson(controlDataJson, PiSerial);
      if (error) 
      {
        Debug.print(F("deserializeJson() failed: "));
        Debug.println(error.f_str());
        return;
      }
  }

  robotControl.handleChassis(controlDataJson);
  robotControl.handleSmallArm(controlDataJson);
  robotControl.handleBigArm(controlDataJson);

  Serial2.flush();
}
