ncurses
===============

ncurses sample <br/>

ncurses is Text-based UI library <br/>
https://invisible-island.net/ncurses/announce.html


###  install ncurses
% brew install ncurses <br/>
https://formulae.brew.sh/formula/ncurses <br/>

% ln -s  /usr/local/opt/ncurses/lib/pkgconfig/ncurses.pc /usr/local/lib/pkgconfig/ncurses


### hello.c <br/>

 display  "Hello World" <br/>

run file <br/>
% gcc hello.c -o hello -lncurses
% ./hello <br/>

### version.c <br/>

 display  version <br/>

run file <br/>
%  gcc version.c -o version  -lncurses
% ./version <br/>

### input_num.h <br/>

single header library <br/>
 pseudo-implement the echo of character input  <br/>
 and input a numerical value  <br/>
 only positive numbers <br/>

run file <br/>
% gcc  input_num_test.c -o  input  -lncurses
% ./input <br/>

### cannon <br/>

Cannon game  <br/>

### snake <br/>

Snake game  <br/>

### tetris <br/>

Tetris game  <br/>

### Reference <br/>
- https://invisible-island.net/ncurses/announce.html#h3-documentation

