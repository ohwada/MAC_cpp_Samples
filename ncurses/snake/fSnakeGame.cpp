// 2022-05-01 K.OHWADA
// oroginal: https://github.com/romanedgn/snake-game

// changlog
// 2022-05-01
// (1) added a return code to NewSnake.PlayGame() to always show GAME OVER
// (2) when the snake ate the fruit, made the snake's body longer


#include "fSnakeGame.h"
#include <unistd.h>

using namespace std;


/**
 * CharPosition constractor
 */
CharPosition::CharPosition(int col, int row)
{
	x = col;
	y = row;
}

/**
 * CharPosition constractor
 */
CharPosition::CharPosition()
{
	x = 0;
	y = 0;
}

/**
 * fSnakeGame constractor
 */
fSnakeGame::fSnakeGame()
{

	fruit.x = 0;
	fruit.y = 0;
	score = 0;	
	length = LENGTH_INIT;
	delay =  DELAY_INIT;

	isEatsFruit = false;
 	isKeyQuit = false;

	direction = DIR_LEFT;

	srand(time(NULL));
	
	InitGameWindow();
	PositionFruit();
	DrawWindow();
	DrawSnake();
	PrintScore();

	refresh();	
}

/**
 * fSnakeGame  destructor
 */
fSnakeGame::~fSnakeGame()
{
	endwin();
}


/**
 * InitGameWindow
 * initialise the game window
 */
void fSnakeGame::InitGameWindow() 
{ 
	initscr(); // initialise the screen
	nodelay(stdscr,true); // nonblock mode
	keypad(stdscr, true); // initialise the keyboard: we can use arrows for directions
	noecho(); // user input is not displayed on the screen
	curs_set(0); // cursor symbol is not not displayed on the screen (Linux)
	getmaxyx(stdscr, maxheight, maxwidth); // define dimensions of game window
	return; 
}

/**
 * DrawWindow
 * draw the game window
 */
void fSnakeGame::DrawWindow()
{
	for (int i = 0; i < maxwidth; i++) // draws top
	{
		move(0, i);
		addch(CHAR_EDGE);
	}

	for (int i = 0; i < maxwidth; i++) // draws bottom
	{
		move(maxheight-2, i);
		addch(CHAR_EDGE);
	}

	for (int i = 0; i < maxheight-1; i++) // draws left side
	{
		move(i, 0);
		addch(CHAR_EDGE);
	}

	for (int i = 0; i < maxheight-1; i++) // draws right side
	{
		move(i, maxwidth-1);
		addch(CHAR_EDGE);
	}
	return;
}

/**
 * DrawSnake
 * draw snake's body
 */
void fSnakeGame::DrawSnake()
{

	// set position
	for (int i = 0; i < length; i++) 
	{
		// when left direction
		snake.push_back(CharPosition((30+i), 10));
	}

	// draw snake
	for (int i = 0; i < snake.size(); i++)
	{
		move(snake[i].y, snake[i].x);
		addch(CHAR_SNAKE);
	}
	return;
}

/**
 * PrintScore
 * print score at botto of window
 */
void fSnakeGame::PrintScore()
{
	move((maxheight-1), 0);
	printw("Score: %d", score);
	return;
}

/*
 * PositionFruit
 *  position a new fruit in the game window
 */
void fSnakeGame::PositionFruit()
{
	while(1)
	{
		int tmpx = rand()%maxwidth+1; // +1 to avoid the 0
		int tmpy = rand()%maxheight+1;

		// check that the fruit is not positioned on the snake
		for (int i = 0; i < snake.size(); i++)
		{
			if (snake[i].x == tmpx && snake[i].y == tmpy)
			{
				continue; // if true, ignore the following and go back to the beginning of function
			}
		}

		// check that the fruit is positioned within the game window
		if (tmpx >= maxwidth-2 || tmpy >= maxheight-3)
		{
			continue; // if true, ignore the following and go back to the beginning of function
		}

		// if the coordinates are valid, add fruit in the window
		fruit.x = tmpx;
		fruit.y = tmpy;
		break;
	}

	move(fruit.y, fruit.x); 
	attron(A_BOLD);	
	addch(CHAR_FRUIT);
	attroff(A_BOLD);	
	refresh();
}

