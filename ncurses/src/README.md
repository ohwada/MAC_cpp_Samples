ncurses src
===============

ncurses sample <br/>


### hello.c <br/>
 display  "Hello World" <br/>

Build and Run file <br/>
% gcc hello.c -lncurses -o hello <br/>
% ./hello <br/>


### scr_size.c <br/>
 display  Display Size <br/>

Build and Run file <br/>
% gcc scr_size.c -lncurses -o size <br/>
% ./size <br/>


### keypad.c <br/>
enable Arrow key ( Cursor key) <br/>

Build and Run file <br/>
% gcc keypad.c -lncurses -o keypad <br/>
% ./keypad <br/>


### version.c <br/>
 display  version <br/>

Build and Run file <br/>
%  gcc version.c -lncurses -o version <br/>
% ./version <br/>


### input_num.h <br/>
single header library <br/>
 pseudo-implement the echo of character input  <br/>
 and input a numerical value  <br/>
 only positive numbers <br/>

Build and Run file <br/>
% gcc  test_input_num.c -lncurses -o input
% ./input <br/>

### buffer.cpp <br/>
Scrool Buffer for Screen

Build and Run file <br/>
% g++  test_buffer.cpp buffer.cpp -lncurses -o buffer
% ./buffer <br/>


### Reference <br/>
- https://invisible-island.net/ncurses/announce.html#h3-documentation

