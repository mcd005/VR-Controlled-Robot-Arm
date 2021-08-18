#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define S_SERVOMIN 150  // this is the 'minimum' pulse length count (out of 4096) for shoulder
#define S_SERVOREST 405 // 'middle or rest' pulse length count (out of 4096) for shoulder
#define S_SERVOMAX 600  // this is the 'maximum' pulse length count (out of 4096) for shoulder

#define E_SERVOMIN 150  // this is the 'minimum' pulse length count (out of 4096) for Elbow
#define E_SERVOREST 220 // 'middle or rest' pulse length count (out of 4096) for Elbow
#define E_SERVOMAX 600  // this is the 'maximum' pulse length count (out of 4096) for Elbow

#define W_SERVOMIN 160  // this is the 'minimum' pulse length count (out of 4096) for Wrist Flexor
#define W_SERVOREST 405 // 'middle or rest' pulse length count (out of 4096) for Wrist Flexor
#define W_SERVOMAX 530  // this is the 'maximum' pulse length count (out of 4096) for Wrist Flexor

#define R_SERVOMIN 150  // this is the 'minimum' pulse length count (out of 4096) for Wrist Rotation
#define R_SERVOREST 350 //CHANGE NEED TO FIND
#define R_SERVOMAX 600  // this is the 'maximum' pulse length count (out of 4096) for Wrist Rotation

#define C_SERVOMIN 144  // this is the 'minimum' pulse length count (out of 4096) for Claw
#define C_SERVOREST 350 // CHANGE NEED TO FIND
#define C_SERVOMAX 500  // this is the 'maximum' pulse length count (out of 4096) for Claw

int posRecieved = 0;
double pulselength;
int shoulderAngle;
int elbowAngle;
int wristAngle;
int rotationWristAngle;
int clawAngle;

void setup()
{
    Serial.begin(9600);
    Serial.println("Send angle from serial to servo");

    pwm.begin();
    pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates

    Serial.println("Resting Position");

    pwm.setPWM(0, 0, S_SERVOREST);
    pwm.setPWM(1, 0, E_SERVOREST);
    pwm.setPWM(2, 0, W_SERVOREST);
    pwm.setPWM(3, 0, R_SERVOREST);
    pwm.setPWM(4, 0, C_SERVOREST);

    int shoulderAngle = map(S_SERVOREST, S_SERVOMIN, S_SERVOMAX, 0, 180);
    int elbowAngle = map(E_SERVOREST, E_SERVOMIN, E_SERVOMAX, 0, 180);
    int wristAngle = map(W_SERVOREST, W_SERVOMIN, W_SERVOMAX, 0, 180);
    int roationWristAngle = map(R_SERVOREST, R_SERVOMIN, R_SERVOMAX, 0, 180);
    int clawAngle = map(C_SERVOREST, C_SERVOMIN, C_SERVOMAX, 0, 180);
}

void loop()
{

    if (Serial.available() > 1)
    {

        String inputFromSerial = Serial.readString();
        char joint = inputFromSerial[0];
        String angleString = inputFromSerial.substring(1);
        int angle = angleString.toInt();
        Serial.println(joint);
        Serial.println(angle);

        if (joint == 'S')
        {
            int startAngle = shoulderAngle;
            int finalAngle = map(angle, 0, 180, S_SERVOMIN, S_SERVOMAX);
            for (uint16_t angle = startAngle; angle < finalAngle; angle++) // This needs to be for bigger and smaller angles
            {
                pwm.setPWM(0, 0, angle);
                delay(30);
                shoulderAngle = finalAngle;
            }
            Serial.println("Shoulder moved");
        }

        if (joint == 'E')
        {
            int startAngle = elbowAngle;
            int finalAngle = map(angle, 0, 180, E_SERVOMIN, E_SERVOMAX);
            for (uint16_t angle = startAngle; angle < finalAngle; angle++) // This needs to be for bigger and smaller angles
            {
                pwm.setPWM(1, 0, angle);
                delay(30);
                elbowAngle = finalAngle;
            }
            Serial.println("Elbow moved");
        }

        if (joint == 'W')
        {
            int startAngle = wristAngle;
            int finalAngle = map(angle, 0, 180, W_SERVOMIN, W_SERVOMAX);
            for (uint16_t angle = startAngle; angle < finalAngle; angle++)
            {
                pwm.setPWM(2, 0, angle);
                delay(30);
            }
            Serial.println("Wrist moved");
        }

        if (joint == 'R')
        {
            int startAngle = rotationWristAngle;
            int finalAngle = map(angle, 0, 180, R_SERVOMIN, R_SERVOMAX);
            for (uint16_t angle = startAngle; angle < finalAngle; angle++)
            {
                pwm.setPWM(3, 0, angle);
                delay(30);
            }
            Serial.println("Rotated Wrist");
        }

        if (joint == 'C')
        {
            int startAngle = clawAngle;
            int finalAngle = map(angle, 0, 180, C_SERVOMIN, C_SERVOMAX);
            for (uint16_t angle = startAngle; angle < finalAngle; angle++)
            {
                pwm.setPWM(4, 0, angle);
                delay(30);
            }
            Serial.println("Claw moved");
        }
    }
    delay(100);
}
