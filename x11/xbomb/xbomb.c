/***************************************
  XBomb - 'Minesweeper' game - Version 2.2b.

  Main function of program - excludes all window interface parts.
  ******************/ /******************
  Written by Andrew M. Bishop

  This file Copyright 1994-2014 Andrew M. Bishop
  It may be distributed under the GNU Public License, version 2, or
  any higher version.  See section COPYING of the GNU Public license
  for conditions under which this file may be redistributed.
  ***************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#if defined(__sun__) && !defined(__svr4__)
int    printf(const char*, ... );
int    tolower (int c);
time_t time(time_t *t);
int    rand(void);
#endif

#include "xbomb.h"

/*+ The names of the different game +*/
char *levels[NLEVELS]={"Easy","Medium","Difficult"},      /*+ levels (difficulty). +*/
     *types [NTYPES] ={"Hexagons","Squares","Triangles"}; /*+ types (grid shapes). +*/

/*+ The size of the grids +*/
int widths [NLEVELS]={ 8 ,16 ,30},  /*+ width in tiles. +*/
    heights[NLEVELS]={ 8 ,16 ,16},  /*+ height in tiles. +*/
    nbombs [NLEVELS]={10 ,40 ,99};  /*+ number of bombs. +*/

/*+ The current game status +*/
static int status=GAME_WAIT;

/*+ The current information about the grid +*/
int grid_width,                 /*+ width. +*/
    grid_height,                /*+ height. +*/
    grid_bombs,                 /*+ number of bombs. +*/
    grid_level,                 /*+ level. +*/
    grid_type;                  /*+ type. +*/

/*+ The status of the tiles in the grid. +*/
static unsigned char state[MAX_SIZE][MAX_SIZE];

/*+ The status of the game, +*/
static int n_unseen,            /*+ the number of tiles unseen. +*/
           n_think,             /*+ the number of flags put down. +*/
           ticks;               /*+ The number of milliseconds of time passed. +*/


static int count_adjacent(int x,int y,int flag);


/*++++++++++++++++++++++++++++++++++++++
  The main program.

  int argc The command line parameters.

  char** argv The command line parameters.
  ++++++++++++++++++++++++++++++++++++++*/

int main(int argc,char** argv)
{
 int level=GAME_EASY,type=GAME_SQUARE;  /* Default values. */
 int xstatus=0;
 long t;

 printf("\n"
        "XBomb Version 2.2b\n"
        "\n"
        "(c) Andrew M. Bishop 1994-2013 [http://www.gedanken.org.uk/software/xbomb/]\n"
        "\n");

 if(argc>1)
   {
    int i,j;

    for(j=0;j<NLEVELS;j++)
      {
       char levstr[3];
       sprintf(levstr,"-%1d",j+1);
       for(i=1;i<argc;i++)
          if(!strcmp(levstr,argv[i]))
             level=GAME_LEVEL+j;
      }

    for(j=0;j<NTYPES;j++)
      {
       for(i=1;i<argc;i++)
          if(argv[i][0]=='-' && !strncasecmp(types[j],argv[i]+1,strlen(argv[i])-1))
             type=GAME_TYPE+j;
      }

    for(i=1;i<argc;i++)
       if(strlen(argv[i])>2 && !strncmp("-hiscore",argv[i],strlen(argv[i])))
         {
          grid_type=type;
          PrintHighScores();
          exit(0);
         }
   }

 t=time(&t);

 srand((unsigned int)t);

 InitialiseX(&argc,argv);

 StartGame(level,type);
 ShowHighScores();

 for(;;)
   {
    xstatus=ProcessXEvents();

    if(xstatus==GAME_QUIT)
       break;

    if(xstatus>=GAME_LEVEL && xstatus<(GAME_LEVEL+NLEVELS) && xstatus!=level)
      {
       level=xstatus;
       xstatus=GAME_START;
      }

    if(xstatus>=GAME_TYPE && xstatus<(GAME_TYPE+NTYPES) && xstatus!=type)
      {
       type=xstatus;
       xstatus=GAME_START;
      }

    if(xstatus==GAME_START)
      {
       if(status==GAME_CONTINUES)
          StopGame();
       StartGame(level,type);
       ShowHighScores();
      }

    if(status==GAME_WON)
      {
       int x,y;
       for(x=0;x<grid_width;x++)
          for(y=0;y<grid_height;y++)
             state[x][y]|=CORRECT;
       DrawGrid();
       StopGame();
       AddHighScore(ticks);
       ShowHighScores();
      }
    else if(status==GAME_LOST)
      {
       StopGame();
       ShowHighScores();
      }
   } 

 FinishUpX();

 return(0);
}


