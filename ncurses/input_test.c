/**
 * iput_test.c
 * 2020-05-01 K.OHWADA
 */


// gcc  input_test.c input.c -o  input  `pkg-config --cflags --libs ncurses`


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "input.h"


const char KEY_ESC = 27;



/**
 * main
 */
int main()
{
    int h;
    int w; 


	initscr();
	curs_set(0); 

	getmaxyx(stdscr, h, w);

    int x = h/2;
    int y = h/2;

  noecho();            
  cbreak();            
  keypad(stdscr,TRUE);

    move(x, y);
    addstr("input>");

    int ch;

while(1)
{
	ch = getch();
    if(ch == KEY_ESC){
        break;
    }

    int num = input(ch);

if( num != -1){
        move(x+2, y);
        printw("num = %d ", num);
 }

} // while

	timeout(-1);
	getch();	
  endwin();      
      
  return EXIT_SUCCESS;
}

