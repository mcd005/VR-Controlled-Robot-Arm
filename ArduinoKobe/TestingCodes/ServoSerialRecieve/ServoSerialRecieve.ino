#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // this is the 'maximum' pulse length count (out of 4096)
 
// our servo # counter
uint8_t servonum = 5;
int posRecieved;
 
void setup() {
  Serial.begin(9600);
  Serial.println("Send data from Serial Variable to servo motor");
 
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
 
}
 
 
void loop() {

   if (Serial.available() > 0){
      posRecieved = Serial.parseInt();       
      Serial.println(posRecieved);  

      pwm.setPWM(15, 15, posRecieved);  
      delay(100);
   }
}
