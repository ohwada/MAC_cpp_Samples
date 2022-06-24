X11 3D Pong
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/x11/3dpong/scrrenshots/pong.png" width="300" /> <br/>

This is Clone <br/>
http://www.newbreedsoftware.com/3dpong/index2.php3 <br/>

Changes :   <br/>
added CMakeLists.txt <br/>
added sound.h  <br/>
and slight changes <br/>


### WHAT IS 3D PONG?

 3D Pong is an X-Window game for 1 or 2 players. <br/> 
It's a 3D game based on the first arcade game, "Pong." <br/>
https://en.wikipedia.org/wiki/Pong <br/>
Like "Pong," it's a game played with a ball and paddles. <br/>
The object is to hit the ball and get it in the other player's goal. <br/>
Use your paddle to deflect the ball and keep it from getting in your goal. <br/>

3D Pong has three game modes: <br/>
1. One player - against a computer player <br/>
2. Two player - requires two X-Window display servers <br/>
3. Handball - one player against gravity and a wall <br/>

### INSTALLING
Require : <br/>
- libx11 <br/>

for Linux or MacOSX <br/>
% cd build <br/>
% cmake .. <br/>
% make <br/>

copy man page to system area (optional) <br/>
% make man <br/>
You may read 3D Pong's man page with "man 3dpong", <br/>


### RUNNING THE GAME

To run the game, type "3dpong" with a pair of arguments  <br/>
that depend on the game mode you wish to play: <br/>

 One player game:  <br/>
% ./3dpong $DISPLAY --computer <br/>

### 3D PONG CONTROLS:

Moving the paddle:  <br/>

Left-Click in your window and drag (holding the left mouse button) <br/>
to move the paddle around. <br/>

Serving: <br/>

In a one- or two-player ping-pong game,  <br/>
when it's your turn to serve <br/>

Position your paddle where you wish the ball to start <br/>
Right-Click to launch the ball <br/>


