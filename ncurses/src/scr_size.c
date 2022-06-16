/*
	* scr_size.c
 * display Screen Size
 * 2022-0501 K.OHWADA 
*/


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
	char *format = "scr: %d x %d";

	// start terminal control
	initscr();

// set to mode that does not display the cursor
	curs_set(0); 

// get screen size
	getmaxyx(stdscr, h, w);

// move to center
	y = h/2;
	x = (w - strlen(format))/2;

	move(y, x);
	printw(format, h, w);

// wait forever until the key is pressed
	timeout(-1);

// eEnter characters
	getch();	

	// finish terminal control
	endwin();	

	return 0;
}

