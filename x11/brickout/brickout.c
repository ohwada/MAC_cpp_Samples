// change log
// 2022-06-01 K.OHWADA
//  IMAGEDIR to images

/*
  brickout.c
  
  A break-the-bricks style game for X11 or SDL, originally made for the
  Agenda VR3 Linux- and X-Window-based PDA, but also ported to the
  Sharp Zaurus SL-5500 Linux- and Qtopia-based PDA (using SDL).
  
  by Bill Kendrick
  bill@newbreedsoftware.com
  http://www.newbreedsoftware.com/brickout/

  With contributions from Tom Satter
  tsatter@purecode.com

  May 17, 2001 - June 9, 2002
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef USE_SDL

#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#define XBUTTON xbutton
#define SDL_X_OFF 0
#define SDL_Y_OFF 0

#else

#include "SDL.h"
#include "SDL_mixer.h"

typedef SDL_Surface * Window;
typedef SDL_Surface * Pixmap;
typedef SDL_Surface * Drawable;
typedef int Display;
typedef Uint32 GC;
typedef SDL_Event XEvent;
typedef SDLKey KeySym;

#define XBUTTON button

#define ButtonPress SDL_MOUSEBUTTONDOWN
#define MotionNotify SDL_MOUSEMOTION
#define KeyPress SDL_KEYDOWN
#define KeyRelease SDL_KEYUP

#define XK_Left SDLK_LEFT
#define XK_Right SDLK_RIGHT
#define XK_Page_Up SDLK_UNKNOWN
#define XK_Page_Down SDLK_UNKNOWN
#define XK_space SDLK_SPACE
#define XK_Escape SDLK_ESCAPE

#define SDL_X_OFF 40
#define SDL_Y_OFF 40

#endif

#include <unistd.h>
#include <sys/time.h>

#ifndef USE_SDL

#include "images/ball.xpm"
#include "images/brick1.xpm"
#include "images/brick2.xpm"
#include "images/brick3.xpm"
#include "images/brick4.xpm"
#include "images/brick5.xpm"
#include "images/conton.xpm"
#include "images/contoff.xpm"
#include "images/done.xpm"
#include "images/launchoff.xpm"
#include "images/launchon.xpm"
#include "images/leftpipe.xpm"
#include "images/numbers.xpm"
#include "images/paddle.xpm"
#include "images/pause.xpm"
#include "images/soundoff.xpm"
#include "images/soundon.xpm"
#include "images/negoff.xpm"
#include "images/negon.xpm"
#include "images/posoff.xpm"
#include "images/poson.xpm"
#include "images/start.xpm"
#include "images/stats.xpm"
#include "images/stats_leftpipe.xpm"
#include "images/stats_rightpipe.xpm"
#include "images/stats_toppipe.xpm"
#include "images/title.xpm"
#include "images/water.xpm"

#else

const char
  * ball_xpm = "images/ball.bmp",
  * brick1_xpm = "images/brick1.bmp",
  * brick2_xpm = "images/brick2.bmp",
  * brick3_xpm = "images/brick3.bmp",
  * brick4_xpm = "images/brick4.bmp",
  * brick5_xpm = "images/brick5.bmp",
  * conton_xpm = "images/conton.bmp",
  * contoff_xpm = "images/contoff.bmp",
  * done_xpm = "images/done.bmp",
  * launchoff_xpm = "images/launchoff.bmp",
  * launchon_xpm = "images/launchon.bmp",
  * leftpipe_xpm = "images/leftpipe.bmp",
  * numbers_xpm = "images/numbers.bmp",
  * paddle_xpm = "images/paddle.bmp",
  * pause_xpm = "images/pause.bmp",
  * soundoff_xpm = "images/soundoff.bmp",
  * soundon_xpm = "images/soundon.bmp",
  * musicoff_xpm = "images/musicoff.bmp",
  * musicon_xpm = "images/musicon.bmp",
  * negoff_xpm = "images/negoff.bmp",
  * negon_xpm = "images/negon.bmp",
  * posoff_xpm = "images/posoff.bmp",
  * poson_xpm = "images/poson.bmp",
  * start_xpm = "images/start.bmp",
  * stats_xpm = "images/stats.bmp",
  * stats_leftpipe_xpm = "images/stats_leftpipe.bmp",
  * stats_rightpipe_xpm = "images/stats_rightpipe.bmp",
  * stats_toppipe_xpm = "images/stats_toppipe.bmp",
  * title_xpm = "images/title.bmp",
  * water_xpm = "images/water.bmp";

#endif


/* Globals: */

Display *display;
Window window;
GC whitegc, blackgc, pastegc;

Pixmap pix_title, pix_leftpipe;
Pixmap pix_stats, pix_stats_toppipe, pix_stats_leftpipe;
Pixmap pix_stats_rightpipe, pix_water;
Pixmap pix_brick1, pix_brick2, pix_brick3, pix_brick4, pix_brick5;
Pixmap pix_done, pix_start, pix_soundon, pix_soundoff, pix_conton, pix_contoff,
  pix_negon, pix_negoff, pix_poson, pix_posoff;
Pixmap pix_pause, pix_launchon, pix_launchoff, pix_numbers;
Pixmap pix_ball, pix_paddle;

#ifdef USE_SDL
Pixmap pix_musicon, pix_musicoff;
#endif

int score, balls, level, paddle_x, paddle_target_x;
int ball_launched, ball_bx, ball_by;
int dir_x, dir_y, brake, slope;
int redraw_brick_x, redraw_brick_y;

char cur_board[6][10];
int num_bricks_left;


#ifdef USE_SDL

typedef struct breaking_brick_type {
  int time;
  char kind;
} breaking_brick_type;

breaking_brick_type breaking_bricks[6][10];



#define NUM_GAME_MUSICS 6

char * music_fnames[NUM_GAME_MUSICS] = {
  MUSICDIR "yawny.mod",
  MUSICDIR "Bootmusic_9.mod",
  MUSICDIR "Dj_bobo_die.mod",
  MUSICDIR "Pleasure_to_paso.mod",
  MUSICDIR "invasion.mod",
  MUSICDIR "Valley_of_chip_6.mod"
};

int use_sound;
Mix_Chunk * snd_wall, * snd_ceiling, * snd_metal, * snd_brick,
	* snd_unbreakable, * snd_paddle, * snd_die;
Mix_Music * mus_title, * mus_game[NUM_GAME_MUSICS];

#endif



int sound, game_pending;

#ifdef USE_SDL
int music;
#endif

int slopes_x[7] = {
     0,
   392,
   800,
  1144,
  1448,
  1720,
  1896
};

int slopes_y[7] = {
  2048,
  2008,
  1888,
  1696,
  1448,
  1112,
   768
};

/* Valid symbols:
   "-" - Regular brick
   "=" - Shiny, two-hit brick
   "/" - Gradient brick
   "#" - Bevelled brick
   ":" - Indestructable rivetted brick
*/

