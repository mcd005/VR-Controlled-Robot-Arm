#include "HBridgeDriver.h"

class ChasisControl
{

public:
    ChasisControl(HBridgeDriver* FrontHbridge,HBridgeDriver* BackHBridge);

    ~ChasisControl();

    void begin();

    void Forward();
    void Backward();
    void Left();
    void Right();
    void Stop();

private:

    HBridgeDriver* _FrontHbridge;
    HBridgeDriver* _BackHBridge;
};


