# Kobe

This is the intern project for summer July 2021. The idea is to demo a bomb disposal robot using virtual reality
Project involves different components:

1. Unity (version 2020.3.14)
2. Arduino (Mega 2560) + HC-05 Bluetooth module
3. Oculus Quest 2 (128 GB + 6 RAM) + Oculus Link
4. Ricoh Theta V
5. Robot made with electrical components

![image](https://user-images.githubusercontent.com/52036219/132705509-429d8e6e-2ad0-4e1b-8884-dd9425168909.png)

Unity is used as the platform to integrate the Oculus Quest 2, the camera live stream and processing / sending the data to the Arduino.
Developping with the Oculus Quest 2:
* https://www.youtube.com/watch?v=YwFXQeBmxZ4 - setting up Unity for Oculus Quest 2
* https://www.xrterra.com/developing-for-vr-with-quest-2-unity-for-the-first-time-a-step-by-step-guide/ - slower and not video 
NOTE: These both explain how to run the Oculus quest 2 as a standalone headset. In order to not make it run that way: use the Link. In Unity Build settings choose as the platform 'PC, Mac & Linux Standalone'.

How to run:
1. Turn on headset and make sure Oculus Link is enabled
2. Camera is plugged to PC running Unity and is on Live mode
3. Arduino code has been uploaded to Arduino
4. HC-05 bluetooth module is paired with the computer
5. Battery is connected to the robot
6. Application can then be started by pressing the play button on Unity

![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/52036219/132708318-093f2bc5-8b52-4061-8285-7998d9c3477e.gif)

High level file structure:

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
