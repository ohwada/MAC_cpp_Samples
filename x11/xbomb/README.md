X11 XBomb
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/x11/xbomb/screenshots/squre.png" width="300" /> <br/>

This is Clone <br/>
https://www.gedanken.org.uk/software/xbomb/ <br/>

No Changes <br/>


### About:
This program that looks superficially like the minesweeper program that comes supplied with MS Windows.  <br/>
Runs under X Windows on the UNIX operating system. <br/>

https://en.wikipedia.org/wiki/Minesweeper_(video_game) <br/>


### Installation:

Require : <br/>
- libx11 <br/>
- libxt <br/>
- libxmu <br/>
- libxraw <br/>


% make xbomb <br/>
% make install (optional) <br/>


### Features:

There are a number of features that make this version different from the others available (that I have seen). <br/>

3 Grid Tile options: <br/>
- Hexagonal ; Easy (the endgame can be difficult). <br/>
- Square ; Traditional. <br/>
- Triangular ; Difficult. <br/>

3 Grid sizes: <br/>
- Small : 8x8 with 10 bombs <br/>
- Medium : 16x16 with 40 bombs <br/>
- Large : 30x16 with 99 bombs <br/>

Highscore table: <br/>
10 entries for the fastest times for each of the 3 levels of each of the 3 grid shapes. <br/>


### Playing the game:

Located under the tiles of the grid are
a number of unexploded bombs. <br/>
The target of the game is detect the location of the bombs
given only the number of bombs neighbouring each of the locations known to have no bomb. <br/>
Locations known to contain bombs, are marked and the game finishes when all locations are uncovered or marked. <br/>

Left mouse button: <br/>
Uncover the current location if not already done or uncover all adjacent squares not marked as bombs.<br/>

Middle mouse button: <br/>
Uncover all adjacent squares not marked as bombs. <br/>

Right mouse button: <br/>
Mark a square as being known to contain a bomb (toggles). <br/>

's' key : Start a new game <br/>
'q' key : Quit the game <br/>
'h' key : Print the high score table for the current grid shape. <br/>

'1','2' or '3' key : Select game level 1, 2 or 3. <br/>
'H','S' or 'T' key : Select game type Hexagon, Square or Triangle grid.<br/>

