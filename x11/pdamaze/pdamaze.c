/*
  pdamaze.c
 
  A 3D maze game for the Agenda VR3 Linux-based PDA.
  
  by Bill Kendrick
  bill@newbreedsoftware.com
  http://www.newbreedsoftware.com/pdamaze/

  May 23, 2001 - October 5, 2001
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <unistd.h>
#include <sys/time.h>

#include "images/loading.xpm"
#include "images/title.xpm"
#include "images/done.xpm"
#include "images/soundon.xpm"
#include "images/soundoff.xpm"
#include "images/start.xpm"
#include "images/numbers.xpm"
#include "images/options.xpm"
#include "images/optionson.xpm"
#include "images/timeup.xpm"
#include "images/youwin.xpm"

#include "images/cmp_east.xpm"
#include "images/cmp_north.xpm"
#include "images/cmp_south.xpm"
#include "images/cmp_west.xpm"

#include "images/bkg_east.xpm"
#include "images/bkg_north.xpm"
#include "images/bkg_south.xpm"
#include "images/bkg_west.xpm"
#include "images/ground.xpm"

#include "images/close_center.xpm"
#include "images/close_center_bright.xpm"
#include "images/close_left.xpm"
#include "images/close_left_bright.xpm"
#include "images/close_right.xpm"
#include "images/close_right_bright.xpm"

#include "images/middle_center.xpm"
#include "images/middle_center_bright.xpm"
#include "images/middle_left.xpm"
#include "images/middle_left_bright.xpm"
#include "images/middle_right.xpm"
#include "images/middle_right_bright.xpm"

#include "images/far_center.xpm"
#include "images/far_center_bright.xpm"
#include "images/far_left.xpm"
#include "images/far_left_bright.xpm"
#include "images/far_right.xpm"
#include "images/far_right_bright.xpm"



/* Definitions: */

enum {
  DIR_NORTH,
  DIR_EAST,
  DIR_SOUTH,
  DIR_WEST
};

enum {
  FAR,
  MID,
  CLOSE
};

enum {
  TIMER_MODE_UP,
  TIMER_MODE_DOWN,
  NUM_TIMER_MODES
};

enum {
  MAP_MODE_ALL,
  MAP_MODE_BUILD,
  MAP_MODE_NONE,
  NUM_MAP_MODES
};


int xm[4] = {0, 1, 0, -1};
int ym[4] = {-1, 0, 1, 0};

#define MAX_SIZE 39


/* Globals: */

Display *display;
Window window;
GC whitegc, blackgc, pastegc;

Pixmap backbuffer, scrollbuf;
Pixmap pix_loading;
Pixmap pix_done, pix_start, pix_numbers, pix_title, pix_soundon, pix_soundoff;
Pixmap pix_options, pix_optionson, pix_timeup, pix_youwin;
Pixmap pix_cmp_east, pix_cmp_north, pix_cmp_south, pix_cmp_west;
Pixmap pix_bkg_east, pix_bkg_north, pix_bkg_south, pix_bkg_west, pix_ground;
Pixmap pix_close_left, pix_close_center, pix_close_right,
       pix_close_left_bright, pix_close_center_bright, pix_close_right_bright,
       pix_mid_left, pix_mid_center, pix_mid_right,
       pix_mid_left_bright, pix_mid_center_bright, pix_mid_right_bright,
       pix_far_left, pix_far_center, pix_far_right,
       pix_far_left_bright, pix_far_center_bright, pix_far_right_bright;

XKeyboardState kbstate;

int timer_mode, map_mode, maze_size, sound, timer;

int xpos, ypos, dir;


int maze[MAX_SIZE][MAX_SIZE],
    seenmaze[MAX_SIZE][MAX_SIZE];


/* Local function prototypes: */

int title(void);
void game(void);
void drawscreen(int scroll);
void drawwall(int block, int dist, int xoffset);
void draw_map(void);
void draw_compass(void);
void draw_farcenter(int xx);
void draw_farleft(int xx);
void draw_farright(int xx);
void draw_midcenter(int xx);
void draw_midleft(int xx);
void draw_midright(int xx);
void draw_closecenter(void);
void draw_closeleft(void);
void draw_closeright(void);
void drawbkg(Pixmap pix, int yy);
void setup(void);
GC CreateGC(Display *display, Drawable drawable, unsigned long forecolor,
            unsigned long backcolor);
void LoadImage(char ** xpm, Pixmap * pix, int percent);
int mazechunk(int xx, int yy);
void swapbuffer(void);
void create_maze(int size);
void playsound(int pitch, int duration);
void drawtimer(void);
void finish(void);


/* --- MAIN! --- */

int main(int argc, char * argv[])
{
  int done;


  setup();

  do
  {
    done = title();

    if (!done)
      game();
  }
  while (!done);

  
  finish();
  

  return(0);
}


