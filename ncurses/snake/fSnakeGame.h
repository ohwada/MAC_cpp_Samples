// 2022-05-01 K.OHWADA
// oroginal: https://github.com/romanedgn/snake-game

/*
This is the game logic (no user interaction).
The game is a very simple version of the classic snake game.
*/

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

#ifndef FSNAKEGAME_H
#define FSNAKEGAME_H

// return code
const int RET_NULL = 0;
const int RET_QUIT = 1;
const int RET_OVER  = 2;

// snake speed
const int DELAY_INIT = 200000; // 0.2 sec
const int DELAY_INC = 10000;  // 0.01 sec
const int DELAY_DEC = 50000;  // 0.05 sec

// snake lngth
const int LENGTH = 5;

// score
const int SCORE_INC = 10; 



// the character representing the snake's body
	const char  CHAR_SNAKE  = 'x'; // character to represent the snake

	// fruitchar is the character representing the fruit
	const char CHAR_FRUIT= '*'; // star

// the character representing the edge of the game window
const char CHAR_EDGE  = (char)219; // full rectangle on the key table

// derection
	const char DIR_LEFT = 'l';
	const char DIR_RIGHT = 'r';
	const char DIR_UP = 'u';
	const char DIR_DOWN = 'd';


/**
 * struct CharPosition
 */
struct CharPosition 
{
	int x, y;
	CharPosition(int col, int row);
	CharPosition();
};


/**
 * class fSnakeGame 
 */
class fSnakeGame 
{
private:
	int score, length, delay, maxwidth, maxheight;
	char direction;
	bool isEatsFruit, isKeyQuit;

	CharPosition fruit; // need to clarify this combination 
	std::vector<CharPosition> snake; // represent the snake's body

	void InitGameWindow();
	void DrawWindow();  
	void DrawSnake();
	void PrintScore();
	void PositionFruit();
	bool FatalCollision();
	void MoveSnake();
	bool GetsFruit();
	void PrintGameOver();

public:
	fSnakeGame();
	~fSnakeGame(); // destructor for cleanup and memory deallocation
	int PlayGame();
};

#endif