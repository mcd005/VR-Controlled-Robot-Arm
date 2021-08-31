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
                            _claw(claw)
                      
{
    /// bit confusing that we are using different names ... 
}

BigArm::~BigArm()
{
}

void BigArm::setJointsTargetAngles(int bigArmWristFlexor, int bigArmClaw, int bigArmWristRotator, int bigArmElbow, int bigArmShoulder)
{
    _waist->setTargetAngle(0);
    _shoulder->setTargetAngle(bigArmShoulder);
    _elbow->setTargetAngle(bigArmElbow);
    _pitch->setTargetAngle(bigArmWristFlexor); // not sure about the names!!!
    _roll->setTargetAngle(bigArmWristRotator);
    _claw->setTargetAngle(bigArmClaw);

}

void BigArm::doJointsMovement()
{
    _waist->incrementPosition();
    _shoulder->incrementPosition();
    _elbow->incrementPosition();
    _pitch->incrementPosition(); // not sure about the names!!!
    _roll->incrementPosition();
    _claw->incrementPosition();
}
