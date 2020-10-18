# TruckHazardDetection
A program to display video feed from a Raspberry Pi Zero by Team14 XIV Consulting.

# Requirements
> QT += core gui multimedia multimediawidgets

Make sure everything is updated.

**Important: Ensure that Fake KMS is enabled on Raspberry Pi** to ensure `libEGL warning: DRI2: failed to authenticate` does not occur.

```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libqt5multimedia5-plugins qml-module-qtmultimedia qt5-default qtcreator qtmultimedia5-dev 

```

# Changelog
- 18-10-2020
    - Attempt at implementing activating camera via bash scripting
        - QProcess::start() is depreciated
    - Autostart script
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



