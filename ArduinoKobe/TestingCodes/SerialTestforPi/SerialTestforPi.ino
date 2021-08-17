#include <Wire.h>

int incomingByte = 0; 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {

if(Serial.available() > 0) {
  incomingByte = Serial.parseInt();
//  Serial.write("I got your message");
}
}