int title(void)
{
  int redraw_screen;
  int done, quit;
  XEvent event;


  redraw_screen = 1;
  done = 0;
  quit = 0;

  
  do
    {
      /* Handle events: */
      
      while (XPending(display))
	{
	  XNextEvent(display, &event);
	  
	  if (event.type == Expose)
	    {
	      /* Expose! */
	      
	      redraw_screen = 1;
	    }
	  else if (event.type == ButtonPress)
	    {
	      if (event.xbutton.y >= 160)
		{
		  /* Tap in the options area! */
		  
		  if (event.xbutton.y <= 196)
		    {
		      /* Directly on the icon (not on an option) */
		      
		      if (event.xbutton.x < 40)
		      {
		        /* Timer mode: */

			timer_mode = ((timer_mode + 1) % NUM_TIMER_MODES);
		      }
		      else if (event.xbutton.x < 80)
		      {
			/* Map mode: */

			map_mode = ((map_mode + 1) % NUM_MAP_MODES);
		      }
		      else if (event.xbutton.x < 120)
		      {
			/* Maze size: */
			
			maze_size = maze_size + 10;
			if (maze_size > MAX_SIZE)
			  maze_size = 19;
		      }
		      else
		      {
		        /* Sound: */

			sound = !sound;
		      }


		      redraw_screen = 1;
		    }
		  else if (event.xbutton.y < 226)
		    {
		      /* Directly on an option! */
		      
		      if (event.xbutton.x < 40)
			{
			  if (event.xbutton.y >= 196 &&
			      event.xbutton.y < 206)
			    timer_mode = 0;
			  else if (event.xbutton.y >= 206 &&
				   event.xbutton.y < 216)
			    timer_mode = 1;
			}
		      else if (event.xbutton.x < 80)
			{
			  map_mode = (event.xbutton.y - 196) / 10;
			}
		      else if (event.xbutton.x < 120)
			{
			  maze_size = ((((event.xbutton.y - 196) / 10) * 10)
				       + 19);
			}
		      else
			{
			  if (event.xbutton.y >= 196 &&
			      event.xbutton.y < 206)
			    sound = 1;
			  else if (event.xbutton.y >= 206 &&
				   event.xbutton.y < 216)
			    sound = 0;
			}
		      
		      redraw_screen = 1;
		    }
		  else
		    {
		      /* On a control button at the very bottom: */

		      if (event.xbutton.x <= 40)
		        {
		          /* "Done" button.  Quit! */

			  done = 1;
			  quit = 1;
		        }
		      else if (event.xbutton.x >= 120)
		        {
	                  /* "Start" button.  Begin! */
			
			  done = 1;
		        }
		    }
		}
	    }
	}
      
      
      if (redraw_screen)
	{
	  redraw_screen = 0;
	  
	  
	  /* Draw title: */
	  
	  XCopyArea(display, pix_title, window, whitegc,
		    0, 0, 160, 160, 0, 0);
	  
	  
	  /* Draw options: */
	  
	  XCopyArea(display, pix_options, window, whitegc,
		    0, 0, 160, 80, 0, 160);


	  /* Draw active options: */

	  XCopyArea(display, pix_optionson, window, whitegc,
	            0, timer_mode * 10,
		    40, 10,
		    0, 196 + (timer_mode * 10));

	  XCopyArea(display, pix_optionson, window, whitegc,
	            40, map_mode * 10,
		    40, 10,
		    40, 196 + (map_mode * 10));

	  XCopyArea(display, pix_optionson, window, whitegc,
		    80, (maze_size - 19),
		    40, 10,
		    80, 196 + (maze_size - 19));  /* this is sick! */

	  XCopyArea(display, pix_optionson, window, whitegc,
	            120, (!sound) * 10,
		    40, 10,
		    120, 196 + ((!sound) * 10));


	  /* Draw control buttons: */

	  XCopyArea(display, pix_done, window, whitegc,
	            0, 0, 40, 12, 0, 228);

	  XCopyArea(display, pix_start, window, whitegc,
		    0, 0, 40, 12, 120, 228);

	  
	  XFlush(display);
	}
      
      usleep(100);
    }
  while (!done);
  
  return(quit);
}


/* --- GAME! --- */