#define NUM_LEVELS 20

char boards[NUM_LEVELS][6][10] = {
  {
    /* Level 1 */
    "          ",
    "----------",
    "----------",
    "----------",
    "          ",
    "          "
  },
  {
    /* Level 2 */
    "----------",
    "----------",
    "----------",
    "----------",
    "==========",
    "::------::"
  },
  {
    /* Level 3 */
    "----------",
    "----------",
    "---::::---",
    "---::::---",
    "----------",
    "=========="
  },
  {
    /* Level 4 */
    "==========",
    "  ::::::  ",
    "----------",
    "  ::--::  ",
    "----------",
    "  --::--  "
  },
  { /* Level 5 */
    "=-/####/-=",
    "-=-/##/-=-",
    "/-=-//-=-/",
    " /-=--=-/ ",
    "  /-==-/  ",
    "   /--/   "
  },
  { /* Level 6 */
    "##########",
    "==========",
    "##########",
    "          ",
    "::::  ::::",
    "::      ::"
  },
  { /* Level 7 */
    "#/#/#/#/#/",
    "/#/#/#/#/#",
    "#/#/#/#/#/",
    "/#/#/#/#/#",
    "          ",
    "          "
  },
  { /* Level 8 */
    "  /####/  ",
    " /##//##/ ",
    " //####// ",
    " /##//##/ ",
    "  /####/  ",
    "          "
  },
  { /* Level 9 */
    "//////////",
    "  //////  ",
    "   ----   ",
    "##:    :##",
    "#:      :#",
    ":        :"
  },
  { /* Level 10 */
    "          ",
    " // // // ",
    "=-=-=-=-=-",
    "-=-=-=-=-=",
    "          ",
    "==--==--=="
  },
  { /* Level 11 */
    "::      ::",
    "          ",
    "  ::::::  ",
    "          ",
    "=        =",
    "::: :: :::"
  },
  { /* Level 12 */
    "          ",
    "//////////",
    "####::####",
    "==========",
    "          ",
    " -- -- -- "
  },
  { /* Level 13 */
    "   ####   ",
    "    ==##  ",
    "      =## ",
    "      =## ",
    "    ==##  ",
    "   ####   "
  },
  { /* Level 14 */
    "::::::::::",
    "::======::",
    ":========:",
    ":===  ===:",
    ":==    ==:",
    "::= == =::"
  },
  { /* Level 15 */
    "/########/",
    "##########",
    "#=      =#",
    "#=      =#",
    "##======##",
    "/########/"
  },
  { /* Level 16 */
    "  =    =  ",
    "   =  =   ",
    ":   ##   :",
    ":   ##   :",
    "   =  =   ",
    "  =    =  "
  },
  { /* Level 17 */
    "    ==    ",
    "  ==--==  ",
    "==--//--==",
    "--//##//--",
    "//##  ##//",
    "##      ##"
  },
  { /* Level 18 */
    "          ",
    "   ====   ",
    "  ######  ",
    "    ==    ",
    " =      = ",
    " =      = "
  },
  { /* Level 19 */
    ":########:",
    ":########:",
    "///:==:///",
    "///:==:///",
    ":--------:",
    ":--------:"
  },
  { /* Level 20 */
    "//////////",
    "==========",
    "##########",
    "          ",
    "          ",
    ": :::::: :"
  }
};


/* Local function prototypes: */

void setup(void);
void loadsettings(void);
int title(void);
void draw_titlescreen(void);
void game(void);
void draw_gamescreen(void);
#ifndef USE_SDL
GC CreateGC(Display *display, Drawable drawable, unsigned long forecolor,
            unsigned long backcolor);
void LoadImage(char ** xpm, Pixmap * pix);
#else
Pixmap LoadImage(const char * file);
#endif
void DrawImage(Pixmap pix, Drawable dest, int x, int y, int w, int h);
void DrawNumbers(char * str, int x, int y);
#ifndef USE_SDL
void playsound(int pitch, int duration);
#else
void playsound(Mix_Chunk * snd);
#endif
void launch_ball(void);
void add_score(int val);
void draw_brick(int x, int y);
void reset_level(void);
int  hit_brick(int x,int y);
#ifdef USE_SDL
Mix_Chunk * LoadSound(char * fname);
#endif


/* --- MAIN! --- */

int main(int argc, char * argv[])
{
  int done;
  
  
  setup();
  
  loadsettings();
 
  level = 1; 
  do
    {
      done = title();
      
      if (!done)
	game();
    }
  while (!done);

#ifdef USE_SDL
  SDL_Quit();
#endif
  
  return(0);
}


/* Title: */

