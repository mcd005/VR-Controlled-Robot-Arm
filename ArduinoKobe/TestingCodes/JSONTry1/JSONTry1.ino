#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Joint.hpp"

Joint shoulder("shoulder", 0, 0);
Joint elbow("elbow", 0, 1);
Joint wrist("wrist", 0, 2);
Joint rotationWrist("rotationWrist", 0, 3);
Joint claw("claw", 0, 4);


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
DynamicJsonDocument doc(1024);

#define S_SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096) for shoulder
#define S_SERVOREST 405 // 'middle or rest' pulse length count (out of 4096) for shoulder
#define S_SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096) for shoulder

#define E_SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096) for Elbow
#define E_SERVOREST 220 // 'middle or rest' pulse length count (out of 4096) for Elbow
#define E_SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096) for Elbow

#define W_SERVOMIN  170 // this is the 'minimum' pulse length count (out of 4096) for Wrist Flexor
#define W_SERVOREST 170 // 'middle or rest' pulse length count (out of 4096) for Wrist Flexor
#define W_SERVOMAX  530 // this is the 'maximum' pulse length count (out of 4096) for Wrist Flexor

#define R_SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096) for Wrist Rotation
#define R_SERVOREST 150 // Rest is 150 too
#define R_SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096) for Wrist Rotation

#define C_SERVOMIN 150 // this is the 'minimum' pulse length count (out of 4096) for Claw
#define C_SERVOREST 150 // Rest is 150 too
#define C_SERVOMAX 284 // this is the 'maximum' pulse length count (out of 4096) for Claw

int posRecieved = 0;
double pulselength;
int wristAngle;

String inputString = "";
bool stringComplete = false;

void setup() {
  // Initialize serial port
  Serial.begin(9600); // Main bus to PC
  Serial1.begin(9600); // to servo shield
  Serial2.begin(9600); //Pi
  
  while (!Serial) continue;

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  Serial.println("Resting Position");

  pwm.setPWM(0,0, S_SERVOREST);
  pwm.setPWM(1,0, E_SERVOREST);
  pwm.setPWM(2,0, W_SERVOREST);
  pwm.setPWM(3,0, R_SERVOREST);
  pwm.setPWM(4,0, C_SERVOREST);

  int shoulderAngle = map(S_SERVOREST, S_SERVOMIN, S_SERVOMAX, 0, 180);
  int elbowAngle = map(E_SERVOREST, E_SERVOMIN, E_SERVOMAX, 0, 180);
  wristAngle = map(W_SERVOREST, W_SERVOMIN, W_SERVOMAX, 0, 180);
  int roationWristAngle = map(R_SERVOREST, R_SERVOMIN, R_SERVOMAX, 0, 180);
  int clawAngle = map(C_SERVOREST, C_SERVOMIN, C_SERVOMAX, 0, 180);
}

void loop() {

  // Deserialize the JSON document
  if (Serial2.available() > 0)
  {   
      DeserializationError error = deserializeJson(doc, Serial2);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      int Shoulder = doc["bigArmShoulder"].as<int>();
      int Claw = doc["bigArmClaw"].as<int>();
      int Elbow = doc["bigArmElbow"].as<int>();
      int WristFlexor = doc["bigArmWristFlexor"].as<int>();
      int WristRotator = doc["bigArmWristRotator"].as<int>();
      int chassisDirection = doc["chassisDirection"].as<int>();
      int smallArmVerticalDirection = doc["smallArmVerticalDirection"].as<int>();

      Serial.println("big arm Wrist Rotator: " + String(WristRotator));
      Serial.println("big arm wrist flexor: " + String(WristFlexor));
      Serial.println("big arm shoulder: " + String(Shoulder));
      Serial.println("big arm Elbow: " + String(Elbow));
      Serial.println("chassisDirection: " + String(chassisDirection));
      Serial.println("smallArmVerticalDirection: " + String(smallArmVerticalDirection));
  }
  Serial2.flush();



//
// Serial2.println(WristFlexor);
// 
//  int startAngle = wristAngle;
//   int finalAngle = map(WristFlexor, 0, 180, W_SERVOMIN, W_SERVOMAX);
//   for (uint16_t angle = startAngle; angle < finalAngle; angle++) // This needs to be for bigger and smaller angles
//      {
//        pwm.setPWM(3,0, angle);
//        delay(30);
//        wristAngle = finalAngle;
//      }

}

//void serialEvent2() {
//  while (Serial2.available()) {
//
//    char inChar = (char)Serial2.read();
//    inputString += inChar;
//    if (inChar == '\n') {
//      stringComplete = true;
//    }
//  }
//}
  
