
#include "Joint.hpp"

class BigArm
{
private:
    /* data */
public:
    BigArm( Joint* waist,
            Joint* shoulder,
            Joint* elbow, 
            Joint* pitch,
            Joint* roll,
            Joint* claw);

    ~BigArm();


    Joint* _waist;
    Joint* _shoulder;
    Joint* _elbow; 
    Joint* _pitch;
    Joint* _roll;
    Joint* _claw;

    void setJointsTargetAngles(int bigArmWristFlexor, int bigArmClaw, int bigArmWristRotator, int bigArmElbow, int bigArmShoulder);

    void doJointsMovement();
};



