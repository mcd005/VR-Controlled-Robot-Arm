#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Joint.hpp"
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 

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
int shoulderAngle;
int elbowAngle;
int wristAngle;
int rotationWristAngle;
int clawAngle;

void setup() {
  Serial.begin(9600);
  Serial.println("Send angle from serial to servo");
 
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
 
  Serial.println("Resting Position");

  pwm.setPWM(0,0, S_SERVOREST);
  pwm.setPWM(1,0, E_SERVOREST);
  pwm.setPWM(2,0, W_SERVOREST);
  pwm.setPWM(3,0, R_SERVOREST);
  pwm.setPWM(4,0, C_SERVOREST);


  int shoulderAngle = map(S_SERVOREST, S_SERVOMIN, S_SERVOMAX, 0, 180);
  Serial.println(shoulderAngle);
  int elbowAngle = map(E_SERVOREST, E_SERVOMIN, E_SERVOMAX, 0, 180);
  Serial.println(elbowAngle);
  int wristAngle = map(W_SERVOREST, W_SERVOMIN, W_SERVOMAX, 0, 180);
  Serial.println(wristAngle);
  int roationWristAngle = map(R_SERVOREST, R_SERVOMIN, R_SERVOMAX, 0, 180);
  Serial.println(rotationWristAngle);
  int clawAngle = map(C_SERVOREST, C_SERVOMIN, C_SERVOMAX, 0, 180);
  Serial.println(clawAngle);
}

void loop() {
  

if (Serial.available() > 1) {

  String inputFromSerial = Serial.readString();
  char joint = inputFromSerial[0];
  String angleString = inputFromSerial.substring(1);
  int angle = angleString.toInt(); 
  Serial.println(joint);
  Serial.println(angle);

    if (joint == 'S') {
      int startAngle = shoulderAngle;
      int finalAngle = map(angle, 0, 180, S_SERVOMIN, S_SERVOMAX);
      for (uint16_t angle = startAngle; angle < finalAngle; angle++) // This needs to be for bigger and smaller angles
      {
        pwm.setPWM(0,0,angle);
        delay(30);
        shoulderAngle = finalAngle;
      }
      Serial.println("Shoulder moved");
  }

    if (joint == 'E') {
      int startAngle = elbowAngle;
      int finalAngle = map(angle, 0, 180, E_SERVOMIN, E_SERVOMAX);
      for (uint16_t angle = startAngle; angle < finalAngle; angle++) // This needs to be for bigger and smaller angles
      {
        pwm.setPWM(1,0,angle);
        delay(30);
        elbowAngle = finalAngle; 
      }
      Serial.println("Elbow moved");
  }

    if (joint == 'W') {
      Joint joint("",0,10);
      int startAngle = wristAngle;
      int startPulseWidth = joint.calculatePulseWidth(0);
      Serial.println(startPulseWidth);
      int finalPulseWidth = joint.calculatePulseWidth(angle);
            Serial.println(finalPulseWidth);
//  int  pulseDurationUsec = map(angle, 0, 180, W_SERVOMIN, W_SERVOMAX);
//    Serial.println(pulseDurationUsec);
//   int pulse_Width = map(pulseDurationUsec, W_SERVOMIN, W_SERVOMAX, 0, 4096);
//    Serial.println(pulse_Width);
      for (uint16_t pulseWidth = startPulseWidth; pulseWidth < finalPulseWidth; pulseWidth++)
      {
        pwm.setPWM(2,0,pulseWidth);
        delay(30);
       Serial.println(pulseWidth);
      }
      Serial.println("Wrist moved");
  }
  
    if (joint == 'R') {
      int startAngle = rotationWristAngle;
      int finalAngle = map(angle, 0, 180, R_SERVOMIN, R_SERVOMAX);
      for (uint16_t angle = startAngle; angle < finalAngle; angle++)
      {
        pwm.setPWM(3,0,angle);
        delay(30);
        rotationWristAngle = finalAngle;
      }
      Serial.println("Rotated Wrist");
  }

    if (joint == 'C') {
      int startAngle = clawAngle;
      int finalAngle = map(angle, 0, 50, C_SERVOMIN, C_SERVOMAX);
      for (uint16_t angle = startAngle; angle < finalAngle; angle++)
      {
        pwm.setPWM(4,0,angle);
        delay(30);
        clawAngle = finalAngle;
      }
      Serial.println("Claw moved");
  }
}
delay(100);
}
