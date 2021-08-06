#include "ChasisControl.h"
#include "HBridgeDriver.h"

#define H1_ENA 1
#define H1_IN1 2
#define H1_IN2 3
#define H1_IN3 4
#define H1_IN4 5
#define H1_ENB 6

#define H2_ENA 7
#define H2_IN1 8
#define H2_IN2 9
#define H2_IN3 10
#define H2_IN4 11
#define H2_ENB 12


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


void setup() 
{
  chasisControl.begin();
}


void loop()
{
    // move forward
    chasisControl.Forward();
    delay(1000);

    // move back
     chasisControl.Backward();
     delay(1000);

    // move right
    chasisControl.Right();
    delay(1000);

    // move left
    chasisControl.Left();
    delay(1000);

    // stop
    chasisControl.Stop();
    delay(1000);
}