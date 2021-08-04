
class HBridgeDriver
{
public:
    HBridgeDriver(int ENA,
                  int IN1,
                  int IN2,
                  int IN3,
                  int IN4,
                  int ENB);

    void begin();

    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void stop();

    ~HBridgeDriver();

private:
    int _ENA;
    int _IN1;
    int _IN2;
    int _IN3;
    int _IN4;
    int _ENB;
};