void game(void)
{
  int done, redraw_screen, move_forward, footstep, turn;
  int oxpos, oypos, odir;
  XEvent event;
  KeySym key;
  struct timeval now, then;

  
  done = 0;

  create_maze(maze_size);
  xpos = (maze_size / 2) + 1;
  ypos = (maze_size / 2) + 1;

  xpos = xpos + (xpos % 2);
  ypos = ypos + (ypos % 2);
  
  timer = 0;
  
  
  /* Pick a direction (where there's no wall!) */
  
  do
    {
      dir = (rand() % 4);
    }
  while (maze[ypos + ym[dir]][xpos + xm[dir]] == 255);

  odir = dir;
  
  footstep = 0;

  
  /* Clear screen: */

  XFillRectangle(display, window, whitegc, 0, 0, 160, 240);
  XFlush(display);

  
  redraw_screen = 1;
  gettimeofday(&then, NULL);
  
  do
    {
      move_forward = 0;
      turn = 0;
      
      oxpos = xpos;
      oypos = ypos;
      odir = dir;
      
      
      /* Handle all pending events: */
      
      while (XPending(display))
	{
	  XNextEvent(display, &event);
	  
	  
	  if (event.type == Expose)
	    {
	      /* Expose! Redraw! */
	      
	      redraw_screen = 1;
	    }
	  else if (event.type == KeyPress)
	    {
	      /* Keypress! */
	      
	      key = XLookupKeysym((XKeyEvent *)&event, 0);
	      
	      if (key == XK_Left)
		{
		  /* Rotate CCW */
		  
		  turn = -1;	      
		}
	      else if (key == XK_Right)
		{
		  /* Rotate CW */
		  
		  turn = 1;
		}
	      else if (key == XK_Up || key == XK_Page_Up)
		{
		  /* Move forward: */
		  
		  move_forward = 1;
		}
	      else if (key == XK_Down || key == XK_Page_Down)
		{
		  /* Move back: */
		  
		  move_forward = -1;
		}
	      else if (key == XK_Escape)
		{
		  /* Quit! */
		  
		  done = 1;
		}
	    }
	  else if (event.type == ButtonPress)
	    {
	      /* Click! */
	      
	      if (event.xbutton.y >= 228 &&
		  event.xbutton.x <= 40)
		{
		  /* Done button! */
		  
		  done = 1;
		}
	      else if (event.xbutton.y >= 228 &&
		       event.xbutton.x >= 120)
	        {
		  /* Sound button! */
		
		  sound = !sound;

		  if (sound)
	 	    {
		      XCopyArea(display, pix_soundon, window, whitegc,
		                0, 0, 40, 12, 120, 228);
		    }
		  else
		    {
		      XCopyArea(display, pix_soundoff, window, whitegc,
		                0, 0, 40, 12, 120, 228);
		    }

		  XFlush(display);
		}
	      else if (event.xbutton.y <= 160)
		{
		  /* Within the 3D display...  move based on it! */
		  
		  if (event.xbutton.x < 80 &&
		      ((event.xbutton.y < 80 &&
			event.xbutton.x <= event.xbutton.y) ||
		       (event.xbutton.y >= 80 &&
			event.xbutton.x <= 160 - event.xbutton.y)))
		    {
		      /* Rotate CCW */
		      
		      turn = -1;  
		    }
		  else if (event.xbutton.x >= 80 &&
			   ((event.xbutton.y < 80 &&
			     160 - event.xbutton.x <= event.xbutton.y) ||
			    (event.xbutton.y >= 80 &&
			     event.xbutton.x >= event.xbutton.y)))
		    {
		      /* Rotate CCW */
		      
		      turn = 1;  
		    }
		  else if (event.xbutton.y < 80)
		    {
		      /* Move forward: */
		      
		      move_forward = 1;
		    }
		  else
		    {
		      /* Move back: */
		      
		      move_forward = -1;
		    }
		}
	    }
	}
      
      
      /* Turn or move: */
      
      if (turn != 0)
	{
	  dir = dir + turn;
	  
	  if (dir < 0)
	    dir = 3;
	  else if (dir > 3)
	    dir = 0;
	  
	  redraw_screen = 1;
	}
      else if (move_forward != 0)
	{
	  xpos = xpos + (move_forward * xm[dir]);
	  ypos = ypos + (move_forward * ym[dir]);
	  
	  
	  /* Bump into walls: */
	  
	  if (mazechunk(xpos, ypos) == 255)
	    {
	      xpos = oxpos;
	      ypos = oypos;
	      playsound(200, 100);
	    }
	  else
	    {
	      redraw_screen = 1;
	      
	      footstep = !footstep;
	      
	      playsound(1000 + (200 * footstep), 10);
	    }
	}


      /* Keep track of where we've seen: */
      
      seenmaze[ypos - 1][xpos - 1] = 1;
      seenmaze[ypos - 1][xpos + 0] = 1;
      seenmaze[ypos - 1][xpos + 1] = 1;
      
      seenmaze[ypos + 0][xpos - 1] = 1;
      seenmaze[ypos + 0][xpos + 0] = 1;
      seenmaze[ypos + 0][xpos + 1] = 1;
      
      seenmaze[ypos + 1][xpos - 1] = 1;
      seenmaze[ypos + 1][xpos + 0] = 1;
      seenmaze[ypos + 1][xpos + 1] = 1;
      
      
      /* Redraw screen: */
      
      if (redraw_screen)
	{
	  redraw_screen = 0;

	  if (odir == dir)
	    drawscreen(0);
	  else if (((odir + 1) % 4) == dir)
	    drawscreen(1);
	  else
	    drawscreen(-1);
	}
      
      
      /* Handle timer: */

      gettimeofday(&now, NULL);
      
      if (timer_mode == TIMER_MODE_UP)
	timer = now.tv_sec - then.tv_sec;
      else
	timer = ((maze_size * maze_size) / 3) - (now.tv_sec - then.tv_sec);
      
      
      /* Draw timer (always!) */
      
      drawtimer();


      /* Draw your location on the thumbnail: */

      XCopyArea(display, pix_ground, window, whitegc,
	        0, (now.tv_sec % 2) * 70,
		2, 2,
                80 - maze_size + xpos * 2,
                162 + ypos * 2);

      
      
      /* End of game?! */
      
      if (timer < 0)
	{
	  /* Time up - you lose! */
	  
	  XCopyArea(display, pix_timeup, window, whitegc,
		    0, 0, 80, 24, 40, 68);

	  XFlush(display);
      
	  playsound(1000, 200);
	  usleep(20000);
	  
	  playsound(400, 200);
	  usleep(20000);
	  
	  playsound(100, 200);
	  sleep(5);
	  
	  done = 1;
	}
      
      
      if (xpos == 1 && ypos == 2)
	{
	  /* You win! */
	  
	  XCopyArea(display, pix_youwin, window, whitegc,
		    0, 0, 80, 24, 40, 68);

	  XFlush(display);
      
	  playsound(200, 200);
	  usleep(20000);
	  
	  playsound(400, 200);
	  usleep(20000);
	  
	  playsound(800, 200);
	  sleep(5);
	  
	  done = 1;
	}
      
      
      /* Pause: */
      
      usleep(1000);
    }
  while(!done);
}


/* Draw the screen: */