int title(void)
{
  int done, quit, want_level_chg, bx, by;
  XEvent event;
  KeySym key;
  char str[24];
#ifdef USE_SDL
  Uint32 last_tick, cur_tick;
#endif
  
  
  draw_titlescreen();
  
  
  /* Title loop: */
  
  done = 0;
  quit = 0;
  
#ifdef USE_SDL
  last_tick = SDL_GetTicks();
#endif

      
  do
    {
      want_level_chg = 0;

#ifndef USE_SDL
      while (XPending(display))
	{
	  XNextEvent(display, &event);
#else
      while (SDL_PollEvent(&event) > 0)
	{
#endif
	  
	  if (event.type == ButtonPress)
	    {
	      bx = event.XBUTTON.x - SDL_X_OFF;
	      by = event.XBUTTON.y - SDL_Y_OFF;

	      if (bx >= 64 &&
		  bx <= 96 &&
		  by >= 170 &&
		  by <= 183)
		{
		  /* Start! */
		  
		  game_pending = 0;
		  done = 1;
		}
	      else if (bx >= 64 &&
		  bx <= 96 &&
		  by >= 190 &&
		  by <= 203 &&
		  game_pending == 1)
		{
		  /* Continue! */
		  
		  done = 1;
		}
	      else if (bx >= 14 &&
		  bx <= 46 &&
		  by >= 225 &&
		  by <= 238)
		{
		  /* Done button! */
		  
		  done = 1;
		  quit = 1;
		}
	      else if (bx >= 126 &&
		       bx <= 144 &&
		       by >= 225 &&
		       by <= 238)
		{
		  /* Sound control! */
		  
		  sound = !sound;
		  
		  if (sound == 1)
		    DrawImage(pix_soundon, window, 126, 225, 18, 13);
		  else
		    DrawImage(pix_soundoff, window, 126, 225, 18, 13);
		 
#ifndef USE_SDL 
		  XFlush(display);
#endif
		}
#ifdef USE_SDL
	      else if (bx >= 100 &&
		       bx <= 118 &&
		       by >= 225 &&
		       by <= 238)
		{
		  /* Music control! */
		  
		  music = !music;
		  
		  if (music == 1)
		    DrawImage(pix_musicon, window, 100, 225, 18, 13);
		  else
		  {
		    DrawImage(pix_musicoff, window, 100, 225, 18, 13);
		    Mix_HaltMusic();
		  }
		}
#endif
	      else if (bx >= 60 &&
		       bx <= 76 &&
		       by >= 144 &&
		       by <= 157)
	        {
		  /* Negative button: */

	          want_level_chg = -1;
	        }
	      else if (bx >= 98 &&
		       bx <= 114 &&
		       by >= 144 &&
		       by <= 157)
	        {
		  /* Positive button: */

		  want_level_chg = 1;
	        }
	    }
	  else if (event.type == KeyPress)
            {
#ifndef USE_SDL
	      key = XLookupKeysym((XKeyEvent *)&event, 0);
#else
	      key = event.key.keysym.sym;
#endif

	      if (key == XK_Left)
		want_level_chg = -1;
	      else if (key == XK_Right)
		want_level_chg = 1;
	      else if (key == XK_space)
		done = 1;
	      else if (key == XK_Escape)
	      {
		quit = 1;
		done = 1;
	      }
	    }
#ifndef USE_SDL
	  else if (event.type == Expose)
	    {
	      draw_titlescreen();
	    }
#endif
	}


      if (want_level_chg == -1 && level > 1)
      {
        level--;

        sprintf(str, "%.2d", level);
        DrawNumbers(str, 79, 141);

        if (level == 1)
          DrawImage(pix_negoff, window, 60, 144, 16, 13);

        if (level < NUM_LEVELS)
          DrawImage(pix_poson, window, 98, 144, 16, 13);

        game_pending = 0;
        DrawImage(pix_contoff, window, 64, 190, 32, 13);

#ifdef USE_SDL
	playsound(snd_wall);
#endif
      }
      else if (want_level_chg == 1 && level < NUM_LEVELS)
      {
        level++;

        sprintf(str, "%.2d", level);
        DrawNumbers(str, 79, 141);

        if (level == NUM_LEVELS)
          DrawImage(pix_posoff, window, 98, 144, 16, 13);

        if (level > 1)
          DrawImage(pix_negon, window, 60, 144, 16, 13);

        game_pending = 0;
        DrawImage(pix_contoff, window, 64, 190, 32, 13);

#ifdef USE_SDL
	playsound(snd_paddle);
#endif
      }


#ifdef USE_SDL
      if (use_sound && music)
      {
	if (!Mix_PlayingMusic())
	{
	  Mix_PlayMusic(mus_title, -1);
	}
      }
#endif


#ifdef USE_SDL
      cur_tick = SDL_GetTicks();

      if (cur_tick > last_tick + 100)
      {
        SDL_Flip(window);
	last_tick = cur_tick;
      }
#endif
    }
  while (done == 0);
 
#ifdef USE_SDL

  if (use_sound)
  {
    Mix_HaltMusic();
  }
      
  if (quit)
  {
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 128));
    SDL_Flip(window);
    playsound(snd_die);
    SDL_Delay(1000);
  }
#endif
      
  return(quit);
}



/* Draw title screen: */

void draw_titlescreen(void)
{
  int y;
  char str[20];

  /* (Title) */
 
#ifndef USE_SDL 
  XFillRectangle(display, window, blackgc, 0, 0, 160, 240);
#else
  SDL_FillRect(window, NULL, blackgc);
#endif
  
  DrawImage(pix_title, window, 0, 0, 160, 100);
  for (y = 100; y < 240; y = y + 10)
    {
      DrawImage(pix_leftpipe, window, 0, y, 14, 10);
    }


  /* (Level buttons) */

  if (level == 1)
    DrawImage(pix_negoff, window, 60, 144, 16, 13);
  else
    DrawImage(pix_negon, window, 60, 144, 16, 13);

  sprintf(str, "%.2d", level);
  DrawNumbers(str, 79, 141);

  if (level < NUM_LEVELS)
    DrawImage(pix_poson, window, 98, 144, 16, 13);
  else
    DrawImage(pix_posoff, window, 98, 144, 16, 13);
  

  /* (Done button) */
  
  DrawImage(pix_done, window, 14, 225, 32, 13);
  
  
  /* (Sound control button) */
  
  if (sound == 1)
    DrawImage(pix_soundon, window, 126, 225, 18, 13);
  else
    DrawImage(pix_soundoff, window, 126, 225, 18, 13);


#ifdef USE_SDL
  /* (Music control button) */
  
  if (music == 1)
    DrawImage(pix_musicon, window, 100, 225, 18, 13);
  else
    DrawImage(pix_musicoff, window, 100, 225, 18, 13);
#endif


  /* (Start button) */
  
  DrawImage(pix_start, window, 64, 170, 32, 13);
  

  /* (Continue button) */
  
  if (game_pending == 1)
    DrawImage(pix_conton, window, 64, 190, 32, 13);
  else
    DrawImage(pix_contoff, window, 64, 190, 32, 13);
  

#ifndef USE_SDL
  XFlush(display);
#endif
}


/* GAME FUNCTION! */

