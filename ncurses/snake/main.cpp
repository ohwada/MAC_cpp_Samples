// 2022-05-01 K.OHWADA
// oroginal: https://github.com/romanedgn/sname-game

// changlog
// 2022-05-01
// added getNotArrowKey() to always show GAME OVER

// g++  main.cpp  fSnakeGame.cpp  -std=c++11 -o snake  `pkg-config --cflags --libs ncurses`


/*
This is the console executable, that makes use of the fSnakeGame class.
This is handling all user interaction. For game logic, please see fSnakeGame.h.
*/

 
#include "fSnakeGame.h"

int maxheight, maxwidth;
int curx, cury;
void PlayGame();
bool IsUserReady();
bool AskUserToPlayAgain();
void ClearCentre();
int UserInput();
void getNotArrowKey();


/**
 * main
 */
int main(int argc, char** argv)
{

 // wait for confirmation of the user
    if ( ! IsUserReady() ) {
	    return EXIT_SUCCESS;
	}

    while(1)
    {
 
			fSnakeGame NewSnake;

			int ret = NewSnake.PlayGame();

            if( ret == RET_QUIT ) {
	                if ( ! AskUserToPlayAgain() ) {
    	                break;
                    }
            }

            if( ret == RET_OVER ) {
                    getNotArrowKey();
	                if ( ! AskUserToPlayAgain() ) {
    	                break;
                    }
            }
    }

	return EXIT_SUCCESS;
}


/**
 *  getNotArrowKey
 */
void getNotArrowKey()
{

    nodelay(stdscr, false);

// repeat key input until a key other than ArrowKey is pressed
    while(1) {

        bool isArrowKey = false;

	    int ch = getch();

	switch(ch)
	{
        // if arrow key 
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_UP:
		case KEY_DOWN:
            isArrowKey = true;
            break;
	
        // others,
        default:
			break;
	    }

        // if not arrow key,,  finish
        if( ! isArrowKey) {
            break;
        }

    }

    return;
}


/**
 * ClearCentre
 * clear the screen and centre the cursor
 */
void ClearCentre(float x, float y)
{
	clear(); // clear the screen if the game is played for the 2nd time	
	initscr(); 
	noecho();
	getmaxyx(stdscr, maxheight, maxwidth);
    curx = (int)(maxheight/y);
    cury = (int)(maxwidth/x);
	move(curx, cury);
}

/**
 * UserInput
 * receive user confirmation
 */
int UserInput()
{
    nodelay(stdscr, false);

	int UserInput = getch();

	refresh();
	endwin();
	clear();

	return UserInput;	
}

/**
 * IsUserReady
 * print start menu
 */
bool IsUserReady() 
{
	ClearCentre(3, 2.5);
    attron(A_BOLD);	
	printw("Welcome to the Snake Game\n");
    
	move((curx+1), cury);
    attroff(A_BOLD);	
	printw("Are you ready? (y/n)");

	if ( UserInput() == 'y' ) {
        return true;
    }

    endwin();
    return false;
}


/**
 * AskUserToPlayAgain
 * print end of the game menu and ask user to play again
 */
bool AskUserToPlayAgain()
{

	ClearCentre(2.5, 2.5);
	printw("Do you want to play again? (y/n)");

    if ( UserInput() == 'y' ) {
        return true;
    }

    endwin();
	return false;
}


