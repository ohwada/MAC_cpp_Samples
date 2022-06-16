/**
 * keypad.c
* enable Arrow key ( Cursor key)
 * 2020-05-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <curses.h>


/**
 * main
 */
int main(int argc, char *argv[])
{
    const char KEY_ESC = 27;

    const int BUFSIZE = 10;
    char buf[BUFSIZE];

    int h, w;

	initscr();
	getmaxyx(stdscr, h, w);

    int cx = h/2;
    int cy = w/2;

    curs_set(0); 
    noecho();            
    cbreak();            
    keypad(stdscr,TRUE);

    move(cx-4, cy-5);
    addstr("press Arreow Key");
    move(cx-3, cy-5);
    addstr("[esc] quit");

    char* str;

while(1)
{
	int ch = getch();

    if( ch == KEY_ESC){
        break;
    }


switch(ch)
{
    case KEY_UP:
        str = "UP";
        break;
    case KEY_DOWN:
        str = "DOWN";
        break;
    case KEY_RIGHT:
        str = "RIGHT";
        break;
    case KEY_LEFT:
        str = "LEFT";
        break;
    default:
        snprintf(buf, BUFSIZE-1, "%d", ch);
        str = buf;
        break;
} // swtch

    move(cx, cy);
        addstr("          ");

    move(cx, cy);
    addstr(str);

}// while
        endwin();  
          
        return 0;
    }
