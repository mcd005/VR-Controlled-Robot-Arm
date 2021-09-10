# Kobe

This is the intern project for summer July 2021. The idea is to demo a bomb disposal robot using virtual reality. There are two important functionalities which are proven in this project: 

1. A robot that can move around an environment with a small arm that can be used to lift a small box (the bomb). A camera can live stream to the headset.
2. A big arm with 3 degrees of freedom

Project involves different components:

1. Unity (version 2020.3.14)
2. Arduino (Mega 2560) + HC-05 Bluetooth module
3. Oculus Quest 2 (128 GB + 6 RAM) + 2 Oculus Touch controllers + Oculus Link
4. Ricoh Theta V
5. Robot made with electrical components

![image](https://user-images.githubusercontent.com/52036219/132705509-429d8e6e-2ad0-4e1b-8884-dd9425168909.png)

Unity is used as the platform to integrate the Oculus Quest 2, the camera live stream and processing / sending the data to the Arduino.
Developping with the Oculus Quest 2:
* https://www.youtube.com/watch?v=YwFXQeBmxZ4 - setting up Unity for Oculus Quest 2
* https://www.xrterra.com/developing-for-vr-with-quest-2-unity-for-the-first-time-a-step-by-step-guide/ - slower and not video 
NOTE: These both explain how to run the Oculus quest 2 as a standalone headset. In order to not make it run that way: use the Link. In Unity Build settings choose as the platform 'PC, Mac & Linux Standalone'.
Unity needs the following packages / assets to be downloaded.

Package manager:
* XR Interaction Toolkit (latest)
* XR Plugin Management (latest)
* Oculus XR Plugin (latest)

Asset:
* Oculus Integration: contains OVRInput, OVRManager etc. NOTE no need to download all the files (they take a lot of space), I have found that the VR package is the only needed file for this to work.

## How to run the demo
1. Turn on headset and make sure Oculus Link is enabled
2. Camera is plugged to PC running Unity and is on Live mode
3. Arduino code has been uploaded to Arduino
4. HC-05 bluetooth module is paired with the computer
5. Battery is connected to the robot
6. Application can then be started by pressing the play button on Unity

## Chassis

![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/52036219/132708318-093f2bc5-8b52-4061-8285-7998d9c3477e.gif)

## Robot Arm with Basic Inverse Kinematics

![Arm Elevation](https://i.imgur.com/DCdY8UZ.gif)
<img src="https://i.imgur.com/vAqzJ0g.gif" width=847>
<img src="https://i.imgur.com/bLd3fDd.gif" width=847>

## High level file structure:

*Unity* : UnityKobe

Go to Assets then Scripts

* HeadsetControlsManager: Collects and process data from the headset
* BluetoothCommsManager: Sends the collected data to Arduino via Bluetooth
* CommsManager: (**not in use anymore**) Sends the collected data by sending a request to a HTTP server on a Raspeberry PI - the PI is then wired to the Arduino
* WebCamDetect: Places the Camera's live stream onto the inside of a sphere to allow operator to see the stream

*Arduino* : ArduinoKobe

Go to ArduinoFirmware

* ArduinoFirmware.ino: main file which contains the 'set up' and the 'loop' 
* All the other files serve to abstract the implementation of the robot movements in an Object-Oriented Programming manner

---------------------------------------------------------------------------------

Branches right now:
* main: runs the robot and the unity code allowing the robot to move around the environment, use the small arm (lift) and the operator to see the stream
* bigArm: unity code to send data to robotic big arm to make it move around with three degrees of freedom
* handTracking: branched from main and has code in the handTracking scene which displays the xyz coordinates of the operators thumb on the screen. Idea is to incorporate this data into the mainScene to allow the user to use their hands instead of the two Oculus Touch controllers.
