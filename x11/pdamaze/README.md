X11 PDA Maze
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/x11/pdamaze/scrrenshots/game.png" width="300" /> <br/>

This is Clone <br/>
http://www.newbreedsoftware.com/pdamaze/ <br/>

Changes:
added CMakeLists.txt  <br/>
added scrren shots <br/>
No other changes <br/>

### About:
  "PDA Maze" is a simple Maze Game.  <br/>
A random two-dimensional maze is generated, <br/>
and you must navigate it using a three-dimensional, <br/>
  first-person view. <br/>

 The game is written using Xlib (X-Window) <br/>
and should run on any POSIX compliant OS <br/>
However, it was specifically created to run on the Linux-based "Agenda" PDA. <br/>

### Installing:
Require : <br/>
- libx11 <br/>
- libxpm <br/>

for Linux or MacOSX <br/>
% cd build <br/>
% cmake .. <br/>
% make <br/>
% ./pdamaze <br/>

### Controls:
  You can control the game with the buttons on keyboard <br/>

Left [←] : <br/>
Rotate counter clockwise (North -> West -> South -> East -> North) <br/>

Right [→] : <br/>
Rotate clockwise (North -> East -> South -> West -> North) <br/>

Up [↑] : <br/>
Move forward <br/>

Down  [↓] : <br/>
Move backwards <br/>

Escape [ESC] : <br/>
Quit <br/>


