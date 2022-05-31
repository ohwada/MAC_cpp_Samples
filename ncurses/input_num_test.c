/**
 * iput_num_test.c
 * 2020-05-01 K.OHWADA
 */


// gcc  input_num_test.c -o  input  `pkg-config --cflags --libs ncurses`


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "input_num.h"

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

    int cx = h/2;
    int cy = h/2;

    int x1 = cx;
    int x2 = cx+2;
    int x3 = cx+4;

  noecho();            
  cbreak();            
  keypad(stdscr,TRUE);

    move(x3, cy);
    addstr("press ESC to exit");

   // wait to input
   move(x1, cy);
    addstr("input>");

    int ch;

while(1)
{
	ch = getch();
    if(ch == KEY_ESC){
        break;
    }

    int num = input_num(ch);

if( num != -1){
        move(x2, cy);
        printw("num = %d    ", num);
        move(x1, cy);
        addstr("          ");
        // wait to input
        move(x1, cy);
        addstr("input>");
 }

} // while

	timeout(-1);
	getch();	
  endwin();      
      
  return EXIT_SUCCESS;
}

