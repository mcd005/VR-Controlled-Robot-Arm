#include "ChasisControl.h"
#include "HBridgeDriver.h"
#include <ArduinoJson.h>


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


ChasisControl chasisControl(&frontHbridge,&backHBridge);


DynamicJsonDocument doc(1024);


void setup() 
{
  Serial.begin(9600);
  Serial2.begin(9600);
  chasisControl.begin();
  
}

void loop() 
{
  if (Serial2.available() > 0)
  {   
      DeserializationError error = deserializeJson(doc, Serial2);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      int WristFlexor = doc["bigArmWristFlexor"].as<int>();
      int bigArmClaw = doc["bigArmClaw"].as<int>();
      int bigArmWristRotator = doc["bigArmWristRotator"].as<int>();
      int bigArmElbow = doc["bigArmElbow"].as<int>();
      int bigArmShoulder = doc["bigArmShoulder"].as<int>();
      int chassisDirection = doc["chassisDirection"].as<int>();
      int smallArmDirection = doc["smallArmVerticalDirection"].as<int>();

      Serial.println("big arm data: " + String(WristFlexor));
      Serial.println("big arm wrist flexor: " + String(bigArmClaw));
      Serial.println("big arm wrist rotator: " + String(bigArmWristRotator));
      Serial.println("big arm elbow: " + String(bigArmElbow));
      Serial.println("big arm elbow: " + String(bigArmShoulder));
      Serial.println("chassis direction: " + String(chassisDirection));
      Serial.println("small arm direction: " + String(smallArmDirection));


      if(chassisDirection == 0) {
          chasisControl.Forward();
      }
      else if(chassisDirection == 1) {
          chasisControl.Backward();
      }
      else if(chassisDirection == 2) {
          chasisControl.Left();
      }
      else if(chassisDirection == 3) {
          chasisControl.Right();
      }
      else if(chassisDirection ==6) {
          chasisControl.Stop();
      }
      else {
        Serial.println("Nothing");
      }
  }
  Serial2.flush();
  //chasisControl.Forward();
}