void game(void)
{
  XEvent event;
  KeySym key;
  int done, counter;
  int x, y, i;
  int ball_x, ball_y, mx, my, hit;
  int left_down, right_down, bx, by;
  char brick;
  struct timeval now, then;
  long time_padding;
#ifdef USE_SDL
  SDL_Rect dest;
#endif
  

  /* Set up game: */
  
  if (!game_pending)
    {
      score = 0;
      balls = 5;
      paddle_x = 64;
      paddle_target_x = 64;
      
      for (y = 0; y < 6; y++)
      {
	for (x = 0; x < 10; x++)
	{
	  cur_board[y][x] = ' ';
	}
      }

      reset_level();

      ball_launched  = 0;
      ball_bx        = 4864;
      ball_by        = 7424;
      brake          = 8;
      slope          = 1;
      dir_x          = 0;
      dir_y          = 0;
      redraw_brick_x = -1;
      game_pending   = 1;
    }
  
  
  /* Draw the game screen: */

  draw_gamescreen();

  done = 0;
  left_down = 0;
  right_down = 0;
  counter = 0;
 
  ball_x = ball_bx >> 6;
  ball_y = ball_by >> 6;
  do
    {
      gettimeofday(&then, NULL);
      counter++;

      /* Erase paddle: */

#ifndef USE_SDL
      XFillRectangle(display, window, whitegc, paddle_x, 150, 32, 10);
#else
      dest.x = paddle_x + SDL_X_OFF;
      dest.y = 150 + SDL_Y_OFF;
      dest.w = 32;
      dest.h = 10;

      SDL_FillRect(window, &dest, whitegc);
#endif
      
      
      /* Erase ball: */

#ifndef USE_SDL
      XFillRectangle(display, window, whitegc, ball_x, ball_y, 8, 8);
#else
      dest.x = ball_x + SDL_X_OFF;
      dest.y = ball_y + SDL_Y_OFF;
      dest.w = 8;
      dest.h = 8;

      SDL_FillRect(window, &dest, whitegc);
#endif
      
      if (redraw_brick_x >= 0)
        {
          draw_brick(redraw_brick_x, redraw_brick_y);
          redraw_brick_x = -1;
        }
      
      /* Handle events: */

#ifndef USE_SDL
      while (XPending(display))
	{
	  XNextEvent(display, &event);
#else
      while (SDL_PollEvent(&event) > 0)
	{
#endif
	 
	  if (event.type == ButtonPress)
	    {
	      bx = event.XBUTTON.x - SDL_X_OFF;
	      by = event.XBUTTON.y - SDL_Y_OFF;

	      if (bx >= 14 &&
		  bx <= 46 &&
		  by >= 225 &&
		  by <= 238)
		{
		  /* Pause button! */
		  
		  done = 1;
		}
	      else if (bx >= 64 &&
		       bx <= 96 &&
		       by >= 225 &&
		       by <= 238)
		{
		  /* Ball launcher button! */

		  if (ball_launched == 0)
		    launch_ball();
		}
	      else if (bx >= 126 &&
		       bx <= 144 &&
		       by >= 225 &&
		       by <= 238)
		{
		  /* Sound control! */
		  
		  sound = !sound;
		  
		  if (sound == 1)
		    DrawImage(pix_soundon, window, 126, 225, 18, 13);
		  else
		    DrawImage(pix_soundoff, window, 126, 225, 18, 13);
		  
#ifndef USE_SDL
		  XFlush(display);
#endif
		}
#ifdef USE_SDL
	      else if (bx >= 100 &&
		       bx <= 118 &&
		       by >= 225 &&
		       by <= 238)
		{
		  /* Music control! */
		  
		  music = !music;
		  
		  if (music == 1)
		    DrawImage(pix_musicon, window, 100, 225, 18, 13);
		  else
		  {
		    DrawImage(pix_musicoff, window, 100, 225, 18, 13);
		    Mix_HaltMusic();
		  }
		}
#endif
	      else if (by < 160)
		{
		  /* Tap screen elsewhere - move paddle! */
		  paddle_target_x = bx - 16;

		  if (paddle_target_x < -16)
		    paddle_target_x = -16;
		  else if (paddle_target_x > 144)
		    paddle_target_x = 144;
		}
	    }
	  else if (event.type == MotionNotify)
            {
	      bx = event.XBUTTON.x - SDL_X_OFF;
	      by = event.XBUTTON.y - SDL_Y_OFF;

	      /* Move stylus - move paddle? */
              paddle_target_x = bx - 16;

              if (paddle_target_x < -16)
                paddle_target_x = -16;
              else if (paddle_target_x > 144)
                paddle_target_x = 144;
            }
	  else if (event.type == KeyPress)
	    {
#ifndef USE_SDL
	      /* Key press! */
	      
	      key = XLookupKeysym((XKeyEvent *)&event, 0);
#else
	      key = event.key.keysym.sym;
#endif
	      
	      if (key == XK_Left)
		{
		  /* Left */
		  
		  left_down = 1;
		  right_down = 0;
		}
	      else if (key == XK_Right)
		{
		  /* Right */
		  
		  left_down = 0;
		  right_down = 1;
		}
	      else if (key == XK_Page_Up || key == XK_Page_Down ||
		       key == XK_space)
		{
		  /* PageUp/PageDown */
		  
		  if (ball_launched == 0)
		    launch_ball();
		}
	      else if (key == XK_Escape)
		{
		  done = 1;
		}
	    }
	  else if (event.type == KeyRelease)
	    {
#ifndef USE_SDL
	      /* Key release! */
	      
	      key = XLookupKeysym((XKeyEvent *)&event, 0);
#else
	      key = event.key.keysym.sym;
#endif
	      
	      if (key == XK_Left)
		{
		  left_down = 0;
		}
	      else if (key == XK_Right)
		{
		  right_down = 0;
		}
	    }
#ifndef USE_SDL	
	  else if (event.type == Expose)
	    {
	      draw_gamescreen();
	    }
#endif
	}
      

      /* Move paddle based on keypresses: */
      
      if (left_down)
	{
	  paddle_x = paddle_x - 4;
	  if (paddle_x < -16)
	    paddle_x = -16;
          paddle_target_x = paddle_x;
	}
      else if (right_down)
	{
	  paddle_x = paddle_x + 4;
	  if (paddle_x > 144)
	    paddle_x = 144;
          paddle_target_x = paddle_x;
	}

      if (paddle_target_x > paddle_x)
        {
          if (paddle_target_x > paddle_x + 4)
            paddle_x += 4;
          else
            paddle_x = paddle_target_x;
        }
      else if (paddle_target_x < paddle_x)
        {
          if (paddle_target_x < paddle_x - 4)
            paddle_x -= 4;
          else
            paddle_x = paddle_target_x;
        }
      
      /* Control ball: */
      
      if (ball_launched)
	{
          /* Move the ball: */

          ball_bx += dir_x * (slopes_x[slope] / (brake + 8));
          ball_by += dir_y * (slopes_y[slope] / (brake + 8));
          ball_x   = ball_bx >> 6;
          ball_y   = ball_by >> 6;
      
          /* Bounce off sides: */
      
          if (ball_x < 0)
            {
              ball_x = 0;
              dir_x = 1;
         
#ifndef USE_SDL
              playsound(500, 10);
#else
	      playsound(snd_wall);
#endif
            }
          else if (ball_x > 152)
            {
              ball_x = 152;
              dir_x = -1;

#ifndef USE_SDL
              playsound(500, 10);
#else
	      playsound(snd_wall);
#endif
            }
	  
	  /* Bounce off top of screen: */

	  if (ball_y < 0)
	    {
	      ball_y = 0;
	      dir_y = 1;
	      
	      /* Go faster! */

              brake--;
              if (brake < 0)
                brake = 0;
	      
#ifndef USE_SDL
	      playsound(3000, 10);
#else
	      playsound(snd_ceiling);
#endif
	    }

	  /* Bounce off bricks: */

	  if (ball_y < 60)
	    {
	      x = (ball_x + 4) >> 4;
	      y = (ball_y + 4) / 10;
              mx = (ball_x + 4) % 16;
              my = (ball_y + 4) % 10;

              hit = 0;
              if (y < 6)
                {
                  hit = hit_brick(x,y);
                  if (!hit)
                    {
                      if (mx + 4 > 15 && x < 9)
                        {
                          x++;
                          hit = hit_brick(x,y);
                          if (!hit)
                            x--;
                        } 
                      else if (mx - 4 < 0 && x > 0)
                        {
                          x--;
                          hit = hit_brick(x,y);
                          if (!hit)
                            x++;
                        }
                    }
                }
              if (!hit)
                {
                  if (my + 4 > 9 && y < 5)
                    {
                      y++;
                      hit = hit_brick(x,y);
                      if (!hit)
                        {
                          if (mx + 4 > 15 && x < 9)
                            {
                              x++;
                              hit = hit_brick(x,y);
                              if (!hit)
                                x--;
                            } 
                          else if (mx - 4 < 0 && x > 0)
                            {
                              x--;
                              hit = hit_brick(x,y);
                              if (!hit)
                                x++;
                            }
                        }
                    } 
                  else if (my - 4 < 0 && y > 0)
                    {
                      y--;
                      hit = hit_brick(x,y);
                      if (!hit)
                        {
                          if (mx + 4 > 15 && x < 9)
                            {
                              x++;
                              hit = hit_brick(x,y);
                            } 
                          else if (mx - 4 < 0 && x > 0)
                            {
                              x--;
                              hit = hit_brick(x,y);
                            }
                        }
                    }
                }

	      if (hit)
		{
                  ball_x = ball_bx >> 6;
                  ball_y = ball_by >> 6;

                  brick = cur_board[y][x];
		  if (brick == '=')
		    {
		      brick = '-';
		      add_score(10);
		      
#ifndef USE_SDL
		      playsound(2000, 10);
#else
		      playsound(snd_metal);
#endif

#ifdef USE_SDL
		      breaking_bricks[y][x].time = 10;
		      breaking_bricks[y][x].kind = cur_board[y][x];
#endif
		    }
		  else if (brick == '-' || brick == '/' ||
			   brick == '#')
		    {
		      add_score(5);
		      brick = ' ';
		      
		      num_bricks_left--;

#ifndef USE_SDL
		      playsound(750, 10);
#else
		      playsound(snd_brick);
#endif
		      
#ifdef USE_SDL
		      breaking_bricks[y][x].time = 10;
		      breaking_bricks[y][x].kind = cur_board[y][x];
#endif
		    }
		  else
		    {
#ifndef USE_SDL
		      playsound(100, 10);
#else
		      playsound(snd_unbreakable);
#endif
		    }
		  
		  
		  cur_board[y][x] = brick;


		  /* Erase (or redraw) brick: */
		 
		  draw_brick(x, y);
		}
	    }

	  
	  /* Bounce off the paddle: */

	  if (ball_y >= 142 &&
	      ball_x >= paddle_x - 8 &&
	      ball_x <= paddle_x + 32)
	    {
              dir_y = -1;
              counter = 0;
	      
	      /* Angle (xm) depends on where it hit the paddle: */

	      if (ball_x <= paddle_x - 4)
		slope -= dir_x * 3;
	      if (ball_x <= paddle_x + 2)
		slope -= dir_x * 2;
	      else if (ball_x <= paddle_x + 8)
		slope -= dir_x;
	      else if (ball_x <= paddle_x + 16)
		slope += 0;
	      else if (ball_x <= paddle_x + 22)
		slope += dir_x;
	      else if (ball_x <= paddle_x + 28)
		slope += dir_x * 2;
	      else
		slope += dir_x * 3;
              if (slope < 0)
                {
                  slope = -slope;
                  dir_x = -dir_x;
                }
              if (slope > 6)
                slope = 6;

#ifndef USE_SDL
	      playsound(1000, 10);
#else
	      playsound(snd_paddle);
#endif

	      add_score(1);
	    }
	  
	  /* Fall off bottom of screen: */
	  
	  if (ball_y > 150)
	    {
	      ball_launched = 0;
	      
	      DrawImage(pix_launchon, window, 64, 225, 32, 13);

#ifndef USE_SDL
	      playsound(125, 100);
#else
	      playsound(snd_die);
#endif
	      
	      balls--;
              draw_gamescreen();
	      
	      /* Game over!? */
	      
	      if (balls < 0)
		{
		  game_pending = 0;
		  done = 1;
		  
		  for (i = 1000; i >= 100; i = i / 2)
		    {
#ifndef USE_SDL
		      playsound(i, 200);
#else
		      playsound(snd_die);
#endif
		      usleep(200000);
		    }
		}
	    }
	}
      
      /* Go to next level? */
      
      if (num_bricks_left <= 0)
	{
	  /* Increment level: */
	  
	  level++;
	  
	  if (level > NUM_LEVELS)
	    level = 1;

          ball_x  = 76;
          ball_bx = 4864;
          ball_y  = 116;
          ball_by = 7424;
          redraw_brick_x = -1;
          reset_level();
	  draw_gamescreen();
          ball_launched = 0;
          DrawImage(pix_launchon, window, 64, 225, 32, 13);

#ifdef USE_SDL
          if (use_sound)
          {
            Mix_HaltMusic();
          }
#endif
	}

      /* figure out if the ball is stuck in an infinite loop */
      if (counter > 1000)
        {
          if (slope > 4)
            slope--;
          else
            slope++;
        }

      /* Draw paddle: */
      
      DrawImage(pix_paddle, window, paddle_x, 150, 32, 10);
      
      
      /* Draw ball: */
      
      if (ball_launched)
        DrawImage(pix_ball, window, ball_x, ball_y, 8, 8);



      /* Draw special effects: */

#ifdef USE_SDL
      for (y = 0; y < 6; y++)
      {
        for (x = 0; x < 10; x++)
	{
	  if (breaking_bricks[y][x].time > 0)
	  {
            SDL_Surface * tmp_surf;
	    char c;
		    
		  
	    breaking_bricks[y][x].time--;

	    dest.x = x * 16 + SDL_X_OFF;
	    dest.y = y * 10 + SDL_Y_OFF;
	    dest.w = 16;
	    dest.h = 10;
	      
	    if (breaking_bricks[y][x].time % 2)
	      c = breaking_bricks[y][x].kind;
	    else
              c = cur_board[y][x];
	      
            if (c == '-')
              tmp_surf = pix_brick1;
	    else if (c == '=')
              tmp_surf = pix_brick2;
	    else if (c == '#')
              tmp_surf = pix_brick3;
	    else if (c == ':')
              tmp_surf = pix_brick4;
	    else if (c == '/')
              tmp_surf = pix_brick5;
	    else
	      tmp_surf = NULL;
     
	    if (tmp_surf != NULL)
	      SDL_BlitSurface(tmp_surf, NULL, window, &dest);
	    else
	      SDL_FillRect(window, &dest, whitegc);
	  }
	}
      }
#endif
      
      
      /* Delay... */

#ifndef USE_SDL      
      XSync(display, 0);
#else
      SDL_Flip(window);
#endif
      
      gettimeofday(&now, NULL);
      
      time_padding = 10000 - ((now.tv_sec - then.tv_sec) * 1000000 +
                              (now.tv_usec - then.tv_usec));
      if (time_padding > 0)
      {
        usleep(time_padding);
      }

#ifdef USE_SDL
      if (use_sound && music)
      {
	if (!Mix_PlayingMusic())
	{
	  Mix_PlayMusic(mus_game[((level - 1) / 2) % NUM_GAME_MUSICS], -1);
	}
      }
#endif
      
    }
  while (!done);

      
#ifdef USE_SDL
  if (use_sound)
  {
    Mix_HaltMusic();
  }
#endif
}


/* Draw game screen: */

void draw_gamescreen(void)
{
  char str[21];
  int x, y;
  
  
  /* Blank areas: */

#ifndef USE_SDL
  XFillRectangle(display, window, whitegc, 0, 0, 160, 160);
  XFillRectangle(display, window, blackgc, 0, 160, 160, 80);
#else
  SDL_Rect dest;

  
  dest.x = SDL_X_OFF;
  dest.y = SDL_Y_OFF;
  dest.w = 160;
  dest.h = 160;
  SDL_FillRect(window, &dest, SDL_MapRGB(window->format, 255, 255, 255));

  dest.x = SDL_X_OFF;
  dest.y = 160 + SDL_Y_OFF;
  dest.w = 160;
  dest.h = 80;
  SDL_FillRect(window, &dest, SDL_MapRGB(window->format, 0, 0, 0));
#endif

  
  /* Draw water lapping: */
  
  for (x = 0; x <= 160; x = x + 29)
    {
      DrawImage(pix_water, window, x, 160, 29, 12);
    }
  
  
  /* (Status info) */
  
  DrawImage(pix_stats_toppipe, window, 0, 172, 160, 9);
  DrawImage(pix_stats_leftpipe, window, 0, 181, 11, 59);
  DrawImage(pix_stats_rightpipe, window, 149, 181, 11, 59);
  DrawImage(pix_stats, window, 12, 181, 52, 44);


  /* (Score) */
  
  sprintf(str, "%.6d", score);
  DrawNumbers(str, 70, 181);
  
  
  /* (Balls) */
  
  sprintf(str, "%.2d", balls);
  DrawNumbers(str, 70, 195);
  
  
  /* (Level) */
  
  sprintf(str, "%.2d", level);
  DrawNumbers(str, 70, 209);
  
  
  /* (Pause button) */
  
  DrawImage(pix_pause, window, 14, 225, 32, 13);
  

  /* (Launch button) */
  
  if (ball_launched == 0)
    DrawImage(pix_launchon, window, 64, 225, 32, 13);
  else
    DrawImage(pix_launchoff, window, 64, 225, 32, 13);
  
  
  /* (Sound control button) */
  
  if (sound == 1)
    DrawImage(pix_soundon, window, 126, 225, 18, 13);
  else
    DrawImage(pix_soundoff, window, 126, 225, 18, 13);
  

#ifdef USE_SDL
  /* (Music control button) */
  
  if (music == 1)
    DrawImage(pix_musicon, window, 100, 225, 18, 13);
  else
    DrawImage(pix_musicoff, window, 100, 225, 18, 13);
#endif
  
  
  /* (Bricks) */
  
  for (y = 0; y < 6; y++)
    {
      for (x = 0; x < 10; x++)
	{
	  draw_brick(x, y);
	}
    }
}


/* Setup! */

void setup(void)
{
#ifndef USE_SDL
  Window rootwindow;
  int screen, black, white;
  XSetWindowAttributes attr;
  XWMHints wmhints;
  unsigned long attr_mask;
  char wname[64];
#else
  int i;
#endif
  struct timeval tp;

  
  /* Seed random number generator: */

  gettimeofday(&tp, NULL);
  srand(tp.tv_sec + tp.tv_usec);
  
 
#ifndef USE_SDL 
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
  
  
  /* Open window: */
  
  attr.event_mask = (KeyPressMask | KeyReleaseMask | ButtonPressMask |
		     ButtonReleaseMask | PointerMotionMask |
		     ExposureMask | VisibilityChangeMask);

  attr.border_pixel = black;
  attr.background_pixel = white;
  attr_mask = CWEventMask | CWBackPixel | CWBorderPixel;
  
  window = XCreateWindow(display, rootwindow, 0, 0, 160, 240, 0,
			 DefaultDepthOfScreen(DefaultScreenOfDisplay(display)),
			 InputOutput, DefaultVisual(display, screen),
			 attr_mask, &attr);


  /* Set input hints and window name (so we appear in the window lists).
     Need to do this because of a bug in VRSM.  Not bad to do anyway, tho */

  wmhints.input = True;
  wmhints.flags |= InputHint;
  XSetWMHints(display, window, &wmhints);

  sprintf(wname, "BrickOut");
  XChangeProperty(display, window, XA_WM_NAME, XA_STRING, 8,
                  PropModeReplace, (unsigned char *)wname, strlen(wname) );

  
  /* Create primitive graphics contexts: */

  whitegc = CreateGC(display, window, white, black);
  blackgc = CreateGC(display, window, black, black);

  pastegc = CreateGC(display, window, white, black);

#else

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "Error: Can't init SDL video\n%s\n", SDL_GetError());
    exit(1);
  }

  use_sound = 1;

  if (SDL_Init(SDL_INIT_AUDIO) < 0)
  {
    fprintf(stderr, "Warning: Can't init SDL audio\n%s\n", SDL_GetError());
    use_sound = 0;
  }


  window = SDL_SetVideoMode(240, 320, 16, SDL_HWSURFACE);

  if (window == NULL)
  {
    fprintf(stderr, "Error: Can't open window\n%s\n", SDL_GetError());
    exit(1);
  }

  whitegc = SDL_MapRGB(window->format, 255, 255, 255);
  blackgc = SDL_MapRGB(window->format, 0, 0, 0);

  SDL_WM_SetCaption("Brickout", "Brickout");
