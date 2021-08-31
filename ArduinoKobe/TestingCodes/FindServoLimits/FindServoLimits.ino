#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int servoChannel = 0;
void setup()
{
    Serial.begin(9600);

    Serial.setTimeout(750);
    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
    delay(10);
}

void loop()
{
    if (Serial.available())
    {
        String serialInput = Serial.readStringUntil(";");
        int pulseWidth = serialInput.toInt();
        pwm.setPWM(servoChannel, 0, pulseWidth);
    }
}