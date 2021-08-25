import math
import sys

# Below is the robot arm. The dashes are the forearm (parallel with the x-axis), the pipes are the upper arm (parallel with the y-axis)
# The shoulder is the "0" at the base of the upper arm. The elbow is the "0" at the connection between the upper arm and forearm. The wrist joint is at the point of the ">"
#
# Imagine that there is a virtual vector that points from the shoulder joint to the wrist joint.
# We define a variable r that is the length of that vector and a variable theta that is the angle between this virtual vector and the x axis
# 
# The following angles are the internal angles of the triangle made up of the virtual vector and the arms of the robot. They are NOT the servo angles (but are related to the servo angles)
# The shoulder_rest_angle and elbow_rest_angle are the starting angles of the servos
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
#
# Units of length are in mm, angles are given in degrees

class InverseKinematics():
    def __init__(self, upper_arm_length=105, forearm_length=110, shoulder_rest_angle=90, elbow_rest_angle=90):
        self.upper_arm_length = upper_arm_length
        self.forearm_length = forearm_length
        self.shoulder_rest_angle = math.radians(shoulder_rest_angle)
        self.elbow_rest_angle = math.radians(elbow_rest_angle)
        self.phi_rest_angle = self.compute_phi(0, 0)
        self.alpha_rest_angle = (math.pi / 2) - self.phi_rest_angle
        self.beta_rest_angle = self.get_angle_from_cosine_rule(self.upper_arm_length, self.forearm_length, self.compute_desired_length_of_virtual_vector(0, 0))

    def compute_servo_angles(self, x, y):
        phi = self.compute_phi(x, y)
        r = self.compute_desired_length_of_virtual_vector(x, y)
        alpha = self.get_angle_from_cosine_rule(r, self.upper_arm_length, self.forearm_length)
        beta = self.get_angle_from_cosine_rule(self.upper_arm_length, self.forearm_length, r)
        shoulder_angle = self.compute_shoulder_angle(phi, alpha)
        elbow_angle = self.compute_elbow_angle(beta)
        print(f"S{shoulder_angle},E{elbow_angle}")

    def compute_phi(self, x, y):
        return math.atan((y + self.upper_arm_length)/(x + self.forearm_length))

    def compute_desired_length_of_virtual_vector(self, x, y):
       return math.sqrt((x + self.forearm_length)**2 + (y + self.upper_arm_length)**2)

    @staticmethod
    def get_angle_from_cosine_rule(enclosing_len_A, enclosing_len_B, opposite_len_C):
        return math.acos((enclosing_len_A**2 + enclosing_len_B**2 - opposite_len_C**2)/(2 * enclosing_len_A * enclosing_len_B))

    def compute_shoulder_angle(self, phi, alpha):
        return  int(math.degrees(self.shoulder_rest_angle + (phi - self.phi_rest_angle) + (alpha - self.alpha_rest_angle)))

    def compute_elbow_angle(self, beta):
        return  int(math.degrees(self.elbow_rest_angle + (beta - self.beta_rest_angle)))

if __name__ == "__main__":
    ik = InverseKinematics(upper_arm_length=100, forearm_length=100)
    # Plug in a coordinate that is x mm in front of and y mm below/above the tip of the robot arm claw
    ik.compute_servo_angles(10 , 10)