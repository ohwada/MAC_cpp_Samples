tetris
===============

Tetris game using ncurses <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/ncurses/tetris/media/tetris.png" width="300" /><br/>

### Requires <br/>
- ncurses <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/ncurses <br/>
- sdl2_mixer ( optinal ) <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/SDL2_mixer<br/>

### Build and Run  the file <br/>

% gcc main.c tetris.c util.c music.c  -o tetris `pkg-config --cflags --libs ncurses`

 <br/>
% ./teiris <br/>

### Instructions <br/>

The controls are typical of Tetris:<br/>

[←] and [→]: Move the tetromino,<br/>
 [↑] : Rotate (clockwise?) the tetromino,<br/>
[↓]: Immediately drop the tetromino (not a fast drop, an immediate drop),<br/>
[Q] : Exit the game prematurely,<br/>
[p] : Pause the game (any key to resume),<br/>
[B] : "Boss mode" - show a mock terminal screen to fool nosy onlookers. <br/>
     Hit [F1] to resume the game afterwards.<br/>
[S]: Save game and exit (just assumes filename "tetris.save"). <br/> 
     To resume the game, <br/>
     run with "tetris.save" <br/>
     % ./tetris tetris.save <br/>

### Backgroud Music <br/>

Require "tetris.mp3" ( or your favorite music ) <br/>
Place this in the same directory that you're running the game from. <br/>

Build and run <br/>
 % gcc main.c tetris.c util.c music.c  -o tetris_music  -DWITH_SDL  `pkg-config --cflags --libs ncurses` `pkg-config --cflags --libs sdl2_mixer` <br/>
% ./teiris_music <br/>


### Reference <br/>
- https://github.com/brenns10/tetris
