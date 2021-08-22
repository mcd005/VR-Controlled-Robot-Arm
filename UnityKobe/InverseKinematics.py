# Variables we need:
#   Lenght of upper arm
#   Length of forearm
#   Angle between virtual vector and upper arm


# This is the robot arm. The dashes are the forearm, the pipes are the upper arm
# Imagine that there is a virtual vector that points from the shoulder joint to the wrist joint. #TODO maybe make this shoulder to tip of claw
#
#  This angle is gamma. This is the wrist joint.
#   
#  >-------0    This angle is delta. This is the elbow joint
#         \|   
#          |
#          |
#          |
#         \|    This angle is alpha. This is the shoulder joint

class InverseKinematics():
    def __init__(self, upperArmLength=105, forearmLength=100, alphaStart=45, deltaStart=90) -> None:
        self.upperArmLength = upperArmLength
        self.forearmLength = forearmLength
        self.alpha = alphaStart
        self.delta = deltaStart


    def computeServoAngles(x, y, z):
        pass

    def shortenVirtualVectorToLenghtR(r):
       '''
       We use the cosine rule here. Given three known sides we can calculate our unknown angles
       ''' 