void drawscreen(int scroll)
{
  int x;


  /* Draw the background: */

  /* (Skyline) */

  if (dir == DIR_NORTH)
    drawbkg(pix_bkg_north, 0);
  else if (dir == DIR_EAST) 
    drawbkg(pix_bkg_east, 0);
  else if (dir == DIR_SOUTH) 
    drawbkg(pix_bkg_south, 0);
  else if (dir == DIR_WEST)
    drawbkg(pix_bkg_west, 0);


  /* (Ground) */

  drawbkg(pix_ground, 80);


  /* Draw the farthest walls: */

  if (dir == DIR_NORTH)
  {
    /* Far... */

    /* drawwall(mazechunk(xpos - 3, ypos - 3), FAR, -3);
    drawwall(mazechunk(xpos - 2, ypos - 3), FAR, -2); */
    drawwall(mazechunk(xpos - 1, ypos - 3), FAR, -1);

    /* drawwall(mazechunk(xpos + 3, ypos - 3), FAR, 3);
    drawwall(mazechunk(xpos + 2, ypos - 3), FAR, 2); */
    drawwall(mazechunk(xpos + 1, ypos - 3), FAR, 1);

    drawwall(mazechunk(xpos + 0, ypos - 3), FAR, 0);


    /* Med... */

    /* drawwall(mazechunk(xpos - 3, ypos - 2), MID, -3);
    drawwall(mazechunk(xpos - 2, ypos - 2), MID, -2); */
    drawwall(mazechunk(xpos - 1, ypos - 2), MID, -1);

    /* drawwall(mazechunk(xpos + 3, ypos - 2), MID, 3);
    drawwall(mazechunk(xpos + 2, ypos - 2), MID, 2); */
    drawwall(mazechunk(xpos + 1, ypos - 2), MID, 1);

    drawwall(mazechunk(xpos + 0, ypos - 2), MID, 0);


    /* Close... */

    drawwall(mazechunk(xpos - 1, ypos - 1), CLOSE, -1);
    drawwall(mazechunk(xpos + 1, ypos - 1), CLOSE, 1);
    drawwall(mazechunk(xpos + 0, ypos - 1), CLOSE, 0);
  }
  else if (dir == DIR_EAST)
  {
    /* Far... */

    /* drawwall(mazechunk(xpos + 3, ypos - 3), FAR, -3);
    drawwall(mazechunk(xpos + 3, ypos - 2), FAR, -2); */
    drawwall(mazechunk(xpos + 3, ypos - 1), FAR, -1);

    /* drawwall(mazechunk(xpos + 3, ypos + 3), FAR, 3);
    drawwall(mazechunk(xpos + 3, ypos + 2), FAR, 2); */
    drawwall(mazechunk(xpos + 3, ypos + 1), FAR, 1);

    drawwall(mazechunk(xpos + 3, ypos + 0), FAR, 0);


    /* Med... */

    /* drawwall(mazechunk(xpos + 2, ypos - 3), MID, -3);
    drawwall(mazechunk(xpos + 2, ypos - 2), MID, -2); */
    drawwall(mazechunk(xpos + 2, ypos - 1), MID, -1);

    /* drawwall(mazechunk(xpos + 2, ypos + 3), MID, 3);
    drawwall(mazechunk(xpos + 2, ypos + 2), MID, 2); */
    drawwall(mazechunk(xpos + 2, ypos + 1), MID, 1);

    drawwall(mazechunk(xpos + 2, ypos + 0), MID, 0);


    /* Close... */

    drawwall(mazechunk(xpos + 1, ypos - 1), CLOSE, -1);
    drawwall(mazechunk(xpos + 1, ypos + 1), CLOSE, 1);
    drawwall(mazechunk(xpos + 1, ypos + 0), CLOSE, 0);
  }
  else if (dir == DIR_SOUTH)
  {
    /* Far... */

    /* drawwall(mazechunk(xpos + 3, ypos + 3), FAR, -3);
    drawwall(mazechunk(xpos + 2, ypos + 3), FAR, -2); */
    drawwall(mazechunk(xpos + 1, ypos + 3), FAR, -1);

    /* drawwall(mazechunk(xpos - 3, ypos + 3), FAR, 3);
    drawwall(mazechunk(xpos - 2, ypos + 3), FAR, 2); */
    drawwall(mazechunk(xpos - 1, ypos + 3), FAR, 1);

    drawwall(mazechunk(xpos + 0, ypos + 3), FAR, 0);


    /* Med... */

    /* drawwall(mazechunk(xpos + 3, ypos + 2), MID, -3);
    drawwall(mazechunk(xpos + 2, ypos + 2), MID, -2); */
    drawwall(mazechunk(xpos + 1, ypos + 2), MID, -1);

    /* drawwall(mazechunk(xpos - 3, ypos + 2), MID, 3);
    drawwall(mazechunk(xpos - 2, ypos + 2), MID, 2); */
    drawwall(mazechunk(xpos - 1, ypos + 2), MID, 1);

    drawwall(mazechunk(xpos + 0, ypos + 2), MID, 0);


    /* Close... */

    drawwall(mazechunk(xpos + 1, ypos + 1), CLOSE, -1);
    drawwall(mazechunk(xpos - 1, ypos + 1), CLOSE, 1);
    drawwall(mazechunk(xpos + 0, ypos + 1), CLOSE, 0);
  }
  else if (dir == DIR_WEST)
  {
    /* Far... */

    /* drawwall(mazechunk(xpos - 3, ypos + 3), FAR, -3);
    drawwall(mazechunk(xpos - 3, ypos + 2), FAR, -2); */
    drawwall(mazechunk(xpos - 3, ypos + 1), FAR, -1);

    /* drawwall(mazechunk(xpos - 3, ypos - 3), FAR, 3);
    drawwall(mazechunk(xpos - 3, ypos - 2), FAR, 2); */
    drawwall(mazechunk(xpos - 3, ypos - 1), FAR, 1);

    drawwall(mazechunk(xpos - 3, ypos + 0), FAR, 0);


    /* Med... */

    /* drawwall(mazechunk(xpos - 2, ypos + 3), MID, -3);
    drawwall(mazechunk(xpos - 2, ypos + 2), MID, -2); */
    drawwall(mazechunk(xpos - 2, ypos + 1), MID, -1);

    /* drawwall(mazechunk(xpos - 2, ypos - 3), MID, 3);
    drawwall(mazechunk(xpos - 2, ypos - 2), MID, 2); */
    drawwall(mazechunk(xpos - 2, ypos - 1), MID, 1);

    drawwall(mazechunk(xpos - 2, ypos + 0), MID, 0);


    /* Close... */

    drawwall(mazechunk(xpos - 1, ypos + 1), CLOSE, -1);
    drawwall(mazechunk(xpos - 1, ypos - 1), CLOSE, 1);
    drawwall(mazechunk(xpos - 1, ypos + 0), CLOSE, 0);
  }
  
  
  draw_map();
  draw_compass();


  /* Swap backbuffer: */

  if (scroll == 0)
    {
      swapbuffer();
    }
  else
    {
      XCopyArea(display, window, scrollbuf, whitegc, 0, 0, 160, 240, 0, 0);
      
      if (scroll == 1)
	{
	  for (x = 0; x <= 160; x = x + 20)
	    {
	      XCopyArea(display, scrollbuf, window, whitegc,
			x, 0,
			160 - x, 160,
			0, 0);
	      
	      XCopyArea(display, backbuffer, window, whitegc,
			0, 0,
			x, 160,
			160 - x, 0);
	      
	      XSync(display, 0);

	      usleep(100);
	    }
	}
      else if (scroll == -1)
	{
	  for (x = 0; x <= 160; x = x + 20)
	    { 
	      XCopyArea(display, scrollbuf, window, whitegc,
			0, 0,
			160 - x, 160,
			x, 0);
	      
	      XCopyArea(display, backbuffer, window, whitegc,
			160 - x, 0,
			x, 160,
			0, 0);
	      
	      XSync(display, 0);

	      usleep(100);
	    }
	}
    }
}


