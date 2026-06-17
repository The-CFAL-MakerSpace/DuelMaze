# DuelMaze - A two player physical arcade game.

## Credits - Makerspace Batch of '26
-> Sharaj Shreyas:- Makerspace President, Hardware Primary UC, Assertive Eyebrows.
-> Sanath Sanjay Shet:- Software Primary UC, Idk what to write about myself, Slay Queen.
-> Nandan Bhandary:- Hardware Primary UC, Designed the Circuitry, Very good at electronics.
-> Lauren Patrao:- Maze Design UC, Very smart nerd, Math afficionado.
-> Vignesh Navada:- Media Team, Really good with Cameras, check out his yt.
-> Pratheek Bhat:- Software UC, Hardcore F1 Fan.
-> Arnav Raju Ghote:-Design Team, Hardcore F1 Fan.
-> Abhhi Sanayya:- Software UC, 
-> Tarang Rajeev:- Maze Design Team, Hardcore F1 Fan.
-> Manvith Udupa:- Software Team, Web development team, Media Team, Great guy.
-> 

## Read this upto the technical details warning Before doing anything silly with our Project!

How's it going, Juniors? Distracted from JEE prep i see. First off, i must warn you. The project is more complicated than it looks (mostly on the software side) and might eat up a lot of your time. In the end, for Makers fete, you may not even have it running (we couldnt get it set up properly on both Makers fete '24 and '25). Tread with caution.

**Also, the maze setup is delicate. do not lift the build up by the maze or from the Wooden ceiling in the centre. Always pick it up from the side walls. Always keep the build perfectly horizontal. Or shit will hit the fan and you'll have to fix it.**

## What is DuelMaze?
Duel - a pre-arranged, formal combat between two people, usually fought with matched weapons under specific rules to settle a personal grievance or point of honor.
Maze - Bruh

Two players race to get a marble from the Starting point to the ending point in the shortest amount of time, for point of honor. Thats it. The joystick moves two servo motors that tilt the maze.

### Technical Details Warning - Pay attention if you're in charge of setting this up.

## Initial Hardware Setup

1. Firstly, all connections to the prototype board (the brown one) have been soldered directly. dont try to pull them out. The central female headers are for the Arduino Nano, and **the orientation is done in such a way that the USB socket of the nano is facing the green connector closest to the female header**. When the USB cable is connected, the communication line (yet to be explained) cannot be connected simultaneously.
2. The connection from the components to the Nano are done via white screw connectors. **Check for any loose/disconnected cable and follow the schematic to reconnect**. The joystick cable is soldered directly, **Do NOT try to pull it out**. The rest of the components are attached via jumper cables.
3. The green female connectors on the board each serve a purpose. **The one right next to the USB Socket of the Nano is the Communication-Line and the one further away is the power line. DO NOT MIX THE TWO UP**.

## Initial Software setup
1. Just open the code in the arduino ide, select the right COM port and **Bootloader Version (the blue maze has an old bootloader)** and thats it.

## Hardware troubleshooting
1. Servo is very Jittery -> Usually a problem with the joystick. check for loose connections. If it 






## Contributing:
To contribute, make sure to open a branch first, and commit there and then the UCs will review it and merge your pull request.

# Current:
The current code is very basic, and not intended to be the final version as of now, it will, however be modified over the coming days and will slowly turn into the main source code, after lots of simulations ofc.

# These are some values:
### Servos:
```
val = map(val, 90, 1023, 60, 77)
```
