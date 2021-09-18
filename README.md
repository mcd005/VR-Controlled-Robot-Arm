# VR Controlled Robot Arm

One of the main limitations of some current robotics technology (e.g. bomb disposal robots) is that an operator often has to use joysticks to control the robot.

Allowing a user to move their hands and arms as they would naturally, and have those movements be mirrored on robot arm, could allow for much more intuitive and dexterous control.

<img src="./Docs/ARM_Elevation_480p.gif" width=847>
<img src="./Docs/ARM_ROM_480p.gif" width=847>
<img src="./Docs/ARM_POV_480p.gif" width=847>

Solutions for this kind of problem do exist already, particularly in the medical robotics space however a key advantage of what is shown here is the comparative low cost and portability: you may not need a 100kg, multi-thousand ££ rig to more dexterously control a robot arm!

Although the current iteration requires a user to hold a controller, future iterations can employ the Oculus Quest 2's hand and finger tracking to allow for even finer control.

This project initially targeted a military application however it may have use in other situations where a robot with human-level dexterity/flexibility of control can be sent into a dangerous environment in place of a person (e.g. construction, transport, mining etc).

# System Overview

We have a Ricoh Theta V 360-degree camera piping video into Unity and then onwards to an Oculus Quest 2. This can allow a user to look around their entire environment. Video data is currently transferred by a tethered connection but will soon be streamed wirelessly.

In Unity, we track the coordinates of the VR controller and then map that to servo rotations for each of the joints on the robot arm.

Those rotations are sent via Bluetooth (again currently a short term solution) to an HC-05 connected to an Arduino, which drives each of the servos on the robot arm.

# Acknowledgements

This repo is a fork of the one used to track source code for the PA Consulting "VR Bomb Disposal Robot" summer intern project. Credit to Alexis Dumon and Rishan Patel for their efforts laying the foundation of this work.