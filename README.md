# TruckHazardDetection
A program to display video feed from a Raspberry Pi Zero by Team14 XIV Consulting.

# Requirements
> QT += core gui multimedia multimediawidgets

Make sure everything is updated.

```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libgstreamer* qt5-default qtcreator

```

# Changelog
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


