#include "SmallArm.h"


SmallArm::SmallArm(Joint* baseServo, Joint* bendServo)
{
    _baseServo = baseServo;
    _bendServo = bendServo;
}

SmallArm::~SmallArm() 
{
}

void SmallArm::UP()
{   
    _bendServo->setTargetAngle(20);
}

void SmallArm::DOWN()
{
    _bendServo->setTargetAngle(0);
}
