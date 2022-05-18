snake
===============

sname game using ncurses <br/>

### Requires <br/>
- ncurses <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/ncurses <br/>

### Run the file <br/>
% g++  main.cpp  fSnakeGame.cpp -std=c++11 -o snake  `pkg-config --cflags --libs ncurses` <br/>
% ./snake <br/>

### The rules
There has never been a more simple game.  <br/>
Control the snake with the arrow keys and eat the fruit (*).  <br/>When you eat the fruit, you gain 10 points. <br/>
and the snake's body gets longer ( not implemented ) <br/>
Every 100 points, the snake's speed will increase.  <br/>
If you hit the borders of the game window, it's game over.  <br/>
or if the snake collapse into his own body, it's game over. ( not implemented ) <br/>

### TODO
 - when the snake eat the fruit, make the snake's body longer <br/>
- when the snake collapse into his own body, make game over.  <br/>

### Reference <br/>
- https://github.com/romanedgn/snake-game