#endif

  
  /* Create images: */
 
#ifndef USE_SDL 
  /* (Title screen stuff) */
  
  LoadImage(title_xpm, &pix_title);
  LoadImage(leftpipe_xpm, &pix_leftpipe);
  
  
  /* (Control buttons) */
  
  LoadImage(start_xpm, &pix_start);
  LoadImage(done_xpm, &pix_done);
  LoadImage(pause_xpm, &pix_pause);
  LoadImage(launchon_xpm, &pix_launchon);
  LoadImage(launchoff_xpm, &pix_launchoff);
  LoadImage(conton_xpm, &pix_conton);
  LoadImage(contoff_xpm, &pix_contoff);
  LoadImage(soundon_xpm, &pix_soundon);
  LoadImage(soundoff_xpm, &pix_soundoff);
  LoadImage(negon_xpm, &pix_negon);
  LoadImage(negoff_xpm, &pix_negoff);
  LoadImage(poson_xpm, &pix_poson);
  LoadImage(posoff_xpm, &pix_posoff);
  
  
  /* (Ball and paddle) */
  
  LoadImage(ball_xpm, &pix_ball);
  LoadImage(paddle_xpm, &pix_paddle);

  
  /* (Bricks) */
  
  LoadImage(brick1_xpm, &pix_brick1);
  LoadImage(brick2_xpm, &pix_brick2);
  LoadImage(brick3_xpm, &pix_brick3);
  LoadImage(brick4_xpm, &pix_brick4);
  LoadImage(brick5_xpm, &pix_brick5);


  /* (Stats stuff) */

  LoadImage(stats_xpm, &pix_stats);
  LoadImage(stats_toppipe_xpm, &pix_stats_toppipe);
  LoadImage(stats_leftpipe_xpm, &pix_stats_leftpipe);
  LoadImage(stats_rightpipe_xpm, &pix_stats_rightpipe);
  LoadImage(water_xpm, &pix_water);
  LoadImage(numbers_xpm, &pix_numbers);

