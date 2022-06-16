/*
 * test_buffer.cpp
 * 2022-0501 K.OHWADA 
*/


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "buffer.hpp"

void addNewLine();
void addFormat();
void toggleEnable(int x1, int y1);

const char KEY_ESC = 27;
const char KEY_SPACE = ' ';
const char KEY_T = 't';
const char KEY_Z = 'z';
const char KEY_C = 'c';
const char KEY_D = 'd';
const char KEY_F = 'f';

Buffer buffer;

int input_cnt = 0;
bool isDraw = true;

/**
 * main
 */
int main()
{

	const char STR_ADD_TOP[] = "input>";

	int  x, y, w, h;

	initscr();
	curs_set(0); 
	getmaxyx(stdscr, h, w);


	int buf_x = h/2;
	int buf_y = w/2;
	int buf_h = 10;

// dump
	int dump_x = buf_x;
	int dump_y = buf_y+10;

// enable
	int enable_x = buf_x -2;
	int enable_y = buf_y+5;

	buffer.setup( buf_x, buf_y, buf_h);

  	curs_set(0); 
    noecho();            
    cbreak();  
    keypad(stdscr,TRUE);          

	int x0 = 2;
	int y0 = buf_y+10;
	move(x0, y0);
	addstr(" SCROLL BUFFER");
	move(x0+1, y0);
	addstr(" [SPACE] add line");
	move(x0+2, y0);
	addstr(" [z] add top");
	move(x0+3, y0);
	addstr(" [f] add format");
	move(x0+4, y0);
	addstr(" [c] clear buffer");
	move(x0+5, y0);
	addstr(" [UP] scroll up");
	move(x0+6, y0);
	addstr(" [t] togle Enable");
	move(x0+7, y0);
	addstr(" [ESC] quit");

	move(buf_x-1, buf_y-5);
	addstr("----------");
	move(buf_x+buf_h, buf_y-5);
	addstr("----------");

	timeout(-1);

while(1)
{
	int ch = getch();	
	if(ch == KEY_ESC) {
		break;
	}

switch(ch)
{
    case KEY_UP:
        buffer.scrollUp();
        break;
    case KEY_SPACE:
        addNewLine();
        break;
case KEY_C:
        buffer.clearBuffer();
		break;
case KEY_D:
        buffer.dumpBuffer(dump_x, dump_y);
		break;
case KEY_F:
        addFormat();
		break;
case KEY_T:
		toggleEnable(enable_x, enable_y);
		break;
case KEY_Z:
        	buffer.addTop( (char *)STR_ADD_TOP );
		break;


} // switch

} // while

	getch();	
	endwin();	

	return 0;
}


/**
 * addNewLine
 */
void addNewLine()
{
	const int BUFSIZE = 100;
	char tenable_xt[BUFSIZE]; 

	snprintf(tenable_xt, BUFSIZE-1, "%d", input_cnt);   
	input_cnt ++;
	buffer.addLine(tenable_xt);
}


/**
 * taddFormat
 */
void addFormat()
{
	char s[] = "abc";
	int d = 123;
	float f = 3.14;

	buffer.addF( (char *)"%s, %d, %f", s, d, f );
}


/**
 * toggleEnable
 */
void toggleEnable(int enable_x, int enable_y) 
{
	isDraw = ! isDraw;

	buffer.enableDraw(isDraw);
	move(enable_x, enable_y);

	if(isDraw){
		addstr("[true]");
	} else {
		addstr("[false]");
	}
}
