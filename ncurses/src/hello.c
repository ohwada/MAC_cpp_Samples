/*
	* hello.c
 * display  "Hello World"
 * 2022-0501 K.OHWADA 
*/


// original: https://www.kushiro-ct.ac.jp/yanagawa/ex-2017/2-game/01.html#exercise

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

/**
 * main
 */
int main()
{
	int  x, y, w, h;
	char *str = "Hello World";

	// start terminal control
	initscr();

// set to mode that does not display the cursor
	curs_set(0); 

// get screen size
	getmaxyx(stdscr, h, w);

// move to center
	y = h/2;
	x = (w - strlen(str))/2;

	move(y, x);

	// highlighting
	attron(A_BOLD);		

// display a string
	addstr(str);

// wait forever until the key is pressed
	timeout(-1);

// eEnter characters
	getch();	

	// finish terminal control
	endwin();	

	return 0;
}

