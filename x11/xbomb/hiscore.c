/***************************************
  $Header: /home/amb/CVS/xbomb/hiscore.c,v 1.13 2008-01-05 19:23:07 amb Exp $

  XBomb - 'Minesweeper' game - Version 2.2.

  Hi-score table management.
  ******************/ /******************
  Written by Andrew M. Bishop

  This file Copyright 1994-2007 Andrew M. Bishop
  It may be distributed under the GNU Public License, version 2, or
  any higher version.  See section COPYING of the GNU Public license
  for conditions under which this file may be redistributed.
  ***************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

#if defined(__sun__) && !defined(__svr4__)
int    fprintf(FILE*, const char*,...);
int    printf(const char*, ... );
int    sscanf(char*, const char*,...);
int    fread(void*,unsigned int,unsigned int, FILE*);
int    fwrite(const void*,unsigned int,unsigned int, FILE*);
int    fclose(FILE*);
long   time(long*);
#endif

#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "xbomb.h"

/*+ The current information about the grid +*/
extern int grid_type,           /*+ type. +*/
           grid_level;          /*+ level. +*/

/*+ The names of the different game +*/
extern char *levels[NLEVELS],   /*+ levels (difficulty). +*/
            *types[NTYPES];     /*+ types (grid shapes). +*/

/*+ The size of the grids +*/
extern int widths[NLEVELS],     /*+ width in tiles. +*/
           heights[NLEVELS],    /*+ height in tiles. +*/
           nbombs[NLEVELS];     /*+ number of bombs. +*/

/*+ The names of the high score tables. +*/
static char *filenames[NTYPES]={"/var/tmp/xbomb6.hi","/var/tmp/xbomb4.hi","/var/tmp/xbomb3.hi"};

/*+ The names of the positions in the high score tables. +*/
static char pos[11][5]={"Top","2nd","3rd","4th","5th","6th","7th","8th","9th","10th","Lost"};

/*+ The list of hi-scores for one grid type. +*/
static int  score[NLEVELS+1][11];

/*+ The list of hi-score usernames for one grid type. +*/
static char name[NLEVELS+1][11][21];

/*+ The list of hi-score dates for one grid type. +*/
static long date[NLEVELS+1][11];

/*+ Which of the hoigh scores in the table to highlight. +*/
static int which_hiscore=-1;

/*+ A structure to store the high score information in the file. +*/
struct score_name
{
 long score;                    /*+ The time in milliseconds. +*/
 char name[20];                 /*+ The user name. +*/
 long date;                     /*+ The time in seconds from the epoch. +*/
};


static void load_high_scores(void);
static void save_high_scores(void);

static void decrypt_score(struct score_name* sn);
static void encrypt_score(struct score_name* sn);


/*++++++++++++++++++++++++++++++++++++++
  Prints the high score tables.
  ++++++++++++++++++++++++++++++++++++++*/

void PrintHighScores(void)
{
 int l,j;

 load_high_scores();

 printf("\nHigh score tables for %s\n",types[grid_type-GAME_TYPE]);

 for(l=0;l<NLEVELS;l++)
   {
    printf("\nHigh scores for %s level (%dx%d grid of %s with %d bombs)\n",levels[l],widths[l],heights[l],types[grid_type-GAME_TYPE],nbombs[l]);
    for(j=0;j<10;j++)
      {
       printf("%4s : %12s = ",pos[j],name[l][j]);
       if(!date[l][j])
          printf("  SLOW");
       else if(l==0)
          printf("%6.2f",(double)score[l][j]/1000.0);
       else if(l==1)
          printf("%6.1f",(double)score[l][j]/1000.0);
       else
          printf("%6.0f",(double)score[l][j]/1000.0);
       if(date[l][j])
          printf(" : %s",ctime(&date[l][j]));
       else
         {printf(" : Never\n");break;}
      }
    printf("\n");
   }
}


/*++++++++++++++++++++++++++++++++++++++
  Adds a high score to the table if it is good enough.

  int ticks The time that was taken.
  ++++++++++++++++++++++++++++++++++++++*/

void AddHighScore(int ticks)
{
 int j;
 int changed=-1;
 struct passwd *pwd;
 char *username;

 load_high_scores();

 pwd=getpwuid(geteuid());
 if(pwd)
    username=pwd->pw_name;
 else
    username="?unknown?";

 which_hiscore=10;
 score[grid_level-GAME_LEVEL][10]=ticks;
 strcpy(name[grid_level-GAME_LEVEL][10],username);
 date[grid_level-GAME_LEVEL][10]=time(NULL);

 for(j=0;j<10;j++)
    if(ticks<score[grid_level-GAME_LEVEL][j])
       {changed=which_hiscore=j;break;}

 if(changed!=-1)
   {
    for(j=9;j>changed;j--)
      {
       score[grid_level-GAME_LEVEL][j]=score[grid_level-GAME_LEVEL][j-1];
       strcpy(name[grid_level-GAME_LEVEL][j],name[grid_level-GAME_LEVEL][j-1]);
       date[grid_level-GAME_LEVEL][j]=date[grid_level-GAME_LEVEL][j-1];
      }
    score[grid_level-GAME_LEVEL][changed]=ticks;
    strcpy(name[grid_level-GAME_LEVEL][changed],username);
    date[grid_level-GAME_LEVEL][changed]=time(NULL);

    save_high_scores();
   }
}