/*++++++++++++++++++++++++++++++++++++++
  Start a new game.

  int level The level of the game to play.

  int type The type of game to play.
  ++++++++++++++++++++++++++++++++++++++*/

void StartGame(int level,int type)
{
 int x,y;

 grid_type=type;
 grid_level=level;
 grid_width=widths[level-GAME_LEVEL];
 grid_height=heights[level-GAME_LEVEL];
 grid_bombs=nbombs[level-GAME_LEVEL];

 n_unseen=grid_width*grid_height;
 n_think=0;

 status=GAME_READY;

 for(x=0;x<grid_width;x++)
    for(y=0;y<grid_height;y++)
       state[x][y]=UNSEEN;

 ScaleWindow();
 DrawGrid();
 StartClock(0);
 SetUXB(grid_bombs);
}


/*++++++++++++++++++++++++++++++++++++++
  Hides the bombs in the grid.

  int xs The location that has no neighbouring bombs.

  int ys The location that has no neighbouring bombs.
  ++++++++++++++++++++++++++++++++++++++*/

void HideBombs(int xs,int ys)
{
 int i,x,y;

 state[xs][ys]+=CORRECT;

 for(i=0;i<grid_bombs;i++)
   {
    do{
       x=(rand()>>8)%grid_width;
       y=(rand()>>8)%grid_height;
      }
    while(state[x][y]!=UNSEEN || count_adjacent(x,y,CORRECT));

    state[x][y]+=ACTUAL_BOMB;
   }

 state[xs][ys]-=CORRECT;

 for(x=0;x<grid_width;x++)
    for(y=0;y<grid_height;y++)
       if(!(state[x][y]&ACTUAL_BOMB))
          state[x][y]+=count_adjacent(x,y,ACTUAL_BOMB);

 StartClock(1);
}


/*++++++++++++++++++++++++++++++++++++++
  Stop the game.
  ++++++++++++++++++++++++++++++++++++++*/

void StopGame(void)
{
 status=GAME_WAIT;
 ticks=StopClock();
}


/*++++++++++++++++++++++++++++++++++++++
  Draws the grid at the start of the game or for expose events.
  ++++++++++++++++++++++++++++++++++++++*/

void DrawGrid(void)
{
 int x,y;

 for(x=0;x<grid_width;x++)
    for(y=0;y<grid_height;y++)
       DrawSquare(x,y,state[x][y]);
}


/*++++++++++++++++++++++++++++++++++++++
  Select a single square and clear it or explode the bomb.

  int x The location of the square.

  int y The location of the square.
  ++++++++++++++++++++++++++++++++++++++*/

void SelectSquare(int x,int y)
{
 if(!(state[x][y]&UNSEEN) || state[x][y]&THINK_BOMB || status==GAME_WAIT)
    return;

 if(status==GAME_READY)
   {
    HideBombs(x,y);
    status=GAME_CONTINUES;
   }

 RemoveEmpties(x,y);

 if(state[x][y]&ACTUAL_BOMB)
   {
    int x,y;

    for(x=0;x<grid_width;x++)
       for(y=0;y<grid_height;y++)
          if(state[x][y]&UNSEEN)
            {
             if(!(state[x][y]&THINK_BOMB))
                state[x][y]&=~UNSEEN;
             if(state[x][y]&ACTUAL_BOMB)
                state[x][y]|=CORRECT;
            }
          else if(!(state[x][y]&ACTUAL_BOMB))
             state[x][y]|=CORRECT;

    status=GAME_LOST;
    DrawGrid();
   }
 else
    if(n_think==n_unseen)
       status=GAME_WON;
}


/*++++++++++++++++++++++++++++++++++++++
  Select a single square and clear it, explode the bomb or clear the adjacent.

  int x The location of the square.

  int y The location of the square.
  ++++++++++++++++++++++++++++++++++++++*/

void SelectSquareOrAdjacent(int x,int y)
{
 if(state[x][y]&UNSEEN)
    SelectSquare(x,y);
 else /* if(state[x][y]&EMPTY) */
    SelectAdjacent(x,y);
}


