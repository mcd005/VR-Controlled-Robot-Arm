#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>
#include "Joint.hpp"

#define SerialMonitor Serial
#define Bluetooth Serial1
#define SERVO_FREQ 50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

Joint waist("waist", 90, 0, &pwm);
Joint shoulder("shoulder", 0, 1, &pwm);
Joint elbow("elbow", 0, 2, &pwm);
Joint pitch("pitch", 0, 3, &pwm);
Joint roll("roll", 0, 4, &pwm);
Joint claw("claw", 0, 5, &pwm);

void setup()
{
    SerialMonitor.begin(9600);
    SerialMonitor.setTimeout(3000);

    Bluetooth.begin(9600);
    Bluetooth.setTimeout(10);

    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQ);
    delay(10);
}

void loop()
{
    if (SerialMonitor.available())
    {
        // Expecting a comma seperated list of coords: W10,S50,E120 etc
        String inputSerial = SerialMonitor.readStringUntil(',');
        char jointID = inputSerial[0];
        int givenAngle = inputSerial.substring(1).toInt();

        if (jointID == 'W') Serial.println(waist.setTargetAngle(givenAngle));
        else if (jointID == 'S') Serial.println(shoulder.setTargetAngle(givenAngle));
        else if (jointID == 'E') Serial.println(elbow.setTargetAngle(givenAngle));
        else if (jointID == 'P') Serial.println(pitch.setTargetAngle(givenAngle));
        else if (jointID == 'R') Serial.println(roll.setTargetAngle(givenAngle));
        else if (jointID == 'C') Serial.println(claw.setTargetAngle(givenAngle));
        else Serial.println("Invalid joint");
    }
    waist.incrementPosition();
    shoulder.incrementPosition();
    elbow.incrementPosition();
    pitch.incrementPosition();
    roll.incrementPosition();
    claw.incrementPosition();
}
