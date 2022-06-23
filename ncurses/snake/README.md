ncurses. Snake
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/ncurses/snake/screenshots/tetris.png" width="300" /><br/>

This is Clone <br/>
https://github.com/romanedgn/snake-game <br/>

Changes:  <br/>
(1) added a return code to NewSnake.PlayGame() to always show GAME OVER   <br/>
(2) when the snake ate the fruit, made the snake's body longer  <br/>


### About  <br/>
Snake is one of clasic games <br/>
https://en.wikipedia.org/wiki/Snake_(video_game_genre) <br/>
This version is  program in C using ncurses. <br/>


### Requires <br/>
- ncurses <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/ncurses <br/>

### Run the file <br/>
% make <br/>
% ./snake <br/>

### The rules
There has never been a more simple game.  <br/>
Control the snake with the arrow keys and eat the fruit (*).  <br/>When you eat the fruit, you gain 10 points. <br/>
and the snake's body gets longer  <br/>
Every 100 points, the snake's speed will increase.  <br/>
If you hit the borders of the game window, it's game over.  <br/>
or if the snake collapse into his own body, it's game over. (  <br/>


