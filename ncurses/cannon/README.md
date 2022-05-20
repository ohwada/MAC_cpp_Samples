cannon
===============

Cannon game using ncurses <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/ncurses/cannon/cannon.png" width="300" /><br/>

### Requires <br/>
- ncurses <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/ncurses <br/>

### Run the file <br/>

% gcc  main.c  object.c  gameutil.c -o cannon  `pkg-config --cflags --libs ncurses` 
 <br/>
% ./cannon <br/>

### How to play <br/>

fire cannon and shoot down enemy aircrafts <br/>
No wins or losses, no score, lasts forever <br/>

[Space] key :  fire bullet <br/>
[z] key " fire missile <br/>
Up key [↑] : turn up the cannon  <br/>
 Down Key  [↓] : turn down the cannon <br/>
 [q] key : quit the game <br/>

### Reference <br/>
- https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/