#else
  
  /* (Title screen stuff) */
  
  pix_title = LoadImage(title_xpm);
  pix_leftpipe = LoadImage(leftpipe_xpm);
  
  
  /* (Control buttons) */
  
  pix_start = LoadImage(start_xpm);
  pix_done = LoadImage(done_xpm);
  pix_pause = LoadImage(pause_xpm);
  pix_launchon = LoadImage(launchon_xpm);
  pix_launchoff = LoadImage(launchoff_xpm);
  pix_conton = LoadImage(conton_xpm);
  pix_contoff = LoadImage(contoff_xpm);
  pix_soundon = LoadImage(soundon_xpm);
  pix_soundoff = LoadImage(soundoff_xpm);
  pix_musicon = LoadImage(musicon_xpm);
  pix_musicoff = LoadImage(musicoff_xpm);
  pix_negon = LoadImage(negon_xpm);
  pix_negoff = LoadImage(negoff_xpm);
  pix_poson = LoadImage(poson_xpm);
  pix_posoff = LoadImage(posoff_xpm);
  
  
  /* (Ball and paddle) */
  
  pix_ball = LoadImage(ball_xpm);
  pix_paddle = LoadImage(paddle_xpm);

  
  /* (Bricks) */
  
  pix_brick1 = LoadImage(brick1_xpm);
  pix_brick2 = LoadImage(brick2_xpm);
  pix_brick3 = LoadImage(brick3_xpm);
  pix_brick4 = LoadImage(brick4_xpm);
  pix_brick5 = LoadImage(brick5_xpm);


  /* (Stats stuff) */

  pix_stats = LoadImage(stats_xpm);
  pix_stats_toppipe = LoadImage(stats_toppipe_xpm);
  pix_stats_leftpipe = LoadImage(stats_leftpipe_xpm);
  pix_stats_rightpipe = LoadImage(stats_rightpipe_xpm);
  pix_water = LoadImage(water_xpm);
  pix_numbers = LoadImage(numbers_xpm);

