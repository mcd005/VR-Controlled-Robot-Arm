#include <ArduinoJson.h>

#include "ChassisControl.h"
#include "HBridgeDriver.h"
#include "Arm.h"
#include "SmallArm.h"
#include "BigArm.h"

#define DEBUG
#define PiSerial Serial2
#define Debug Serial

#define H1_ENA 1
#define H1_IN1 2
#define H1_IN2 3
#define H1_IN3 4
#define H1_IN4 5
#define H1_ENB 6

#define H2_ENA 7
#define H2_IN1 8
#define H2_IN2 9
#define H2_IN3 10
#define H2_IN4 11
#define H2_ENB 12


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

  chasisControl.begin();
}

void loop() 
{

  if (PiSerial.available() > 0)
  {   
      DeserializationError error = deserializeJson(controlDataJson, PiSerial);
      if (error) 
      {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
  }

  robotControl.handleChassis(controlDataJson);
  robotControl.handleSmallArm(controlDataJson);
  robotControl.handleBigArm(controlDataJson);

  Serial2.flush();
}