void draw_map(void)
{
  int x, y;

  
  /* Draw the thumbnail map of the maze: */

  XDrawRectangle(display, window, blackgc,
		 80 - maze_size - 1, 161,
		 maze_size * 2 + 2, maze_size * 2 + 2);

  /* XFillRectangle(display, window, whitegc,
		 80 - maze_size, 162,
		 maze_size * 2, maze_size * 2); */

  XCopyArea(display, pix_ground, window, whitegc,
	    0, 0, maze_size * 2, maze_size * 2,
	    80 - maze_size, 162);
  
  for (y = 0; y < maze_size; y++)
    {
      for (x = 0; x < maze_size; x++)
	{
	  if (map_mode == MAP_MODE_ALL ||
	      (map_mode == MAP_MODE_BUILD && seenmaze[y][x]))
	    {
              if (maze[y][x] == 255)
	        {
	          XFillRectangle(display, window, blackgc,
		  	         80 - maze_size + x * 2,
			         162 + y * 2,
	  		         2, 2);
  	        }
	      else
	        {
		  XFillRectangle(display, window, whitegc,
				 80 - maze_size + x * 2,
				 162 + y * 2,
				 2, 2);
	        }
	    }
	}
    }
}


void draw_compass(void)
{
  /* Draw the compass: */
  
  XSetClipOrigin(display, pastegc, 0, 172);
  
  if (dir == DIR_NORTH)
    {
      XCopyArea(display, pix_cmp_north, window, pastegc,
		0, 0, 40, 40, 0, 172);
    }
  else if (dir == DIR_SOUTH)
    {
      XCopyArea(display, pix_cmp_south, window, pastegc,
		0, 0, 40, 40, 0, 172);
    }
  else if (dir == DIR_EAST)
    {
      XCopyArea(display, pix_cmp_east, window, pastegc,
		0, 0, 40, 40, 0, 172);
    }
  else if (dir == DIR_WEST)
    {
      XCopyArea(display, pix_cmp_west, window, pastegc,
		0, 0, 40, 40, 0, 172);
    }


  /* Draw the "Done" button: */
  
  XCopyArea(display, pix_done, window, whitegc,
            0, 0, 40, 12, 0, 228);

  
  /* Draw the "Sound" button: */

  if (sound)
    {
      XCopyArea(display, pix_soundon, window, whitegc,
		0, 0, 40, 12, 120, 228);
    }
  else
    {
      XCopyArea(display, pix_soundoff, window, whitegc,
		0, 0, 40, 12, 120, 228);
    }
} 


/* Draw a wall piece: */

void drawwall(int block, int dist, int xoffset)
{
  if (block == 255)
  {
    if (dist == FAR)
    {
      if (xoffset < 0)
      {
        draw_farcenter(80 - 12 + (xoffset * 24));
        draw_farleft(80 - 12 + (xoffset * 24) + 24);
      }
      else if (xoffset == 0)
      {
        draw_farcenter(80 - 12);
      }
      else if (xoffset > 0)
      {
        draw_farcenter(80 - 12 + (xoffset * 24));
        draw_farright(80 - 12 + (xoffset * 24) - 10);
      }
    }
    else if (dist == MID)
    {
      if (xoffset < 0)
      {
        draw_midcenter(80 - 33 - (66 - 24) + (xoffset * 24));
        draw_midleft(80 - 33 - (66 - 24) + (xoffset * 24) + 66);
      }
      else if (xoffset == 0)
      {
        draw_midcenter(80 - 33);
      }
      else if (xoffset > 0)
      {
        draw_midcenter(80 - 33 + (66 - 24) + (xoffset * 24));
        draw_midright(80 - 33 + (66 - 24) + (xoffset * 24) - 21);
      }
    }
    else if (dist == CLOSE)
    {
      if (xoffset < 0)
      {
        draw_closeleft();
      }
      else if (xoffset == 0)
      {
        draw_closecenter();
      }
      else if (xoffset > 0)
      {
        draw_closeright();
      }
    }
  }
}