#endif


#ifdef USE_SDL
  if (Mix_OpenAudio(44100, AUDIO_S16, 2, 512) < 0)
  {
    fprintf(stderr, "Warning: Can't open audio at 44100 Hz / 16-bit\n%s\n",
		    SDL_GetError());

    use_sound = 0;
  }

  
  /* Load sounds: */

  snd_wall = LoadSound(SOUNDDIR "wall.wav");
  snd_ceiling = LoadSound(SOUNDDIR "ceiling.wav");
  snd_metal = LoadSound(SOUNDDIR "metal.wav");
  snd_brick = LoadSound(SOUNDDIR "brick.wav");
  snd_unbreakable = LoadSound(SOUNDDIR "unbreakable.wav");
  snd_paddle = LoadSound(SOUNDDIR "paddle.wav");
  snd_die = LoadSound(SOUNDDIR "die.wav");


  /* Load music: */

  if (use_sound)
  {
    mus_title = Mix_LoadMUS(MUSICDIR "/Church.mod");
    if (mus_title == NULL)
    {
      fprintf(stderr, "Warning: Can't load music: " MUSICDIR "/Chruch.mod\n"
		      "%s\n",
		      SDL_GetError());

      use_sound = 0;
    }
  }


  for (i = 0; i < NUM_GAME_MUSICS && use_sound; i++)
  {
    mus_game[i] = Mix_LoadMUS(music_fnames[i]);
    if (mus_game[i] == NULL)
    {
      fprintf(stderr, "Warning: Can't load music: %s\n%s\n",
		      music_fnames[i], SDL_GetError());
      use_sound = 0;
    }
  }
  
#endif
  
  
  /* Bring window up! */
 
#ifndef USE_SDL 
  XMapWindow(display, window);
  XMapRaised(display, window);
  XSync(display, 0);
#else
  SDL_Flip(window);
#endif
}


/* Load settings from file: */

void loadsettings(void)
{
  sound = 1;
#ifdef USE_SDL
  music = 1;
#endif
  game_pending = 0;
}



/* Create a graphics context: */

#ifndef USE_SDL
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
#endif


/* Convert an image from XPM data to a pixmap: */

#ifndef USE_SDL
void LoadImage(char ** xpm, Pixmap * pix)
{
  XpmCreatePixmapFromData(display, window, xpm, pix, NULL, NULL);
}
#else
Pixmap LoadImage(const char * file)
{
  Pixmap pix;
  pix = SDL_LoadBMP(file);

  if (pix == NULL)
  {
    fprintf(stderr, "Error: Can't load %s\n%s\n", file, SDL_GetError());
    exit(1);
  }

  return pix;
}
#endif


/* Paste a pixmap onto the screen: */

void DrawImage(Pixmap pix, Drawable dest, int x, int y, int w, int h)
{
#ifndef USE_SDL
  XSetClipOrigin(display, pastegc, x, y);
  
  XCopyArea(display, pix, dest, pastegc, 0, 0, w, h, x, y);
#else
  SDL_Rect dest_rect;
  
  dest_rect.x = x + SDL_X_OFF;
  dest_rect.y = y + SDL_Y_OFF;
  dest_rect.w = w;
  dest_rect.h = h;
  
  SDL_BlitSurface(pix, NULL, dest, &dest_rect);
#endif
}


/* Draw numbers: */

void DrawNumbers(char * str, int x, int y)
{
  int i;
#ifdef USE_SDL
  SDL_Rect src, dest;
#endif

  for (i = 0; i < strlen(str); i++)
    {
#ifndef USE_SDL 
      XSetClipOrigin(display, pastegc, x, y);
#else
      src.x = (str[i] - '0') * 8;
      src.y = 0;
      src.w = 8;
      src.h = 14;

      dest.x = x + SDL_X_OFF;
      dest.y = y + SDL_Y_OFF;
#endif
      
      if (str[i] >= '0' && str[i] <= '9')
	{
#ifndef USE_SDL
	  XCopyArea(display, pix_numbers, window, pastegc,
		    (str[i] - '0') * 8, 0, 8, 14, x, y);
#else
	  SDL_BlitSurface(pix_numbers, &src, window, &dest);
#endif
	}
      
      x = x + 8;
    }
}



/* Play a sound! */

#ifndef USE_SDL

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

#else

void playsound(Mix_Chunk * snd)
{
  if (use_sound && sound)
  {
    Mix_PlayChannel(-1, snd, 0);
  }
}

