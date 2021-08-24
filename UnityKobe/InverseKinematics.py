import math
import sys

# Below is the robot arm. The dashes are the forearm (parallel with the x-axis), the pipes are the upper arm (parallel with the y-axis)
# The shoulder is the "0" at the base of the upper arm. The elbow is the "0" at the connection between the upper arm and forearm. The wrist joint is at the point of the ">"
#
# Imagine that there is a virtual vector that points from the shoulder joint to the wrist joint.
# We define a variable r that is the length of that vector and a variable theta that is the angle between this virtual vector and the x axis
# 
# The following angles are the internal angles of the triangle made up of the virtual vector and the arms of the robot. They are NOT the servo angles (but are related to the servo angles)
#
#   This angle is gamma. It is the angle between the virtual vector and the forearm
#   
#  >-------0    This angle is beta. This is the elbow joint.
#         \|   
#          |
#          |
#          |
#         \|    This angle is alpha. It is the angle from between the virtual vector and the shoulder. This is the shoulder joint
#          0    
#          
#  This angle is phi. It is the angle between the x-axis and the virtual vector. It is 90 - alpha

class InverseKinematics():
    def __init__(self, upper_arm_length=105, forearm_length=110, shoulder_rest_angle=90, elbow_rest_angle=90):
        self.upper_arm_length = upper_arm_length
        self.forearm_length = forearm_length
        self.shoulder_rest_angle = math.radians(shoulder_rest_angle)
        self.elbow_rest_angle = math.radians(elbow_rest_angle)
        self.phi_at_rest = self.compute_phi(0, 0)

    def compute_servo_angles(self, x, y):
        phi = self.compute_phi(x, y)
        shoulder_angle = int(math.degrees(self.shoulder_rest_angle + (phi - self.phi_at_rest)))
        print(f"S{shoulder_angle}")

    def compute_phi(self, x, y):
        return math.atan((y + self.upper_arm_length)/(x + self.forearm_length))

if __name__ == "__main__":
    ik = InverseKinematics(upper_arm_length=100, forearm_length=100)
    ik.compute_servo_angles(0 , 0)