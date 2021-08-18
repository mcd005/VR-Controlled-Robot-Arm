#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // this is the 'maximum' pulse length count (out of 4096)
 
// our servo # counter
uint8_t servonum = 5;
 

void setup() {
  Serial.begin(9600);

 
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
 
  //yield();
}
 
 
void loop() { // 110 is min , 580 is max, 0 is 

    pwm.setPWM(0,0, 580);   //
    pwm.setPWM(1,0, 580); // was pot2
    pwm.setPWM(2,0, 580);
    pwm.setPWM(3,0, 580); 
delay(100);
}
