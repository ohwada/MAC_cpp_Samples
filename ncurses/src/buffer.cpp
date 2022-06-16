/*
 * buffer.cpp
 * Scrool Buffer for Screen
 * 2022-0501 K.OHWADA 
*/


#include <ncurses.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "buffer.hpp"


const char SPACE = ' ';
const char ZERO = '\0';


const int LINE_SIZE = 20;
const int BUF_SIZE = 128;
static char buf[LINE_SIZE][BUF_SIZE];


/*
 * constractor
*/
Buffer::Buffer()
{
	ptr_buf = 0;
	ptr_scr = 0;
	 is_draw = true;
	clearBuf();
}

/*
 * destractor
*/
Buffer::~Buffer()
{
	// none
}


/*
 * setup
*/
void Buffer::setup(int buf_x1, int buf_y1, int buf_h1)
{
 	buf_x = buf_x1;
	buf_y = buf_y1;
	buf_h = buf_h1;

	int h, w;
	getmaxyx(stdscr, h, w);
	scr_h = h;
	scr_w = w;
}


/*
 * addLine
*/
void Buffer::addLine( char *str )
{
	addLineBuf( str );
	if(  is_draw ) {
		addLineScr( str );
	}
}


/*
 * addLine
*/
void Buffer::addLineBuf( char *str )
{
	if ( ptr_buf < BUF_SIZE )
	{
		strcpy( buf[ptr_buf], str); 
		ptr_buf ++;
	} else {
  		ptr_buf = 0;
	}
}


/*
 * addLine
*/
void Buffer::addLineScr( char *str )
{
	const int SLEEP = 100000; // 0.1 sec
	if(ptr_scr < buf_h)
	{
		int x = buf_x + ptr_scr;
		move(x, buf_y);
// wait a bit
// because the cursor position doesn't seem to change immediately
		usleep(SLEEP);
		addstr(str);
 		ptr_scr ++;
	} else {
		scrollUp();
	}
}


/*
 * addTop
*/
void Buffer::addTop( char *str)
{
	addTopBuf(str);
	addTopScr(str);
}


/*
 * addTop
*/
void Buffer::addTopBuf( char *str)
{
	clearBuf();
	strcpy(buf[0], str);
	ptr_buf = 1;
}


/*
 * addTop
*/
void Buffer::addTopScr( char *str)
{
	clearScr();
	move(buf_x, buf_y);
	addstr(str);
	ptr_scr = 1;
}


/*
 * setEnable
*/
void Buffer::enableDraw(bool flag)
{
	 is_draw = flag;
}


/*
 * clearBuffer
*/
 void Buffer::clearBuffer()
{
 	clearBuf();
	ptr_buf = 0;
	clearScr();
	ptr_scr = 0;
}


/*
 * clearBuff
*/
 void Buffer::clearBuf()
{
	for(int i=0; i<LINE_SIZE; i++)
	{
		buf[i][0] = ZERO;
	}
}


/*
 * clearLine
*/
void Buffer::clearScr()
{
	for(int i=0; i<buf_h; i++)
	{
		int x = buf_x +i;
		clearScrLine(x);
	}
}


/*
 * clearScrLine
*/
 void Buffer::clearScrLine( int x)
{
	for(int y=0; y<scr_w; y++)
	{
		move(x, y);
		addch(SPACE);
	}
}


/*
 * scrollUp
*/
void Buffer::scrollUp()
{
	scrollUpBuf();
	scrollUpScr();
}


/*
 * scrollUp
*/
void Buffer::scrollUpBuf()
{
	char line[BUF_SIZE];

strcpy(line, buf[0]);

	for( int i=0; i<LINE_SIZE-1; i++)
	{

		if (strlen(buf[i+1] ) > 0)
		{
			strcpy( buf[i], buf[i+1] );
		} else {
			strcpy(buf[i], line);
			break;
		}
	} // for

	for( int i=0; i<LINE_SIZE; i++)
	{
		if (strlen(buf[i] ) == 0){
			ptr_buf = i;
			break;
		}
	} // for
}


/*
 * scrollUp
*/
void Buffer::scrollUpScr()
{
	clearScr();
	ptr_scr = 0;

	for(int i=0; i< buf_h; i++)
	{
		if ( strlen(buf[i]) > 0)
		{
			int x = buf_x +i;
			move(x, buf_y);
			addstr( buf[i] );
			ptr_scr ++;
		}
	} // for
}


/*
 * scrollUp
*/
void  Buffer::dumpBuffer(int x1, int y1)
{
	for(int i=0; i<LINE_SIZE; i++)
	{
		int x = x1+i;
		if(x < scr_h) {
			move(x, y1);
			printw("%d: %s", i, buf[i] );
		} else {
			break;
		}
	} // for
}


/**
 * addF
 */
void  Buffer::addF(char* format, ...)
{

    const int BUFSIZE = 128;
    char buf[BUFSIZE];

    va_list ap;

    va_start(ap, format);

    vsprintf(buf, format, ap);

    va_end(ap);

    addLine(buf);
}
