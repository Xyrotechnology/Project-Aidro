#Welcome to Project Anthrax's Software development site.

To start with , here is our work flow:
======================================
1) The Raspberry Pi , which is connected to the laser scanner and the pixycam, responds to user input by executing the:
  a) Environment scanning script. (Laser Scanning Module)
  b) 2D and 3D map creation script (Laser Scanning Module)
  c) Object detection (includes face detection) script. (Pixycam Module)
  d) Assigns coordinates to each object based on the map and object id. (cooperation of both pixycam and laser scanner
     will be needed)
  e) Coordinate movement of GoPro module based on the position of the object.
  f) Avoid obstacles when the laser radar shows an obstacle.
   It will also need to execute a script that
   i) Responds to Object detection by sending commands via mavlink to the Pixhawk module.
  ii)Saves and stores all output to the sdcard provided (For Mark 1 be verbose, but for Mark 2, try to be user friendly)

2) The Pixhawk scanning module is in charge of the following:
  a) Respond to mission control. (Available via mission planner softwares)
  b) Control flight of the drone.
  c) Stabilize drone.
  d) Send GPS coordinates to mission control.
  e) Snap picture or shoot a video via the GoPro or the Hero modules.
  f) Avoid obstacles which are less than 5 cm above it.


IMPORTANT NOTES WHILE WORKING:
===============================
 
1) The software for the quadcopter should be based strictly on only Python and Arduino.
2) The operating system for the raspberry pi should be either Debian Barebones (strictly no GUI), Ubuntu minimal, or the
   Raspbian OS. Get me a report on the teams opinion within 3 days.
3) All problems should be reported on the ISSUES section WITHOUT any hesitation.
4) Do not feel shy to speak up and suggest new ideas to the team.
5) If you want to make changes to other modules in the framework, please talk to the module master first.
   (The one who is working on it.)
6) For reference, please look at board.jpg for the assembly instructions. But be warned not to solder immediately,
   request permission for it.
