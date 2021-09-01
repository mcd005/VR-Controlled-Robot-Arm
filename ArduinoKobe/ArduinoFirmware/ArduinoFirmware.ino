#include <ArduinoJson.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#include "ChassisControl.h"
#include "HBridgeDriver.h"
#include "SmallArm.h"
#include "BigArm.h"
#include "Joint.hpp"
#include "RobotControl.h"
#include "JointInfoStructs.hpp"

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


Adafruit_PWMServoDriver pwmDriver1 = Adafruit_PWMServoDriver(0x40); // has default adress
Adafruit_PWMServoDriver pwmDriver2 = Adafruit_PWMServoDriver(0x41); // the address of the pwmdriver needs to be changed

// TODO make sure Rishan is happy with these pulse widths

// Initialse servo pulse info as: {minPulseWidth, maxPulseWidth}
JointPulseWidthInfo bigServo { 100, 500 };
JointPulseWidthInfo smallServo { 150, 450 };

// TODO find out correct starting angles, ROM and offsets
// Initialise angle info for each joint as
// {
//     Start angle,
//     Min legal angle, given in terms of the servos ROM, as opposed to the frame of refrence of the joint
//     Max legal angle,
//     Offset angle (to account for frame of referance + misalignments during assembly e.g. servo horn etc)
//     Invert the given angle. In case a servo is on backwards for example
// }

JointAngleInfo waistAngles {0, 0, 180, 10, true };
JointAngleInfo shoulderAngles { 0, 0, 180, 45 + 10, false };
JointAngleInfo elbowAngles { 0, 50, 180, 90 + 10, false };
JointAngleInfo pitchAngles { 0, 0, 180, 10, false };
JointAngleInfo rollAngles { 0, 0, 180, 0, true };
JointAngleInfo clawAngles { 0, 20, 100, 0, false };
JointAngleInfo baseAngles { 0, 0, 20, 0, false };
JointAngleInfo bendAngles { 90, 0, 180, 0, false };

Joint waist("waist", waistAngles, bigServo, 0, &pwmDriver2);  //big
Joint shoulder("shoulder", shoulderAngles, bigServo,  1, &pwmDriver1); // big
Joint elbow("elbow", elbowAngles, bigServo, 2, &pwmDriver1); // big
Joint pitch("pitch", pitchAngles, smallServo, 3, &pwmDriver1); // small
Joint roll("roll", rollAngles, smallServo, 4, &pwmDriver2); // small
Joint claw("claw", clawAngles, smallServo, 5, &pwmDriver1); // small

Joint baseServo("baseServo", baseAngles, bigServo, 1, &pwmDriver2); // big
Joint bendServo("bendServo", bendAngles, bigServo, 0, &pwmDriver2);


BigArm bigArmControl(&waist,&shoulder,&elbow,&pitch,&roll,&claw); 

SmallArm smallArmControl(&baseServo, &bendServo);

ChassisControl chassisControl(&frontHbridge,&backHBridge);

RobotControl robotControl(&bigArmControl, &smallArmControl, &chassisControl);

DynamicJsonDocument controlDataJson(1024);

// when reset is called is just setup called or is the entire - it powers on and off
void setup() 
{
  Debug.begin(9600);
  PiSerial.begin(9600);

  Bluetooth.begin(9600);
  Bluetooth.setTimeout(1000);

  pwmDriver1.begin();
  pwmDriver1.setPWMFreq(SERVO_FREQ);

  pwmDriver2.begin();
  pwmDriver2.setPWMFreq(SERVO_FREQ);
  
//  bigArmControl.begin();
  chassisControl.begin();
}

void loop() 
{
  if (Bluetooth.available())
  {
    // Expecting a comma seperated list of coords: W10,S50,E120 etc
    String inputSerial = Bluetooth.readStringUntil(',');
    char jointID = inputSerial[0];
    int givenValue = inputSerial.substring(1).toInt();

    Serial.print(jointID);
    Serial.println(givenValue);

    // if (jointID == 'D')
    // {
    //   if (givenValue == 0) Serial.println(bendServo.setTargetAngle(60));
    //   if (givenValue == 1) Serial.println(bendServo.setTargetAngle(0));
    
    // else
    //   Serial.println("Invalid joint");
  }
}

bool isDeserializeJsonStringSuccessful()
{
  DeserializationError deserializationError;

    if (Bluetooth.available() > 0)
    {   
        deserializationError = deserializeJson(controlDataJson, Bluetooth);
        if (deserializationError) 
        {
          Debug.print(F("deserializeJson() failed: "));
          Debug.println(deserializationError.f_str());
          // if the data is not deserialise what happens ??? Old data?
          // see what deserializeJson does ?? nothing?
          return false;
        }
        return true;
    }
  return false;
}
