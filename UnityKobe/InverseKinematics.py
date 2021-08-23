import math
from os import stat

# Variables we need:
#   Lenght of upper arm
#   Length of forearm
#   Angle between virtual vector and upper arm

# This is the robot arm. The dashes are the forearm (parallel with the x-axis), the pipes are the upper arm (parallel with the y-axis)
# Imagine that there is a virtual vector that points from the shoulder joint to the wrist joint. #TODO maybe make this shoulder to tip of claw
#
#  This angle is gamma. This is the wrist joint.
#   
#  >-------0    This angle is beta. This is the elbow joint.
#         \|   
#          |
#          |
#          |
#         \|    This angle is alpha. It is the angle from between the virtual vector and the shoulder. This is the shoulder joint
#               This angle is phi. It is the angle between the x-axis and the virtual vector. It is 90 - alpha


class InverseKinematics():
    def __init__(self, upper_arm_length=105, forearm_length=110, elbow_rest=90, shoulder_rest=90) -> None:
        self.upper_arm_length = upper_arm_length
        self.forearm_length = forearm_length
        self.r = self.compute_desired_length_of_virtual_vector(upper_arm_length, forearm_length)
        self.alpha = self.get_angle_from_cosine_rule(self.r, self.upper_arm_length, self.forearm_length)
        self.beta = self.get_angle_from_cosine_rule(self.upper_arm_length, self.forearm_length, self.r)

    def compute_servo_angles(x, y):
        pass

    @staticmethod
    def compute_desired_length_of_virtual_vector(x, y):
        return math.sqrt(x**2 + y**2)

    def update_angles_to_change_virtual_vector_length(self, r):
       '''
       We use the cosine rule here. Given three known sides we can calculate our unknown angles
       '''
       pass
    #    self.alpha = self.get_angle_from_cosine_rule(self.r, self.upper_arm_length)

    @staticmethod
    def get_angle_from_cosine_rule(enclosing_len_A, enclosing_len_B, opposite_len_C):
        return math.acos((enclosing_len_A**2 + enclosing_len_B**2 - opposite_len_C**2)/(2 * enclosing_len_A * enclosing_len_B))


if __name__ == "__main__":
    ik = InverseKinematics()
    print(ik.compute_desired_length_of_virtual_vector(3, 4))