void draw_farcenter(int xx)
{
  Pixmap pix;
  
  if (dir == DIR_NORTH || dir == DIR_WEST)
    pix = pix_far_center_bright;
  else
    pix = pix_far_center;
  
  XSetClipOrigin(display, pastegc, xx, 80 - 12);
  XCopyArea(display, pix, backbuffer, pastegc,
            0, 0, 24, 24, xx, 80 - 12);
}

void draw_farleft(int xx)
{
  int y;
  Pixmap pix;
  
  if (dir == DIR_NORTH || dir == DIR_EAST)
    pix = pix_far_left_bright;
  else
    pix = pix_far_left;
  
  XSetClipOrigin(display, pastegc, xx, 80 - 12);
  
  for (y = 0; y < 11; y++)
    {
      XCopyArea(display, pix, backbuffer, pastegc,
		0, y,
		y, 1,
		xx, 80 - 12 + y);

      XCopyArea(display, pix, backbuffer, pastegc,
		0, 23 - y,
		y, 1,
		xx, 80 - 12 + 23 - y);
    }
  
  XCopyArea(display, pix, backbuffer, pastegc,
	    0, 11,
	    12, 2,
	    xx, 80 - 12 + 11);
}

void draw_farright(int xx)
{
  Pixmap pix;
  int y;
  
  if (dir == DIR_SOUTH || dir == DIR_WEST)
    pix = pix_far_right_bright;
  else
    pix = pix_far_right;


  for (y = 0; y < 11; y++)
    {
      XSetClipOrigin(display, pastegc, xx + 11 - y, 80 - 12);
      
      XCopyArea(display, pix, backbuffer, pastegc,
		11 - y, y,
		y, 1,
		xx + 11 - y, 80 - 12 + y);
      
      XCopyArea(display, pix, backbuffer, pastegc,
		11 - y, 24 - y,
		y, 1,
		xx + 11 - y, 80 - 12 + 24 - y);
    }
  
  
  XCopyArea(display, pix, backbuffer, pastegc,
	    0, 11,
	    12, 2,
	    xx, 80 - 12 + 11);
}


void draw_midcenter(int xx)
{
  Pixmap pix;
  
  if (dir == DIR_NORTH || dir == DIR_WEST)
    pix = pix_mid_center_bright;
  else
    pix = pix_mid_center;
  
  XSetClipOrigin(display, pastegc, xx, 80 - 33);
  XCopyArea(display, pix, backbuffer, pastegc,
            0, 0, 66, 66, xx, 80 - 33);
}

void draw_midleft(int xx)
{
  int y;
  Pixmap pix;
  
  if (dir == DIR_NORTH || dir == DIR_EAST)
    pix = pix_mid_left_bright;
  else
    pix = pix_mid_left;
  
  
  XSetClipOrigin(display, pastegc, xx, 80 - 33);

  for (y = 0; y < 22; y++)
    {
      XCopyArea(display, pix, backbuffer, pastegc,
		0, y,
		y, 1,
		xx, 80 - 33 + y);

      XCopyArea(display, pix, backbuffer, pastegc,
		0, 66 - y,
		y, 1,
		xx, 80 - 33 + 66 - y);
    }
  
  XCopyArea(display, pix, backbuffer, pastegc,
	    0, 22,
	    24, 25,
	    xx, 80 - 33 + 22);
}

void draw_midright(int xx)
{
  Pixmap pix;
  int y;

  if (dir == DIR_SOUTH || dir == DIR_WEST)
    pix = pix_mid_right_bright;
  else
    pix = pix_mid_right;
  
  for (y = 0; y < 22; y++)
    {
      XSetClipOrigin(display, pastegc, xx + 22 - y, 80 - 33);
      
      XCopyArea(display, pix, backbuffer, pastegc,
		22 - y, y,
		y, 1,
		xx + 22 - y, 80 - 33 + y);
      
      XCopyArea(display, pix, backbuffer, pastegc,
		22 - y, 66 - y,
		y, 1,
		xx + 22 - y, 80 - 33 + 66 - y);
    }
  
  
  XCopyArea(display, pix, backbuffer, pastegc,
	    0, 22,
	    24, 25,
	    xx, 80 - 33 + 22);
}


void draw_closecenter(void)
{
  Pixmap pix;

  if (dir == DIR_NORTH || dir == DIR_WEST)
    pix = pix_close_center_bright;
  else
    pix = pix_close_center;

  XSetClipOrigin(display, pastegc, 0, 0);
  XCopyArea(display, pix, backbuffer, pastegc,
            0, 0, 160, 160, 0, 0);
}

void draw_closeleft(void)
{
  Pixmap pix;
  int y;
  
  if (dir == DIR_NORTH || dir == DIR_EAST)
    pix = pix_close_left_bright;
  else
    pix = pix_close_left;

  
  XSetClipOrigin(display, pastegc, 0, 0);

  for (y = 0; y < 51; y++)
    {
      XCopyArea(display, pix, backbuffer, pastegc,
		0, y,
		y, 1,
		0, y);

      XCopyArea(display, pix, backbuffer, pastegc,
		0, 160 - y,
		y, 1,
		0, 160 - y);
    }
  
  XCopyArea(display, pix, backbuffer, pastegc,
	    0, 51,
	    50, 60,
	    0, 51);
}

void draw_closeright(void)
{
  Pixmap pix;
  int y;
  
  if (dir == DIR_SOUTH || dir == DIR_WEST)
    pix = pix_close_right_bright;
  else
    pix = pix_close_right;

  
  for (y = 0; y < 51; y++)
    {
      XSetClipOrigin(display, pastegc, 160 - y, 0);
  
      XCopyArea(display, pix, backbuffer, pastegc,
		51 - y, y,
		y, 1,
		160 - y, y);
      
      XCopyArea(display, pix, backbuffer, pastegc,
		51 - y, 160 - y,
		y, 1,
		160 - y, 160 - y);
    }
  
  XCopyArea(display, pix, backbuffer, pastegc,
	    0, 51,
	    50, 60,
	    110, 51);
}


