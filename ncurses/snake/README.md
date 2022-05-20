snake
===============

Snake game using ncurses <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/ncurses/snake/snake.png" width="300" /><br/>

### Requires <br/>
- ncurses <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/ncurses <br/>

### Run the file <br/>
% g++  main.cpp  fSnakeGame.cpp -std=c++11 -o snake  `pkg-config --cflags --libs ncurses` <br/>
% ./snake <br/>

### The rules
There has never been a more simple game.  <br/>
Control the snake with the arrow keys and eat the fruit (*).  <br/>When you eat the fruit, you gain 10 points. <br/>
and the snake's body gets longer  <br/>
Every 100 points, the snake's speed will increase.  <br/>
If you hit the borders of the game window or if the snake collapse into his own body, it's game over. <br/>


### Reference <br/>
- https://github.com/romanedgn/snake-game

