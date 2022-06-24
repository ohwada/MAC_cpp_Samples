X11 brickout
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/x11/brickout/scrrenshots/game.png" width="300" /> <br/>

This is Clone <br/>
http://www.newbreedsoftware.com/brickout/ <br/>

Changes :   <br/>
added CMakeLists.txt, <br/>
so that you can build on Mac OS X <br/>
and slight changes <br/>


### About
 "Brick Out" is based on the classic arcade game "Breakout."  <br/>
https://en.wikipedia.org/wiki/Breakout_(video_game)  <br/>

 The objective is to clear a screen of bricks by bouncing a ball against them.   <br/>
You use a paddle to bounce the ball,  <br/>
and keep it on the screen.  <br/>

### Installing
Require : <br/>
- libx11 <br/>
- SDL_mixer (optional) <br/>

for Linux or MacOSX <br/>
% cd build <br/>
% cmake .. <br/>
% make <br/>
% ./brickout <br/>

when adding sound effects <br/>
% cmake .. -DSDL=ON <br/>
% make <br/>
% ./brickout_sound <br/>


### Controls
You can play the game with the buttons on your keyboard, <br/>
  or using the mouse: <br/>

Space : <br/>
or "Launch" button on screen : <br/>
Launch a new ball (if one isn't in play). <br/>

Left  [←] and Right [→] : <br/>
or Pointer motion (mouse movement) : <br/>
Move the paddle side to side. <br/>