#endif

/* Launch a ball! */

void launch_ball(void)
{
  int ball_x;
  /* Launch the ball with a random direction/etc: */
  
  ball_launched = 1;
  ball_x = (rand() % 60) - 30 + paddle_x;
  if (ball_x <= 10)
    ball_x = 10;
  if (ball_x >= 150)
    ball_x = 150;
  ball_bx = ball_x << 6;
  ball_by = 65 << 6;
  slope = (rand() % 5) + 1;
  brake = 8;
  dir_x = ((rand() % 2) * 2) - 1;
  dir_y = 1;

  /* Disable Launch button: */
  
  DrawImage(pix_launchoff, window, 64, 225, 32, 13);
}


/* Increment score, and redraw it on the screen: */

void add_score(int val)
{
  char str[20];
  
  score = score + val;
  
  sprintf(str, "%.6d", score);
  DrawNumbers(str, 70, 181);
}
      

/* Draw a brick: */
      
void draw_brick(int x, int y)
{
  char c;
#ifdef USE_SDL
  SDL_Rect dest;
#endif

  c = cur_board[y][x];

  if (c == '-')
    DrawImage(pix_brick1, window, x * 16, y * 10, 16, 10);
  else if (c == '=')
    DrawImage(pix_brick2, window, x * 16, y * 10, 16, 10);
  else if (c == '#')
    DrawImage(pix_brick3, window, x * 16, y * 10, 16, 10);
  else if (c == ':')
    DrawImage(pix_brick4, window, x * 16, y * 10, 16, 10);
  else if (c == '/')
    DrawImage(pix_brick5, window, x * 16, y * 10, 16, 10);
  else
   {
#ifndef USE_SDL
     XFillRectangle(display, window, whitegc, x * 16, y * 10, 16, 10);
#else
     dest.x = x * 16 + SDL_X_OFF;
     dest.y = y * 10 + SDL_Y_OFF;
     dest.w = 16;
     dest.h = 10;
     
     SDL_FillRect(window, &dest, whitegc);
#endif
    }
}


/* Initialize board: */

void reset_level(void)
{
  int x, y;
  
  num_bricks_left = 0;
  
  for (y = 0; y < 6; y++)
    {
      for (x = 0; x < 10; x++)
	{
#ifdef USE_SDL
            breaking_bricks[y][x].time = (rand() % 4) + 8;
            breaking_bricks[y][x].kind = cur_board[y][x];
#endif

	  cur_board[y][x] = boards[level - 1][y][x];
	  
	  if (cur_board[y][x] != ' ' &&
	      cur_board[y][x] != ':')
	    {
	      num_bricks_left++;
	    }

	}
    }
}

/* Check to see if we hit the given brick */

int hit_brick(int x,int y)
{
  int dx, dy;
  int corner, forward_ball, forward_corner;

  /* don't check anything if there is no brick here */
  if (cur_board[y][x] == ' ')
    return 0;

  dx = ((ball_bx >> 6) + 4) - (x << 4);
  dy = ((ball_by >> 6) + 4) - (y * 10);

  /* skip out if the ball is outside the sides */
  /* of the brick                              */
  if (dx < -4 || dx > 19)
    return 0;
  if (dy < -4 || dy > 13)
    return 0;

  /* check for clean hit on top or bottom edge of brick */
  if (dx >= -1 && dx <= 16)
    {
      dir_y = -dir_y;
      if (dy < 5)
          ball_by -= ((dy + 4) << 6);
      else 
          ball_by += ((14 - dy) << 6);
      return 1;
    }

  /* check for vertical slope - must be a corner hit */
  if (slope == 0)
    {
      if (dx < -2)
        slope = 2;
      else
        slope = 1;
      dir_x = (dy >= 5) ? 1 : -1;
      dir_y = -dir_y;
      if (dy < 5)
          ball_by -= ((dy + 4) << 6);
      else 
          ball_by += ((14 - dy) << 6);
      return 1;
    }

  /* check for clean hit on side edge of brick */
  if (dy >= -1 && dy > 10)
    {
      dir_x = -dir_x;
      if (dx < 8)
          ball_bx -= ((dx + 4) << 6);
      else 
          ball_bx += ((20 - dx) << 6);
      return 1;
    }

  /* if the slope is close to 45 (#4) then  */
  /* use a 6x6 square to approximate the    */
  /* ball at the corners.                   */
  if (slope >= 3 && slope <= 5)
    {
      dx -= 1;
      dy -= 1;
      if (dx < -3 || dx > 18 || 
          dy < -3 || dy > 12)
        {
          /* mark this brick for redrawing as */
          /* the ball will probaby erase part */
          /* of it as it goes by (because the */
          /* ball is really a square pixmap   */
          /* that just displays a round ball  */
          redraw_brick_x = x;
          redraw_brick_y = y;
          return 0;
        }
      dx += 1;
      dy += 1;
    }

  /* the ball hit a corner so figure that out now   */

  /* figure out which corner the ball hit           */
  /* 0        1                                     */
  /*  +------+                                      */
  /*  |      |                                      */
  /*  +------+                                      */
  /* 2        3                                     */
  corner = 0;
  if (dx >= 8)
    corner |= 1;
  if (dy >= 5)
    corner |= 2;
  forward_corner = (corner == 1 || corner == 2) ? 1 : 0;
  forward_ball   = (dir_y != dir_x) ? 1 : 0;

  /* first figure out if we hit the corner directly */
  /* or with a glancing blow                        */
  if (forward_corner ^ forward_ball)
    {
      /* for glancing blows, only toggle the dir_x   */
      /* or dir_y that makes sense for the corner    */
      if ((dir_x == 1 && dx < 8) ||
          (dir_x == -1 && dx >= 8))
        dir_x = -dir_x;
      else
        dir_y = -dir_y;
    }
  else 
    {
      /* it was a direct hit on the corner */
      dir_x = -dir_x;
      dir_y = -dir_y;
    }

  /* And adjust the ball so that it is not   */
  /* overlapping the brick anymore           */
  if ((dir_x == 1 && dx < 8) ||
      (dir_x == -1 && dx >= 8))
    {
      if (dy < 5)
        ball_by -= ((dy + 4) << 6);
      else 
        ball_by += ((14 - dy) << 6);
    } 
  else
    {
      if (dx < 8)
        ball_bx -= ((dx + 4) << 6);
      else 
        ball_bx += ((20 - dx) << 6);
    }
  
  return 1;
}


#ifdef USE_SDL

Mix_Chunk * LoadSound(char * fname)
{
  Mix_Chunk * s;

  
  if (use_sound)
  {
    s = Mix_LoadWAV(fname);

    if (s == NULL)
    {
      use_sound = 0;

      fprintf(stderr, "Warning: Can't load sound: %s\n%s\n", fname,
	      SDL_GetError());
    }

    return s;
  }
  else
    return NULL;
}

#endif