/*
 * FatalCollision
 *  set game over situations
 */
bool fSnakeGame::FatalCollision()
{
	// if the snake hits the edge of the window
	if (snake[0].x == 0 || snake[0].x == maxwidth-1 || snake[0].y == 0 || snake[0].y == maxheight-2)
	{
		return true;
	}

	// if the snake collides into himself
	for (int i = 2; i < snake.size(); i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			return true;
		}
	}

	return false;
}

/**
 * GetsFruit
 *  define behaviour when snake eats the fruit
 */
bool fSnakeGame::GetsFruit()
{
	if (snake[0].x == fruit.x && snake[0].y == fruit.y)
	{
		PositionFruit(); 

		score += SCORE_INC; 
		PrintScore();

		length += LENGTH_INC;

		delay += DELAY_INC ;
		
		// if score is a multiple of 100, increase snake speed
		if ((score%100) == 0)
		{
			delay -= DELAY_DEC ;
		}

		return isEatsFruit = true;
	}
	else 
	{
		return isEatsFruit = false;
	}
	return isEatsFruit;
}

/**
 * MoveSnake
 *  define snake's movements
 */
void fSnakeGame::MoveSnake()
{
	const int KEY_ESC = 27;

	isKeyQuit = false;

	int KeyPressed = getch();

	switch(KeyPressed)
	{
		case KEY_LEFT:
			if (direction != DIR_RIGHT) 
			{ direction = DIR_LEFT; }  
			break;

		case KEY_RIGHT:
			if (direction != DIR_LEFT)
			{ direction = DIR_RIGHT; }
			break;

		case KEY_UP:
			if (direction != DIR_DOWN)
			{ direction = DIR_UP; }
			break;

		case KEY_DOWN:
			if (direction != DIR_UP)
			{ direction = DIR_DOWN; }
			break;

		case KEY_BACKSPACE:
		case KEY_ESC:
			// key to quit the game
			isKeyQuit = true;
			break;
	}


	// the snake moves and we add an extra character at the beginning of the vector
	// add a head and initialise new coordinates for CharPosition according to the direction input
	if (direction == DIR_LEFT)
	{ snake.insert(snake.begin(), CharPosition(snake[0].x-1, snake[0].y)); } 
	else if (direction == DIR_RIGHT)
	{ snake.insert(snake.begin(), CharPosition(snake[0].x+1, snake[0].y)); }
	else if (direction == DIR_UP)
	{ snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y-1)); }
	else if (direction == DIR_DOWN)
	{ snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y+1)); }

	// move to the new CharPosition coordinates
	move(snake[0].y, snake[0].x);
	addch(CHAR_SNAKE); // draw a new head

//　Make the snake's body longer until it reaches length
if( snake.size() >= length  ){

		// moves at the end of the tail
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); 

		printw(" "); // add empty ch to remove last character
	
		snake.pop_back(); // removes the last element in the vector, reducing the container size by one
}

	refresh();

	return;
}


/**
 * PlayGame
 */
int  fSnakeGame::PlayGame()
{
	int ret= RET_NULL;

    while(1)
    {
        if (FatalCollision())
        {
			PrintGameOver();
 			ret = RET_OVER;
            break;

        }

        GetsFruit();
        MoveSnake();

        if (isKeyQuit)
        {
			ret = RET_QUIT;
        	break;
        }

		// wait
        usleep(delay); 
    }

	return ret;
}


/**
 *  PrintGameOver
 */
void fSnakeGame::PrintGameOver()
{
 		int x = (maxheight-2)/2;
		int y = (maxwidth-5)/2;

        move(x, y);
   		attron(A_BOLD);	
        printw("GAME OVER");
   		attroff(A_BOLD);	

        move( (x+1), y);
        printw("press return key");
}

