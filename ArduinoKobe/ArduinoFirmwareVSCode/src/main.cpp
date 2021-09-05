#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>
#include "Joint.hpp"
#include "JointInfoStructs.hpp"

#define SerialMonitor Serial
#define Bluetooth Serial1
#define SERVO_FREQ 50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Initialse servo pulse info as: {minPulseWidth, maxPulseWidth}
JointPulseWidthInfo bigServo { 100, 500 };
JointPulseWidthInfo smallServo { 150, 450 };

// Initialise angle infor for each joint as 
// {
//     Start angle,
//     Min legal angle, given in terms of the servos ROM, as opposed to the frame of refrence of the joint
//     Max legal angle,
//     Offset angle (to account for frame of referance + misalignments during assembly e.g. servo horn etc)
//     Invert the given angle. In case a servo is on backwards for example
// }

JointAngleInfo waistAngles { 90, 0, 180, 15, true };
JointAngleInfo shoulderAngles { 90, 0, 180, 45 + 10, false };
JointAngleInfo elbowAngles { 90, 50, 180, 90 + 10, false };
JointAngleInfo pitchAngles { 90, 0, 180, 10, false };
JointAngleInfo rollAngles { 90, 0, 180, 0, true };
JointAngleInfo clawAngles { 70, 20, 100, 0, false };

// Instantiate all arm joints
Joint waist("waist", waistAngles, bigServo, 0, &pwm);
Joint shoulder("shoulder", shoulderAngles, bigServo, 1, &pwm);
Joint elbow("elbow", elbowAngles, bigServo, 2, &pwm);
Joint pitch("pitch", pitchAngles, smallServo, 3, &pwm);
Joint roll("roll", rollAngles, smallServo, 4, &pwm);
Joint claw("claw", clawAngles, smallServo, 5, &pwm);

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
    if (Bluetooth.available())
    {
        // Expecting a comma seperated list of coords: W10,S50,E120 etc
        String inputSerial = Bluetooth.readStringUntil(',');
        char jointID = inputSerial[0];
        int givenAngle = inputSerial.substring(1).toInt();

        String actuatorResponse;
        if (jointID == 'W') actuatorResponse = waist.setTargetAngle(givenAngle);
        else if (jointID == 'S') actuatorResponse = shoulder.setTargetAngle(givenAngle);
        else if (jointID == 'E') actuatorResponse = elbow.setTargetAngle(givenAngle);
        else if (jointID == 'P') actuatorResponse = pitch.setTargetAngle(givenAngle);
        else if (jointID == 'R') actuatorResponse = roll.setTargetAngle(givenAngle);
        else if (jointID == 'C') actuatorResponse = claw.setTargetAngle(givenAngle);
        else if (jointID == 'K' || jointID == 'D') actuatorResponse = "Unassigned joint";
        else actuatorResponse = "Invalid joint";
        Serial.println(actuatorResponse);
    }
    waist.incrementPosition();
    shoulder.incrementPosition();
    elbow.incrementPosition();
    pitch.incrementPosition();
    roll.incrementPosition();
    claw.incrementPosition();
}