/* Draw the background: */

void drawbkg(Pixmap pix, int yy)
{
  XSetClipOrigin(display, pastegc, 0, yy);
  XCopyArea(display, pix, backbuffer, pastegc, 0, 0, 160, 80, 0, yy);
}


/* Set up X and handle images! */

void setup(void)
{
  Window rootwindow;
  XWMHints wmhints;
  int screen, black, white;
  XSetWindowAttributes attr;
  unsigned long attr_mask;
  struct timeval tp;
  char wname[64];

  
  /* Default settings: */
  
  timer_mode = TIMER_MODE_UP;
  map_mode = MAP_MODE_BUILD;
  maze_size = 19;
  sound = 1;
  
  
  /* Seed random number generator: */

  gettimeofday(&tp, NULL);
  srand(tp.tv_sec + tp.tv_usec);
  
  
  /* Connect to X server: */
  
  display = XOpenDisplay(NULL);
  if (display == NULL)
    {
      fprintf(stderr, "Can't connect to display!\n");
      exit(1);
    }
  
  screen = DefaultScreen(display);
  rootwindow = RootWindow(display, screen);
  
  
  /* Get primitive colors: */
  
  black = BlackPixel(display, screen);
  white = WhitePixel(display, screen);

  
  /* Get keyboard state (so we can put beep values back!) */
  
  XGetKeyboardControl(display, &kbstate);
  
  
  /* Open window: */
  
  attr.event_mask = (KeyPressMask | ButtonPressMask |
                     ButtonReleaseMask |
                     ExposureMask | VisibilityChangeMask);

  attr.border_pixel = black;
  attr.background_pixel = white;
  attr_mask = CWEventMask | CWBackPixel | CWBorderPixel;
  
  window = XCreateWindow(display, rootwindow, 0, 0, 160, 240, 0,
                         DefaultDepthOfScreen(DefaultScreenOfDisplay(display)),
                         InputOutput, DefaultVisual(display, screen),
                         attr_mask, &attr);

  
  /* Set input hints (so we appear in the window lists).
     Need to do this because of a bug in VRSM.  Not bad to do anyway, tho */

  wmhints.input = True;
  wmhints.flags |= InputHint;
  XSetWMHints(display, window, &wmhints);

  sprintf(wname, "PDA Maze");
  XChangeProperty(display, window, XA_WM_NAME, XA_STRING, 8,
		  PropModeReplace, wname, strlen(wname));
  

  /* Create primitive graphics contexts: */

  whitegc = CreateGC(display, window, white, black);
  blackgc = CreateGC(display, window, black, black);

  pastegc = CreateGC(display, window, white, black);


  /* Create backbuffer: */

  backbuffer = XCreatePixmap(display, window, 160, 160,
                 DefaultDepthOfScreen(DefaultScreenOfDisplay(display)));

  scrollbuf = XCreatePixmap(display, window, 160, 160,
                DefaultDepthOfScreen(DefaultScreenOfDisplay(display)));


  pix_loading = -1;
  LoadImage(loading_xpm, &pix_loading, 0);


  /* Bring window up! */

  XMapWindow(display, window);
  XMapRaised(display, window);
  XSync(display, 0);


  /* Create images: */

  /* (Status stuff) */

  LoadImage(title_xpm, &pix_title, 3);
  LoadImage(done_xpm, &pix_done, 5);
  LoadImage(start_xpm, &pix_start, 8);
  LoadImage(numbers_xpm, &pix_numbers, 10);

  LoadImage(soundon_xpm, &pix_soundon, 13);
  LoadImage(soundoff_xpm, &pix_soundoff, 15);

  LoadImage(options_xpm, &pix_options, 18);
  LoadImage(optionson_xpm, &pix_optionson, 20);

  LoadImage(timeup_xpm, &pix_timeup, 23);
  LoadImage(youwin_xpm, &pix_youwin, 25);

  LoadImage(cmp_north_xpm, &pix_cmp_north, 28);
  LoadImage(cmp_south_xpm, &pix_cmp_south, 30);
  LoadImage(cmp_east_xpm, &pix_cmp_east, 33);
  LoadImage(cmp_west_xpm, &pix_cmp_west, 35);


  /* (Background stuff) */

  LoadImage(ground_xpm, &pix_ground, 38);
  LoadImage(bkg_north_xpm, &pix_bkg_north, 40);
  LoadImage(bkg_south_xpm, &pix_bkg_south, 43);
  LoadImage(bkg_east_xpm, &pix_bkg_east, 45);
  LoadImage(bkg_west_xpm, &pix_bkg_west, 48);


  /* (Walls) */

  LoadImage(close_left_xpm, &pix_close_left, 50);
  LoadImage(close_center_xpm, &pix_close_center, 53);
  LoadImage(close_right_xpm, &pix_close_right, 55);

  LoadImage(middle_left_xpm, &pix_mid_left, 58);
  LoadImage(middle_center_xpm, &pix_mid_center, 60);
  LoadImage(middle_right_xpm, &pix_mid_right, 63);

  LoadImage(far_left_xpm, &pix_far_left, 65);
  LoadImage(far_center_xpm, &pix_far_center, 68);
  LoadImage(far_right_xpm, &pix_far_right, 70);

  
  /* (Bright walls) */
  
  LoadImage(close_left_bright_xpm, &pix_close_left_bright, 73);
  LoadImage(close_center_bright_xpm, &pix_close_center_bright, 75);
  LoadImage(close_right_bright_xpm, &pix_close_right_bright, 78);

  LoadImage(middle_left_bright_xpm, &pix_mid_left_bright, 80);
  LoadImage(middle_center_bright_xpm, &pix_mid_center_bright, 83);
  LoadImage(middle_right_bright_xpm, &pix_mid_right_bright, 85);

  LoadImage(far_left_bright_xpm, &pix_far_left_bright, 88);
  LoadImage(far_center_bright_xpm, &pix_far_center_bright, 90);
  LoadImage(far_right_bright_xpm, &pix_far_right_bright, 95);


  /* Bring window up! */
  
  XSync(display, 0);
}


