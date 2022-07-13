/***************************************
  $Header: /home/amb/CVS/xbomb/xbomb.h,v 1.9 2008-01-05 19:24:16 amb Exp $

  XBomb - 'Minesweeper' game - Version 2.2.

  Global header file.
  ******************/ /******************
  Written by Andrew M. Bishop

  This file Copyright 1994-2007 Andrew M. Bishop
  It may be distributed under the GNU Public License, version 2, or
  any higher version.  See section COPYING of the GNU Public license
  for conditions under which this file may be redistributed.
  ***************************************/


#ifndef XBOMB_H
#define XBOMB_H

/* State of each square */

#define EMPTY         0         /*+ No bomb. +*/
#define ACTUAL_BOMB  16         /*+ Really is a bomb. +*/
#define THINK_BOMB   32         /*+ User thinks there is a bomb. +*/
#define UNSEEN       64         /*+ Not seen by user. +*/
#define CORRECT     128         /*+ guessed correctly at end of game. +*/

/* Status of game */

#define GAME_CONTINUES 0        /*+ Normal state during game. +*/
#define GAME_WAIT      1        /*+ Waiting for start to be pressed.  +*/
#define GAME_LOST      2        /*+ Just finished a game and lost. +*/
#define GAME_WON       3        /*+ Just finished a game and won. +*/
#define GAME_READY     4        /*+ Ready to start playing. +*/

/* Status of game from the X part */

#define GAME_START     10       /*+ User has pressed start button. +*/
#define GAME_QUIT      11       /*+ User has pressed quit button. +*/

/* The level of difficulty */

#define GAME_LEVEL     12       /*+ Starting point for the levels. +*/
#define GAME_EASY      12       /*+ The Easy level. +*/
#define GAME_MEDIUM    13       /*+ The Medium level. +*/
#define GAME_DIFFICULT 14       /*+ The Difficult level. +*/

/* The type of game */

#define GAME_TYPE     20        /*+ Starting point for the game types. +*/
#define GAME_HEXAGON  20        /*+ The hexagons game. +*/
#define GAME_SQUARE   21        /*+ The squares game. +*/
#define GAME_TRIANGLE 22        /*+ The triangles game. +*/

/* The levels */

#define NLEVELS  3              /*+ The number of levels. +*/
#define MAX_SIZE 30             /*+ The maximum size of the grid. +*/

/* The game types */

#define NTYPES    3             /*+ The number of types of game. +*/

/* In hiscore.c */

void PrintHighScores(void);
void AddHighScore(int ticks);
void ShowHighScores(void);

/* In xbomb.c */

void StartGame(int level,int type);
void HideBombs(int xs,int ys);
void StopGame(void);
void DrawGrid(void);
void SelectSquare(int x,int y);
void SelectSquareOrAdjacent(int x,int y);
void SelectAdjacent(int x,int y);
void MarkBomb(int x,int y);
void RemoveEmpties(int x, int y);

/* In xwindow.c */

void InitialiseX(int *argc,char **argv);
void FinishUpX(void);
int ProcessXEvents(void);
void DrawSquare(int x,int y,unsigned char value);
void DisplayHighScores(char *scores[11][4],int which_score);
void ScaleWindow(void);
void StartClock(int reset);
int StopClock(void);
void SetUXB(int n);

#endif
