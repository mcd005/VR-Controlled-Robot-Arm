import math

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
    def __init__(self, upper_arm_length=105, forearm_length=110, shoulder_rest=90, elbow_rest=90):
        self.upper_arm_length = upper_arm_length
        self.forearm_length = forearm_length
        self.alpha = self.get_angle_from_cosine_rule(self.r, self.upper_arm_length, self.forearm_length)
        self.beta = self.get_angle_from_cosine_rule(self.upper_arm_length, self.forearm_length, self.r)
        self.r = self.compute_desired_length_of_virtual_vector(upper_arm_length, forearm_length)
        self.phi
        self.shoulder_angle = shoulder_rest
        self.elbow_angle = elbow_rest

    def compute_servo_angles(self, x, y):
        self.r = self.compute_desired_length_of_virtual_vector(x, y)
        self.update_angles_to_change_virtual_vector_length()
        self.convert_triangle_angles_to_servo_angles()
        print(f"W90,S{self.shoulder_angle},E{self.elbow_angle}")

    @staticmethod
    def compute_desired_length_of_virtual_vector(x, y):
        return math.sqrt(x**2 + y**2)

    @staticmethod
    def compute_phi(x, y):
        return math.atan(y/x)
        
    def update_angles_to_change_virtual_vector_length(self):
       '''
       We use the cosine rule here. Given three known sides we can calculate our unknown angles
       '''
       self.alpha = self.get_angle_from_cosine_rule(self.r, self.upper_arm_length, self.forearm_length)
       self.beta = self.get_angle_from_cosine_rule(self.upper_arm_length, self.forearm_length, self.r)
    
    def convert_triangle_angles_to_servo_angles(self):
       self.elbow_angle = math.degrees(self.beta)
       self.shoulder_angle = math.degrees() 

    @staticmethod
    def get_angle_from_cosine_rule(enclosing_len_A, enclosing_len_B, opposite_len_C):
        return math.acos((enclosing_len_A**2 + enclosing_len_B**2 - opposite_len_C**2)/(2 * enclosing_len_A * enclosing_len_B))

if __name__ == "__main__":
    ik = InverseKinematics()
    print(ik.compute_desired_length_of_virtual_vector(3, 4))