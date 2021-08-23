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
    /// bit confusing that we are using different names ... 
}

BigArm::~BigArm()
{
}

BigArm::setJointsTargetAngles(int bigArmWristFlexor, int bigArmClaw, int bigArmWristRotator, int bigArmElbow, int bigArmShoulder)
{
    _waist.setJointsTargetAngles(0);
    _shoulder.setJointsTargetAngles(bigArmShoulder);
    _elbow.setJointsTargetAngles(bigArmElbow);
    _pitch.setJointsTargetAngles(bigArmWristFlexor); // not sure about the names!!!
    _roll.setJointsTargetAngles(bigArmWristRotator);
    _claw.setJointsTargetAngles(bigArmClaw);

}

BigArm::doJointsMovement()
{
    _waist.incrementPosition();
    _shoulder.incrementPosition();
    _elbow.incrementPosition();
    _pitch.incrementPosition(); // not sure about the names!!!
    _roll.incrementPosition();
    _claw.incrementPosition();
}