/*++++++++++++++++++++++++++++++++++++++
  Select a set of high scores for display.
  ++++++++++++++++++++++++++++++++++++++*/

void ShowHighScores(void)
{
 char datestr[11][32],*scores[11][4],scorestr[11][10];
 int i;

 load_high_scores();

 for(i=0;i<11;i++)
   {
    if(i==10 && which_hiscore!=10)
      {scores[i][0]=scores[i][1]=scores[i][2]=scores[i][3]="";continue;}

    strcpy(datestr[i],ctime(&date[grid_level-GAME_LEVEL][i]));

    scores[i][0]=pos[i];

    scores[i][1]=name[grid_level-GAME_LEVEL][i];

    if(!date[grid_level-GAME_LEVEL][i])
       scores[i][2]="SLOW";
    else if(grid_level==GAME_EASY)
      {sprintf(scorestr[i],"%6.2f",(double)score[grid_level-GAME_LEVEL][i]/1000.0);scores[i][2]=scorestr[i];}
    else if(grid_level==GAME_MEDIUM)
      {sprintf(scorestr[i],"%6.1f",(double)score[grid_level-GAME_LEVEL][i]/1000.0);scores[i][2]=scorestr[i];}
    else
      {sprintf(scorestr[i],"%6.0f",(double)score[grid_level-GAME_LEVEL][i]/1000.0);scores[i][2]=scorestr[i];}

    if(date[grid_level-GAME_LEVEL][i])
       scores[i][3]=datestr[i];
    else
       scores[i][3]="Never";
   }

 DisplayHighScores(scores,which_hiscore);

 which_hiscore=-1;
}


/*++++++++++++++++++++++++++++++++++++++
  Load in the high score table.
  ++++++++++++++++++++++++++++++++++++++*/

static void load_high_scores(void)
{
 FILE *f;
 int i,j;
 struct score_name sn;

 for(i=0;i<NLEVELS;i++)
    for(j=0;j<10;j++)
      {
       score[i][j]=9999999;
       strcpy(name[i][j],"nobody");
       date[i][j]=0;
      }

 f=fopen(filenames[grid_type-GAME_TYPE],"r");

 if(!f)
   {
    fprintf(stderr,"XBomb: Cannot open high score table '%s' to read.\n",filenames[grid_type-GAME_TYPE]);
    return;
   }

 for(i=0;i<NLEVELS;i++)
    for(j=0;j<10;j++)
      {
       if(!fread(&sn,sizeof(sn),1,f))
          break;
       decrypt_score(&sn);
       score[i][j]=sn.score;
       strcpy(name[i][j],sn.name);
       date[i][j]=sn.date;
      }

 fclose(f);
}


/*++++++++++++++++++++++++++++++++++++++
  Saves the high score table.
  ++++++++++++++++++++++++++++++++++++++*/

static void save_high_scores(void)
{
 FILE *f;
 int i,j;
 struct score_name sn;

 f=fopen(filenames[grid_type-GAME_TYPE],"w");

 if(!f)
   {
    fprintf(stderr,"XBomb: Cannot open high score table '%s' to write.\n",filenames[grid_type-GAME_TYPE]);
    return;
   }

 for(i=0;i<NLEVELS;i++)
    for(j=0;j<10;j++)
      {
       sn.score=score[i][j];
       strcpy(sn.name,name[i][j]);
       sn.date=date[i][j];
       encrypt_score(&sn);
       fwrite(&sn,sizeof(sn),1,f);
      }

 fclose(f);

 chmod(filenames[grid_type-GAME_TYPE],S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
}


/*++++++++++++++++++++++++++++++++++++++
  Decrypts the high score table

  struct score_name* sn The score and name to decrypt.
  ++++++++++++++++++++++++++++++++++++++*/

static void decrypt_score(struct score_name* sn)
{
 int i;
 char *p=(char*)sn;

 for(i=0;i<sizeof(struct score_name);i++)
    p[i]^=125;

 return;
}


/*++++++++++++++++++++++++++++++++++++++
  Encrypts the high score table

  struct score_name* sn The score and name to encrypt.
  ++++++++++++++++++++++++++++++++++++++*/

static void encrypt_score(struct score_name* sn)
{
 int i;
 char *p=(char*)sn;

 for(i=0;i<sizeof(struct score_name);i++)
    p[i]^=125;

 return;
}
