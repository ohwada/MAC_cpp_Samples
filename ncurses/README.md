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
% gcc hello.c -o hello `pkg-config --cflags --libs ncurses`
% ./hello <br/>

### version.c <br/>

 display  version <br/>

run file <br/>
% gcc version.c -o version `pkg-config --cflags --libs ncurses`
% ./version <br/>

### snake <br/>

sname game  <br/>

### Reference <br/>
- https://invisible-island.net/ncurses/announce.html#h3-documentation

