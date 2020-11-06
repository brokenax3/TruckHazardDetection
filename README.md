# TruckHazardDetection
A program to display video feed from a Raspberry Pi Zero by Team14 XIV Consulting.

The video demonstration of the product can be shown in VideoDemonstration.mp4

The project consists of three parts:
- Camera Module
- MQTT + Ultrasonic Sensor
- Main Unit

# Requirements
> QT += core gui multimedia multimediawidgets

Make sure everything is updated.

**Important: Ensure that Fake KMS is enabled on Raspberry Pi** to ensure `libEGL warning: DRI2: failed to authenticate` does not occur.

```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libqt5multimedia5-plugins qml-module-qtmultimedia qt5-default qtcreator qtmultimedia5-dev 

```

# Setup 

## Camera Module
Put the following into a bash script:

```bash
#!/bin/bash

raspivid -o - -t 0 -rot 180 -w 640 -h 480 -fps 15 -b 2000000 | cvlc -vvv stream:///dev/stdin --sout '#rtp{sdp=rtsp://:8554/stream}' :demux=h264
```

## MQTT
1. Install mosquitto

```bash
wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
sudo apt-key add mosquitto-repo.gpg.key
cd /etc/apt/sources.list.d/
sudo wget http://repo.mosquitto.org/debian/mosquitto-stretch.list
sudo apt-get update
sudo apt-get install mosquitto
sudo apt-get install mosquitto-clients
systemctl status mosquitto.service
```

2. Configure mosquitto

Once installed:

> sudo nano /etc/mosquitto/mosquitto.conf

At the bottom of this file, you should see the line:
> include_dir /etc/mosquitto/conf.d

Comment this line above and add the following lines to the bottom of the file:

```bash
allow_anonymous false
password_file /etc/mosquitto/pwfile
listener 1883
```

Then:
> sudo mosquitto_passwd -c /etc/mosquitto/pwfile username

Enter a new password: `raspberry`

## Main Unit

### Main Process
1. Compile `camera.cpp` and place into debug directory with

> g++ -Wall -o leftLDR camera.cpp -lwiringPi

2. Edit parameters for Server.py to Host IP Address

```python
- mqtt_broker_ip = "192.168.43.145" # CHANGE TO RPI IP
+ mqtt_broker_ip = "<Raspberry Pi Host IP Address HERE>" # CHANGE TO RPI IP
```

3. WiFi Hosting with [raspap](https://raspap.com/#quick-installer)

> curl -sL https://install.raspap.com | bash

4. Run `autoTruckHazard`

### SSH Enable/ Disable Camera
1. Install expect

> sudo apt-get install expect

2. Put the following into /usr/bin/exp:

```bash
#!/usr/bin/expect

set timeout 20

set cmd [lrange $argv 1 end]
set password [lindex $argv 0]

eval spawn $cmd
expect "assword:"
send "$password\r";
interact
```

- Usage:
    - `exp <password> ssh <anything>`
    - `exp <password> scp <anysrc> <anydst>`

# Changelog
- 18-10-2020
    - Attempt at implementing activating camera via bash scripting
        - QProcess::start() is depreciated
    - Autostart script
    - More instructions on installation process
- 17-10-2020
    - Video player optimisations
    - Streams not playing smoothly is an issue with the streamer, not the client.
        - Tested with RTSP stream test and hosting VLC stream and video and audio was playing as expected
    - Fixed some problems with code
    - Update dependencies list
- 16-10-2020
    - Re-Implemented some UI elements
    - Auto-switching now works with Left and Right Camera
    - Enable setting, saving and applying two cameras
    - Distance displaying improvements
    - Quick start instructions
    - FileWatcher works
    - Code clean-up 
- 15-10-2020
    - Implemented Automatic switching with Photoresistor
    - Reverted FileWatcher as it breaks automatic video stream displaying (GStreamer Error)
- 14-10-2020
    - Removed press to play and stop button for automatic switching
    - Implemented Filewatcher to monitor the contents of a file to switch camera feeds
    - Changed Distance label to show actual distance provided from MQTT server
- 29-08-2020
    - Initial Backup

# Misc
- Backup29082020
- Backup07102020
- Backup14102020
    - camera.cpp (photoresistor trigger script)
    - MQTT stuff
- Backup16102020
- Backup17102020
- Backup18102020



