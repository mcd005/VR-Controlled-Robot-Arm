#include "Arm.h"

#define leftArmSelector1 11
#define leftArmSelector2 12
#define leftArmSelector3 13
#define leftArmSelector4 14
#define leftArmSelector5 15



Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();


Arm leftArm(pwmDriver,
            leftArmSelector1,
            leftArmSelector2,
            leftArmSelector3,
            leftArmSelector4,
            leftArmSelector5,
            );


Arm rightArm(pwmDriver);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  leftArm.moveLeft();

  Serial.println("Hello");
  delay(1000);
}