/*++++++++++++++++++++++++++++++++++++++
  Select all of the squares adjacent

  int x The location of the square.

  int y The location of the square.
  ++++++++++++++++++++++++++++++++++++++*/

void SelectAdjacent(int x,int y)
{
 int dx,dy,n,dd=(grid_type==GAME_TRIANGLE?2:1);

 if(state[x][y]&UNSEEN || status==GAME_WAIT)
    return;

 n=count_adjacent(x,y,THINK_BOMB);

 if(state[x][y]!=n)
    return;

 for(dx=-dd;dx<=dd;dx++)
   {
    if((x+dx)<0 || (x+dx)>=grid_width)
       continue;

    for(dy=-1;dy<=1;dy++)
      {
       if((y+dy)<0 || (y+dy)>=grid_height)
          continue;
       if(dx==0 && dy==0)
          continue;

       if(grid_type==GAME_HEXAGON && dy!=0 && dx==(1-2*(y%2)))
          continue;
       if(grid_type==GAME_TRIANGLE && dy==(2*((x+y)%2)-1) && (dx==-2 || dx==2))
          continue;

       if(!(state[x+dx][y+dy]&THINK_BOMB))
          SelectSquare(x+dx,y+dy);
      }
   }
}


/*++++++++++++++++++++++++++++++++++++++
  Marks as a bomb the square.

  int x The location of the square.

  int y The location of the square.
  ++++++++++++++++++++++++++++++++++++++*/

void MarkBomb(int x,int y)
{
 if(!(state[x][y]&UNSEEN) || status==GAME_WAIT || status==GAME_READY)
    return;

 if(n_think==grid_bombs && !(state[x][y]&THINK_BOMB))
    return;

 state[x][y]^=THINK_BOMB;

 if(state[x][y]&THINK_BOMB)
    n_think++;
 else
    n_think--;

 SetUXB(grid_bombs-n_think);

 DrawSquare(x,y,state[x][y]);

 if(n_think==n_unseen)
    status=GAME_WON;
}


/*++++++++++++++++++++++++++++++++++++++
  Removes the empty squares around here

  int x Start from this position.

  int y Start from this position.
  ++++++++++++++++++++++++++++++++++++++*/

void RemoveEmpties(int x, int y)
{
 int dx,dy,dd=(grid_type==GAME_TRIANGLE?2:1);

 if(!(state[x][y]&UNSEEN) || state[x][y]&THINK_BOMB)
    return;

 state[x][y]&=~UNSEEN;
 n_unseen--;
 DrawSquare(x,y,state[x][y]);

 if(state[x][y]!=EMPTY)
    return;

 for(dx=-dd;dx<=dd;dx++)
   {
    if((x+dx)<0 || (x+dx)>=grid_width)
       continue;

    for(dy=-1;dy<=1;dy++)
      {
       if((y+dy)<0 || (y+dy)>=grid_height)
          continue;
       if(dx==0 && dy==0)
          continue;

       if(grid_type==GAME_HEXAGON && dy!=0 && dx==(1-2*(y%2)))
          continue;
       if(grid_type==GAME_TRIANGLE && dy==(2*((x+y)%2)-1) && (dx==-2 || dx==2))
          continue;

       RemoveEmpties(x+dx,y+dy);
      }
   }
}


/*++++++++++++++++++++++++++++++++++++++
  Count the number of adjacent squares that are bombs.

  int count_adjacent Returns the number of adjacent tiles with the specified flag.

  int x The position to start from.

  int y The position to start from.

  int flag The type of thing to look for.
  ++++++++++++++++++++++++++++++++++++++*/

static int count_adjacent(int x,int y,int flag)
{
 int n=0,dx,dy,dd=(grid_type==GAME_TRIANGLE?2:1);

 for(dx=-dd;dx<=dd;dx++)
   {
    if((x+dx)<0 || (x+dx)>=grid_width)
       continue;

    for(dy=-1;dy<=1;dy++)
      {
       if((y+dy)<0 || (y+dy)>=grid_height)
          continue;

       if(grid_type==GAME_HEXAGON && dy!=0 && dx==(1-2*(y%2)))
          continue;
       if(grid_type==GAME_TRIANGLE && dy==(2*((x+y)%2)-1) && (dx==-2 || dx==2))
          continue;

       if(state[x+dx][y+dy]&flag)
          n++;
      }
   }

 return(n);
}
