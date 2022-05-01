# README #

This is app for controlling GNSS Tevogs Tesbench. This app is started manually from terminal. 
Positions are logged into /oDriveApp/logs and are stored permanently.
Parameters for app are set in Rounds per second of motor, for example 20 rps will result in about 40km/h of angular speed at the end of testbench, where reciever devices are placed.
Second parameter is timelength of spin, whic is set in seconds. 

WARNING testbench will turn into starting position to where is inductive sensor placed at startup and before every spinsession start, dont stand in the way of arms of testbench. Use emergency stop to get out of way. Then release the emergency stop WARNING

There is another version of this app which is running on system as daemon service.

### What is this repository for? ###

* Quick summary
* Set up
* Usage

### Prerequisities ###

* Odrive board 24V 3.6 
	-Firmware version : 0.5.2
* SDK tdx-wayland 5.3.0 build from testbench layers

### Setup ###
* Build
* Deploy to toradex 

### Usage ###
* Power up testbench
* Connect to testbench via wifi 
* Connect to testbench via ssh
* Run "/oDriveApp/oDriveApp {speed in rps of motor} {length of spinning in seconds} {nameOfLogFile}"
* WARNING testbench will turn into starting position to where is inductive sensor placed at startup and before every spinsession start, dont stand in the way of arms of testbench. Use emergency stop to get out of way. Then release the emergency stop WARNING
* Spin testbench
