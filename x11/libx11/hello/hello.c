/**
 * hello.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://uguisu.skr.jp/Windows/x11.html

#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>


/**
 * main
 */
int main()
{
// this font will work after trying various things
const char FONT[] =  "lucidasanstypewriter-bold-24";

const char HELLO[]= "Hello World!!";
 
// window size

const int W  = 320;
const int H  = 240;

// font width
// it constant
// because I didn't know how to get it
const int FW  = 12;

  Display *d;  // Display struct
  Window  wr;  // window identifier
  Font    f;   // font identifier
  GC      gc;  // GC identifier
  XEvent  event;  // XEvent struct

  unsigned long black, white;

// connrct to display
  d=XOpenDisplay(NULL);  
if(!d){
    printf("cannot open display \n");
    return 1;
}

  black=BlackPixel(d, 0);   // get black pixel value
  white=WhitePixel(d, 0);   // get white pixel value

  wr=XCreateSimpleWindow(d, RootWindow(d, 0), 
        100, 100,        // position of the root window
		W, H,        // width, height
		2, black, white);// frame width, frame color window body color

// event mask to select Expose event
  XSelectInput(d, wr, ExposureMask); 


// window wr map
  // https://uguisu.skr.jp/Windows/x11.html
  XMapWindow(d, wr);     

// request to create GC for window
gc =XCreateGC(d, wr, 0, 0); 

// load font  by name 
      f=XLoadFont(d, (char *)FONT); 
    if( !f ){
        printf("cannot load font: %s \n", FONT);
        return 1;
    }

// set font to GC
XSetFont(d, gc,  f); 

// endless lopp
  while(1) 
{
// extract Event from the event queue
    XNextEvent(d, &event); 
 
// event type
    switch(event.type)    
{
// draw when expose event
    case Expose :
      
// // set black setting for the foreground color
      XSetForeground(d, gc,  black); 

// draw center of window
        int len = strlen(HELLO);
        int x = W/2 - (FW*len)/2;
       int y = H/2;
     XDrawString(d, wr, gc,  x, y,  (char *)HELLO, len);

// forced sending of request
      XFlush(d);

    } // switch
  } // while
	return 0;
}

