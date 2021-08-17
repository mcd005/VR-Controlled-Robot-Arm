#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
 
// our servo # counter
uint8_t servonum = 5;
int posRecieved = 0;
double pulselength;
 
void setup() {
  Serial.begin(9600);
  Serial.println("Send angle from serial to servo");
 
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
 
  //yield();
}

 
void loop() {
Serial.print("serial avilble");
Serial.println(Serial.available());

if (Serial.available() > 1){
  posRecieved = Serial.parseInt();
  Serial.print("Pos received: "); 
  Serial.println(posRecieved);
  pulselength = map(posRecieved, 0, 180, SERVOMIN, SERVOMAX);
  Serial.print("Pulselength: ");
  Serial.println(pulselength);
  pwm.setPWM(1,0, pulselength);
  
}

delay(100);
}
