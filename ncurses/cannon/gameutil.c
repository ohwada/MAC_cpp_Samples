// 2022-05-01 K.OHWADA
// original : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/


// gameutil.c
// timer, rsndom, sound, etc.

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define BUFLEN 256
char player[BUFLEN] = "";

/* print error error */
void Fatal(char *msg)
{
  endwin();
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

/* print debug */
void Debug(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

/* Color initialization */
void InitColor( int bg )
{
  if (bg < -1) return;

  start_color();
  use_default_colors();

  // Color for displaying characters
  assume_default_colors(COLOR_BLACK, bg);	// init_pair(0, ...);
  init_pair(1, COLOR_RED, bg);
  init_pair(2, COLOR_GREEN, bg);
  init_pair(3, COLOR_YELLOW, bg);
  init_pair(4, COLOR_BLUE, bg);
  init_pair(5, COLOR_MAGENTA, bg);
  init_pair(6, COLOR_CYAN, bg);
  init_pair(7, COLOR_WHITE, bg);

  // Color for block character display
  init_pair(10, COLOR_BLACK, COLOR_BLACK);
  init_pair(11, COLOR_RED, COLOR_RED);
  init_pair(12, COLOR_GREEN, COLOR_GREEN);
  init_pair(13, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(14, COLOR_BLUE, COLOR_BLUE);
  init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(16, COLOR_CYAN, COLOR_CYAN);
  init_pair(17, COLOR_WHITE, COLOR_WHITE);

  // Background color
  if (bg >= 0) {
    bkgd(COLOR_PAIR(7-bg));
  } else {
    bkgd(COLOR_PAIR(0));
  }
}


/**
 * Use of color
 */
void UseColor(int c)
{
  attron(COLOR_PAIR(c));
}


/**
 *  Draw Block color
 */
void DrawBlocks(int y, int x, char *s)
{
  int w, h;

  getmaxyx(stdscr, h, w);
  if (y < 0) return;
  if (y >= h) return;
  while (*s != '\0') {
    if (x < 0); else
    if (x >= w); else
    if (*s != ' ') mvaddch(y, x, *s);
    s++;
    x++;
  }
}


/**
 *  Centered display of character string
 */
void CenterStr(int y, int x, char *s)
{
  int  n;
  n = strlen(s);
  x -= n/2;
  mvaddstr(y, x, s);
}


/**
 *  Random number initialization
 */
void InitRand()
{
  srand(time(NULL));
}


/**
 *  Integer random number greater than or equal to 0 and less than n
 */
int Rand(int n)
{
  return ((int)(n*(rand()/(RAND_MAX + 1.0))));
}


// sound
static int sound = 0;


/**
 *  Sound On / Off
 */
void SetSnd(int sw)
{
  sound = sw;
}


/**
 *  play sound
 */
void PlaySnd(char *file)
{
  static char cmd[256];

  if (sound == 0) return;		// Silent mode

  if (strlen(file) > 200) return;	// Buffer overflow prevention

  sprintf(cmd, "%s %s 2> /dev/null &", player, file);	// 再生
  system(cmd);
}


/**
 *  SetPlay
 */
void SetPlay(char *cmd)
{
  strncpy(player, cmd, BUFLEN);
}

// timer

static struct timeval start_time;


/**
 *  Timer initialization
 */
void InitWait()
{
  gettimeofday(&start_time, NULL);
}


/**
 *  diffTime
 */
static int diffTime(struct timeval *t1, struct timeval *t2)
{
  static int sec, msec;

  sec = t1->tv_sec - t2->tv_sec;
  msec = (t1->tv_usec - t2->tv_usec)/1000;

  if (msec < 0) {
    sec -= 1;
    msec += 1000;
  }
  return (sec*1000 + msec);
}


/**
 *  getTime
 */
static int getTime()
{
  static struct timeval now;

  gettimeofday(&now, NULL);
  return (diffTime(&now, &start_time));
}


/**
 *  Wait
 */
void Wait(int msec)
{
  while (1) {
    if (getTime() >= msec) return;
  }
}

