#include <ArduinoJson.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#include "ChassisControl.h"
#include "HBridgeDriver.h"
#include "Arm.h"
#include "SmallArm.h"
#include "BigArm.h"
#include "Joint.hpp"

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


ChassisControl chassisControl(&frontHbridge,&backHBridge);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

Joint waist("waist", 90, 150, 450, 0, &pwm);
Joint shoulder("shoulder", 0, 150, 450,  1, &pwm);
Joint elbow("elbow", 0, 150, 450, 2, &pwm);
Joint pitch("pitch", 0, 150, 450, 3, &pwm);
Joint roll("roll", 0, 150, 450, 4, &pwm);
Joint claw("claw", 0, 150, 450, 5, &pwm);

BigArm bigArm(&waist,&shoulder,&elbow,&pitch,&roll,&claw); 

RobotControl robotControl(&chasisControl,&smallArmControl, &bigArm);

DynamicJsonDocument controlDataJson(1024);

void setup() 
{
  Debug.begin(9600);
  PiSerial.begin(9600);

  Bluetooth.begin(9600);
  Bluetooth.setTimeout(10);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  bigArm.begin();

  chassisControl.begin();

}

void loop() 
{
  robotControl.handleControl(controlDataJson);
  Serial2.flush();
}

void serialEvent1() 
{
  while (Serial1.available()) 
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
  }
}