/* Create a graphics context: */

GC CreateGC(Display *display, Drawable drawable, unsigned long forecolor,
            unsigned long backcolor)
{
  XGCValues xgcvalues;
  GC gc;
  
  xgcvalues.foreground = forecolor;
  xgcvalues.background = backcolor;
  gc = XCreateGC(display,drawable,(GCForeground | GCBackground),
                 &xgcvalues);
  
  return(gc);
}



/* Load an image from XPM data: */

void LoadImage(char ** xpm, Pixmap * pix, int percent)
{
  XpmCreatePixmapFromData(display, window, xpm, pix, NULL, NULL);

  if (pix_loading != -1)
  {
    XCopyArea(display, pix_loading, window, whitegc,
              0, 0, 160, 25, 0, 107);
    XFillRectangle(display, window, blackgc,
		   0, 132, (percent * 160) / 100, 10);
    XFlush(display);
  }
}


int mazechunk(int xx, int yy)
{
  if (xx > 0 && yy > 0 &&
      xx < maze_size - 1 && yy < maze_size - 1)
  {
    return(maze[yy][xx]);
  }
  else
  {
    return -1;
  }
}


/* Swap the buffer into the window! */

void swapbuffer(void)
{
  XCopyArea(display, backbuffer, window, whitegc, 0, 0, 160, 160, 0, 0);
  XFlush(display);
}


/* Create a maze randomly: */

void create_maze(int size)
{
  int x, y, ok, xx, nx, ny, j;
  
  
  /* Create 100% wall: */
  
  for (y = 1; y < maze_size - 1; y++)
    {
      maze[y][0] = -1;
      for (x = 1; x < maze_size - 1; x++)
	{
	  maze[y][x] = 255;
	}
      maze[y][maze_size - 1] = -1;
    }

  for (x = 0; x < maze_size; x++)
    {
      maze[0][x] = -1;
      maze[maze_size - 1][x] = -1;
    }
 
  
  y = 2;
  x = 2;
  
  xx = 0;
  j = 0;
  
  maze[y][x] = 5;
  
  ok = 2;
  
  do
    {
      if (ok == 2)
	{
	  j = (rand() % 4);
	  xx = j;
	}
      
      ok = 0;
      
      nx = x + xm[j] * 2;
      ny = y + ym[j] * 2;
      
      if (mazechunk(nx, ny) == 255)
	{
	  maze[ny][nx] = j + 1;
	  maze[y + ym[j]][x + xm[j]] = 0;
	  
	  x = nx;
	  y = ny;
	  
	  ok = 2;
	}
      
      if (ok == 0)
	{
	  if (j < 3)
	    {
	      j = j + 1;
	      
	      while (j > 3)
		j = j - 4;
	    }
	  else
	    j = 0;
	  
	  
	  if (j != xx)
	    ok = 1;
	}
      
      
      if (ok == 0)
	{
	  j = mazechunk(x, y);
	  maze[y][x] = 0;
	  
	  if (j < 5)
	    {
	      x = x - (xm[j - 1] * 2);
	      y = y - (ym[j - 1] * 2);
	      
	      ok = 2;
	    }
	}
    }
  while (ok != 0);


  /* Create seen-maze map: */

  for (x = 0; x < maze_size; x++)
  {
    seenmaze[0][x] = 1;
    seenmaze[1][x] = 1;

    seenmaze[maze_size - 2][x] = 1;
    seenmaze[maze_size - 1][x] = 1;
  }

  for (y = 2; y < maze_size - 2; y++)
  {
    seenmaze[y][0] = 1;
    seenmaze[y][1] = 1;

    seenmaze[y][maze_size - 2] = 1;
    seenmaze[y][maze_size - 1] = 1;
    
    for (x = 2; x < maze_size - 2; x++)
    {
      seenmaze[y][x] = 0;
    }
  }


  /* Create exit */
  
  maze[2][1] = 0;
}


/* Play a sound: */

void playsound(int pitch, int duration)
{
  XKeyboardControl vals;
  
  if (sound)
    {
      vals.bell_pitch = pitch;
      vals.bell_duration = duration;
      vals.bell_percent = 100;
      
      XChangeKeyboardControl(display,
                             (KBBellPitch | KBBellDuration | KBBellPercent),
                             &vals);
      XBell(display, 100);
      XFlush(display);
    }
}


void drawtimer(void)
{
  char str[10];
  int i;
  
  sprintf(str, "%.2d:%.2d", timer / 60, timer % 60);
  
  for (i = 0; i < strlen(str); i++)
    {
      if (str[i] >= '0' && str[i] <= ':')
	{
	  XSetClipOrigin(display, pastegc, 118 + i * 8, 186);
	  XCopyArea(display, pix_numbers, window, pastegc,
		    (str[i] - '0') * 8, 0,
		    8, 12,
		    118 + i * 8, 186);
	}
    }
}


void finish(void)
{
  XKeyboardControl vals;


  /* Return display's beel pitch/duration to normal! */

  vals.bell_pitch = kbstate.bell_pitch;
  vals.bell_duration = kbstate.bell_duration;

  XChangeKeyboardControl(display, KBBellPitch | KBBellDuration, &vals);
  XFlush(display);
}
