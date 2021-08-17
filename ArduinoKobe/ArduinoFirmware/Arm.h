

class Arm
{

public:
    Arm(Adafruit_PWMServoDriver pwmDriver,
        uint8_t selector1,
        uint8_t selector2,
        uint8_t selector3,
        uint8_t selector4,
        uint8_t selector5
        );
        
    ~Arm();


    void moveLeft();

private:
    /* data */


};

