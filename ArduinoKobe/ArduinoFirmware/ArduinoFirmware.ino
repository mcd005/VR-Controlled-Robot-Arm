#include <ArduinoJson.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#include "ChassisControl.h"
#include "HBridgeDriver.h"
#include "Arm.h"
#include "SmallArm.h"
#include "BigArm.h"
#include "Joint.hpp"
#include "RobotControl.h"

#define DEBUG
#define Debug Serial
#define Bluetooth Serial1
#define PiSerial Serial2

#define SERVO_FREQ 50


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




Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver();

// find out DEFAULT positions
Joint waist("waist", 0, 150, 450, 0, &pwm);
Joint shoulder("shoulder", 0, 150, 450,  1, &pwm);
Joint elbow("elbow", 0, 150, 450, 2, &pwm);
Joint pitch("pitch", 0, 150, 450, 3, &pwm);
Joint roll("roll", 0, 150, 450, 4, &pwm);
Joint claw("claw", 0, 150, 450, 5, &pwm);

Joint servo1("servo1", 0, 150, 450, 5, &pwm2);
Joint servo2();


// should they be in the setup?  (Lose pwr, reset, etc...) -- we need to address these comments
BigArm bigArmControl(&waist,&shoulder,&elbow,&pitch,&roll,&claw); 

SmallArm smallArmControl(&servo1,&servo2);

ChassisControl chassisControl(&frontHbridge,&backHBridge);

RobotControl robotControl(&chassisControl,&smallArmControl, &bigArmControl);

DynamicJsonDocument controlDataJson(1024);

// when reset is called is just setup called or is the entire - it powers on and off
void setup() 
{
  Debug.begin(9600);
  PiSerial.begin(9600);

  Bluetooth.begin(9600);
  Bluetooth.setTimeout(10);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  bigArm.begin();
  smallArmControl.begin();
  chassisControl.begin();
}

void loop() 
{
  if (isDeserializeJsonStringSuccessful())
  {
    robotControl.handleControl(controlDataJson);
  }

  Bluetooth.flush();
}

DeserializationError isDeserializeJsonStringSuccessful() 
{
  DeserializationError deserializationError;

  while (Bluetooth.available()) 
  {
    if (Bluetooth.available() > 0)
    {   
        deserializationError = deserializeJson(controlDataJson, Bluetooth);
        if (deserializationError) 
        {
          Debug.print(F("deserializeJson() failed: "));
          Debug.println(error.f_str());
          // if the data is not deserialise what happens ??? Old data?
          // see what deserializeJson does ?? nothing?
          //return;
        }
    }
  }
  return deserializationError;
}
