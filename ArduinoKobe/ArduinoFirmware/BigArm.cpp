#include "BigArm.h"

BigArm::BigArm(Joint* waist,
            Joint* shoulder,
            Joint* elbow, 
            Joint* pitch,
            Joint* roll,
            Joint* claw) : _waist(waist),
                            _shoulder(shoulder),
                            _elbow(elbow),
                            _pitch(pitch),
                            _roll(roll),
                            _claw(claw),
{
}

BigArm::~BigArm()
{
}

BigArm::handleControl()
{
    
}


