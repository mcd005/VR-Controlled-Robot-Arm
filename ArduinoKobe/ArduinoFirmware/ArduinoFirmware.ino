#include <ArduinoJson.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#include "ChassisControl.h"
#include "HBridgeDriver.h"
#include "SmallArm.h"
#include "BigArm.h"
#include "Joint.h"
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

#define SMALL_ARM_MAX_PULSE_WIDTH 200 // angle of 20 degree 
#define SMALL_ARM_MIN_PULSE_WIDTH 150 // angle of 0


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


Adafruit_PWMServoDriver pwmDriver1 = Adafruit_PWMServoDriver(0x40); // has default adress
Adafruit_PWMServoDriver pwmDriver2 = Adafruit_PWMServoDriver(0x41); // the address of the pwmdriver needs to be changed

// find out DEFAULT positions
Joint waist("waist", 0, 150, 450, 0, &pwmDriver2);  //big 
Joint shoulder("shoulder", 0, 150, 450,  1, &pwmDriver1); // big
Joint elbow("elbow", 0, 150, 450, 2, &pwmDriver1); // big
Joint pitch("pitch", 0, 150, 450, 3, &pwmDriver1); // small
Joint roll("roll", 0, 150, 450, 4, &pwmDriver2); // small
Joint claw("claw", 0, 150, 450, 5, &pwmDriver1); // small

Joint baseServo("baseServo", 0, 150, SMALL_ARM_MAX_PULSE_WIDTH, 6, &pwmDriver2); // big
Joint bendServo("bendServo", 0, 150, SMALL_ARM_MAX_PULSE_WIDTH, 7, &pwmDriver2); // small


BigArm bigArmControl(&waist,&shoulder,&elbow,&pitch,&roll,&claw); 

SmallArm smallArmControl(&baseServo, &bendServo);

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

  pwmDriver1.begin();
  pwmDriver1.setPWMFreq(SERVO_FREQ);

  pwmDriver2.begin();
  pwmDriver2.setPWMFreq(SERVO_FREQ);
  
  bigArmControl.begin();
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
          return deserializationError;
        }
    }
  }
  return deserializationError;
}
