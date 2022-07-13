/***************************************
  XBomb - 'Minesweeper' game - Version 2.2b.

  All X Window functions.
  ******************/ /******************
  Written by Andrew M. Bishop

  This file Copyright 1994-2015 Andrew M. Bishop
  It may be distributed under the GNU Public License, version 2, or
  any higher version.  See section COPYING of the GNU Public license
  for conditions under which this file may be redistributed.
  ***************************************/


#include <stdio.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/Toggle.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/MenuButton.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/keysym.h>

#include <sys/time.h>
#include <unistd.h>

#include "xbomb.h"
#include "icon.h"

#if defined(__sun__) && !defined(__svr4__)
int gettimeofday(struct timeval *tv, struct timezone *tz);
#endif

/*+ The current information about the grid +*/
extern int grid_width,          /*+ width. +*/
           grid_height,         /*+ height. +*/
           grid_bombs,          /*+ number of bombs. +*/
           grid_type,           /*+ type. +*/
           grid_level;          /*+ level. +*/

/*+ The names of the different game +*/
extern char *levels[NLEVELS],   /*+ levels (difficulty). +*/
            *types[NTYPES];     /*+ types (grid shapes). +*/

static int xoffset,yoffset;
static int status=0;
static int unsigned scalex=10,scaley=10;
static int unsigned pixw,pixh;
static XtAppContext app_context;
static Display* display;
static Window play_window;
static Widget play_area,clock_w,uxb_w,hiscore,toplevel;
static Widget highscore,highscoresform,highscores[12][4];
static Pixmap icon_p,bombpix[2]={0,0};
static XPoint outline[8];

static void size_expose_proc(Widget w,XtPointer va,XEvent* e,Boolean* vb);
static void mouse_press_proc(Widget w,XtPointer va,XEvent* e,Boolean* vb);
static void key_press_proc(Widget w,XtPointer va,XEvent* e,Boolean* vb);
static void change_status_proc(Widget widget,XtPointer clientData,XtPointer callData);
static void hiscore_proc(Widget widget,XtPointer clientData,XtPointer callData);
static void close_proc(Widget w,XtPointer va,XEvent* e,Boolean* vb);
static void display_clock(XtPointer p,XtIntervalId i);
static int msecs(void);


#define GC_BOMB        0        /*+ For drawing the bomb and flag foreground. +*/
#define GC_ACTUAL_BACK 1        /*+ For drawing the bomb background. +*/
#define GC_THINK_BACK  2        /*+ For drawing the flag background. +*/
#define GC_NUMBER1     3        /*+ For drawing the number 1 on the grid. +*/
#define GC_NUMBER2     4        /*+ For drawing the number 2 +*/
#define GC_NUMBER3     5        /*+ For drawing the number 3 +*/
#define GC_NUMBER4     6        /*+ For drawing the number 4 +*/
#define GC_NUMBER5     7        /*+ For drawing the number 5 +*/
#define GC_NUMBER6     8        /*+ For drawing the number 6 +*/
#define GC_NUMBER7     9        /*+ For drawing the number 7 +*/
#define GC_NUMBER8     10       /*+ For drawing the number 8 +*/
#define GC_NUMBER9     11       /*+ For drawing the number 9 +*/
#define GC_NUMBER10    12       /*+ For drawing the number 10 (A) +*/
#define GC_NUMBER11    13       /*+ For drawing the number 11 (B) +*/
#define GC_NUMBER12    14       /*+ For drawing the number 12 (C) +*/
#define GC_UNSEEN      15       /*+ For unseen (hidden) tiles. +*/
#define GC_CORRECT     16       /*+ For correctly guessed tiles at the end.+*/
#define GC_BLANK       17       /*+ For blank squares. +*/
#define NUM_GC         18

/*+ A structure to hold the colour and font resource data in. +*/
struct temp
{
 XFontStruct* fontstruct;       /*+ The font. +*/
 Pixel colours[NUM_GC-1];       /*+ The colours. +*/
}
resources;

/*+ An array to hold the GCs in. +*/
static GC gc[NUM_GC];

/*+ The colour resources for the map. +*/
static XtResource xresources[]=
{
 {"font"    , "XBomb", XtRFontStruct, sizeof(XFontStruct*), 0               , XtRString, "lucidasans-24"},
 {"bomb"    , "XBomb", XtRPixel     , sizeof(String)      ,   sizeof(String), XtRString, "black" },
 {"bombreal", "XBomb", XtRPixel     , sizeof(String)      , 2*sizeof(String), XtRString, "red" },
 {"bombmark", "XBomb", XtRPixel     , sizeof(String)      , 3*sizeof(String), XtRString, "orange" },
 {"number"  , "XBomb", XtRPixel     , sizeof(String)      , 4*sizeof(String), XtRString, "navyblue" },
 {"number2" , "XBomb", XtRPixel     , sizeof(String)      , 5*sizeof(String), XtRString, "darkgreen" },
 {"number3" , "XBomb", XtRPixel     , sizeof(String)      , 6*sizeof(String), XtRString, "darkred" },
 {"number4" , "XBomb", XtRPixel     , sizeof(String)      , 7*sizeof(String), XtRString, "black" },
 {"number5" , "XBomb", XtRPixel     , sizeof(String)      , 8*sizeof(String), XtRString, "turquoise" },
 {"number6" , "XBomb", XtRPixel     , sizeof(String)      , 9*sizeof(String), XtRString, "orange" },
 {"number7" , "XBomb", XtRPixel     , sizeof(String)      ,10*sizeof(String), XtRString, "violet" },
 {"number8" , "XBomb", XtRPixel     , sizeof(String)      ,11*sizeof(String), XtRString, "lightgreen" },
 {"number9" , "XBomb", XtRPixel     , sizeof(String)      ,12*sizeof(String), XtRString, "blue" },
 {"number10", "XBomb", XtRPixel     , sizeof(String)      ,13*sizeof(String), XtRString, "blue" },
 {"number11", "XBomb", XtRPixel     , sizeof(String)      ,14*sizeof(String), XtRString, "blue" },
 {"number12", "XBomb", XtRPixel     , sizeof(String)      ,15*sizeof(String), XtRString, "blue" },
 {"hidden"  , "XBomb", XtRPixel     , sizeof(String)      ,16*sizeof(String), XtRString, "grey50" },
 {"correct" , "XBomb", XtRPixel     , sizeof(String)      ,17*sizeof(String), XtRString, "green" }
};


/*++++++++++++++++++++++++++++++++++++++
  Open the X connection.

  int *argc A pointer to the command line parameters.

  char **argv The pointer to the command line parameters.
  ++++++++++++++++++++++++++++++++++++++*/

void InitialiseX(int *argc,char **argv)
{
 Atom close_atom;
 XFontStruct *fontstruct;
 XGCValues values;
 Widget form,quit,start,menu,menushell;
 int i;

 /* Initialise the display */

 toplevel=XtVaAppInitialize(&app_context,"XBomb",
                            NULL, (Cardinal)0,argc,argv,NULL,
                            XtNtitle,"XBomb V2.2b",
                            XtNiconName,"XBomb",
                            NULL);

 display=XtDisplay(toplevel);

 /* Create the widgets */

 form=XtVaCreateManagedWidget("form",formWidgetClass,toplevel,
                              XtNwidth,100,XtNheight,100,
                              NULL);

 XtAddEventHandler(form,KeyReleaseMask,False,(XtEventHandler)key_press_proc,NULL);

 start=XtVaCreateManagedWidget("start",commandWidgetClass,form,
                               XtNlabel,"Restart",
                               XtNfromHoriz,NULL,XtNfromVert,NULL,
                               XtNleft,XtChainLeft,XtNtop,XtChainTop,XtNright,XtChainLeft,XtNbottom,XtChainTop,
                               NULL);
 XtAddCallback(start,XtNcallback,change_status_proc,(XtPointer)GAME_START);

 menu=XtVaCreateManagedWidget("menu",menuButtonWidgetClass,form,
                              XtNlabel,"Level",
                              XtNmenuName,"levelmenushell",
                              XtNfromHoriz,start,XtNfromVert,NULL,
                              XtNleft,XtChainLeft,XtNtop,XtChainTop,XtNright,XtChainLeft,XtNbottom,XtChainTop,
                              NULL);

 menushell=XtCreatePopupShell("levelmenushell",simpleMenuWidgetClass,menu,NULL,0);

 for(i=0;i<NLEVELS;i++)
   {
    Widget item=XtVaCreateManagedWidget(levels[i],smeBSBObjectClass,menushell,
                                        XtNlabel,levels[i],
                                        NULL);
    XtAddCallback(item,XtNcallback,change_status_proc,(XtPointer)(GAME_LEVEL+i));
   }

 menu=XtVaCreateManagedWidget("menu",menuButtonWidgetClass,form,
                              XtNlabel,"Game Type",
                              XtNmenuName,"typemenushell",
                              XtNfromHoriz,menu,XtNfromVert,NULL,
                              XtNleft,XtChainLeft,XtNtop,XtChainTop,XtNright,XtChainLeft,XtNbottom,XtChainTop,
                              NULL);

 menushell=XtCreatePopupShell("typemenushell",simpleMenuWidgetClass,menu,NULL,0);

 for(i=0;i<NTYPES;i++)
   {
    Widget item=XtVaCreateManagedWidget(types[i],smeBSBObjectClass,menushell,
                                        XtNlabel,types[i],
                                        NULL);
    XtAddCallback(item,XtNcallback,change_status_proc,(XtPointer)(GAME_TYPE+i));
   }

 hiscore=XtVaCreateManagedWidget("hiscore",toggleWidgetClass,form,
                                 XtNlabel,"Hi-Scores",
                                 XtNfromHoriz,menu,XtNfromVert,NULL,
                                 XtNleft,XtChainLeft,XtNtop,XtChainTop,XtNright,XtChainLeft,XtNbottom,XtChainTop,
                                 NULL);
 XtAddCallback(hiscore,XtNcallback,hiscore_proc,NULL);

 quit=XtVaCreateManagedWidget("quit",commandWidgetClass,form,
                              XtNlabel,"Quit",
                              XtNfromHoriz,hiscore,XtNfromVert,NULL,
                              XtNleft,XtChainLeft,XtNtop,XtChainTop,XtNright,XtChainLeft,XtNbottom,XtChainTop,
                              NULL);
 XtAddCallback(quit,XtNcallback,change_status_proc,(XtPointer)GAME_QUIT);

 play_area=XtVaCreateManagedWidget("grid",coreWidgetClass,form,
                                   XtNwidth,400,XtNheight,400,
                                   XtNtop,XtChainTop,XtNright,XtChainRight,XtNleft,XtChainLeft,XtNbottom,XtChainBottom,
                                   XtNfromHoriz,NULL,XtNfromVert,start,
                                   XtNresizable,True,
                                   NULL);

 XtAddEventHandler(play_area,ButtonPressMask,False,(XtEventHandler)mouse_press_proc,NULL);
 XtAddEventHandler(play_area,ExposureMask|StructureNotifyMask,False,(XtEventHandler)size_expose_proc,NULL);

 clock_w=XtVaCreateManagedWidget("clock",labelWidgetClass,form,
                                 XtNlabel,"Time : MMMM.MMM",
                                 XtNfromHoriz,NULL,XtNfromVert,play_area,
                                 XtNtop,XtChainBottom,XtNright,XtChainLeft,XtNleft,XtChainLeft,XtNbottom,XtChainBottom,
                                 NULL);

 uxb_w=XtVaCreateManagedWidget("uxb",labelWidgetClass,form,
                               XtNlabel,"UXB : MMM",
                               XtNfromHoriz,clock_w,XtNfromVert,play_area,
                               XtNtop,XtChainBottom,XtNright,XtChainLeft,XtNleft,XtChainLeft,XtNbottom,XtChainBottom,
                               NULL);

 /* Create graphics contexts */

 XtVaGetSubresources(play_area,(XtPointer)&resources,"grid","XBomb",xresources,XtNumber(xresources),NULL);

 values.font=resources.fontstruct->fid;
 for(i=0;i<NUM_GC-1;i++)
   {
    values.foreground=resources.colours[i];
    if(i==GC_UNSEEN)
      {
       GC tempgc;
       XGCValues gcxval;
       Dimension w,h;
       Pixmap stipple=XCreatePixmap(display,RootWindowOfScreen(XtScreen(toplevel)),8,8,1);

       gcxval.foreground=0;
       gcxval.background=0;
       tempgc=XCreateGC(display,stipple,GCForeground|GCBackground,&gcxval);

       XFillRectangle(display,stipple,tempgc,0,0,8,8);

       XSetForeground(display,tempgc,(unsigned long)~0);

       for(w=0;w<8;w++)
          for(h=0;h<8;h++)
             if((w+h)%2)
                XDrawPoint(display,stipple,tempgc,w,h);

       XtVaGetValues(play_area,XtNbackground,&values.background,NULL);
       values.stipple=stipple;
       values.fill_style=FillOpaqueStippled;
       gc[i]=XCreateGC(display,RootWindowOfScreen(XtScreen(toplevel)),GCForeground|GCBackground|GCFont|GCStipple|GCFillStyle,&values);

       XFreeGC(display,tempgc);
       XFreePixmap(display,stipple);
      }
    else
       gc[i]=XCreateGC(display,RootWindowOfScreen(XtScreen(toplevel)),GCForeground|GCFont,&values);
   }

 XtVaGetValues(play_area,XtNbackground,&values.foreground,NULL);
 gc[GC_BLANK]=XCreateGC(display,RootWindowOfScreen(XtScreen(toplevel)),GCForeground,&values);

 /* The highscore table. */

 highscore=XtVaCreatePopupShell("hiscores",topLevelShellWidgetClass,toplevel,
                                XtNtitle,"XBomb V2.2b High Scores",XtNiconName,"XBomb Hi-scores",
                                XtNmappedWhenManaged,False,
                                NULL);

 highscoresform=XtVaCreateManagedWidget("form",formWidgetClass,highscore,
                                        XtNwidth,200,XtNheight,100,
                                        NULL);

 XtAddEventHandler(highscoresform,KeyReleaseMask,False,(XtEventHandler)key_press_proc,NULL);

 for(i=0;i<12;i++)
   {
    char name[4][6];

    sprintf(name[0],"hs%da",i);
    sprintf(name[1],"hs%db",i);
    sprintf(name[2],"hs%ds",i);
    sprintf(name[3],"hs%dd",i);

    highscores[i][0]=XtVaCreateManagedWidget(name[0],labelWidgetClass,highscoresform,
                                             XtNborderWidth,0,XtNlabel,"MMM",
                                             XtNfromHoriz,NULL,XtNfromVert,i?highscores[i-1][0]:NULL,
                                             NULL);
    highscores[i][1]=XtVaCreateManagedWidget(name[1],labelWidgetClass,highscoresform,
                                             XtNborderWidth,0,XtNlabel,"MMMMMMM",
                                             XtNfromHoriz,highscores[i][0],XtNfromVert,i?highscores[i-1][0]:NULL,
                                             NULL);
    highscores[i][2]=XtVaCreateManagedWidget(name[2],labelWidgetClass,highscoresform,
                                             XtNborderWidth,0,XtNlabel,"MMMM",
                                             XtNfromHoriz,highscores[i][1],XtNfromVert,i?highscores[i-1][0]:NULL,
                                             NULL);
    highscores[i][3]=XtVaCreateManagedWidget(name[3],labelWidgetClass,highscoresform,
                                             XtNborderWidth,0,XtNlabel,"MMMMMMMMMMMMMM",
                                             XtNjustify,XtJustifyLeft,
                                             XtNfromHoriz,highscores[i][2],XtNfromVert,i?highscores[i-1][0]:NULL,
                                             NULL);
   }

 /* Add the icon */

 icon_p=XCreateBitmapFromData(display,RootWindowOfScreen(XtScreen(toplevel)),
                              icon_bits,icon_width,icon_height);

 XtVaSetValues(toplevel,XtNiconPixmap,icon_p,NULL);
 XtVaSetValues(highscore,XtNiconPixmap,icon_p,NULL);

 /* Show the widgets */

 XtRealizeWidget(toplevel);
 XtManageChild(highscore);
 XFlush(display);

 play_window=XtWindow(play_area);

 /* Centre the text */

 fontstruct=XQueryFont(display,XGContextFromGC(gc[GC_NUMBER1]));

 xoffset=XTextWidth(fontstruct,"0",1)/2;
 yoffset=fontstruct->ascent/2;

 /* Put an action on the close button */

 close_atom=XInternAtom(display,"WM_DELETE_WINDOW",False);

 XSetWMProtocols(display,XtWindow(toplevel),&close_atom,1);
 XtAddEventHandler(toplevel,0,True,close_proc,NULL);

 XSetWMProtocols(display,XtWindow(highscore),&close_atom,1);
 XtAddEventHandler(highscore,0,True,close_proc,NULL);
}


/*++++++++++++++++++++++++++++++++++++++
  Close the X connection.
  ++++++++++++++++++++++++++++++++++++++*/

void FinishUpX(void)
{
 int i;

 /* Free the graphics contexts. */

 for(i=0;i<NUM_GC;i++)
    XFreeGC(display,gc[i]);

 /* Free the pixmaps. */

 for(i=0;i<2;i++)
    XFreePixmap(display,bombpix[i]);

 XFreePixmap(display,icon_p);

 /* Close the display.. */

 XCloseDisplay(display);
}


/*++++++++++++++++++++++++++++++++++++++
  Process events.

  int ProcessXEvents Returns the game status.
  ++++++++++++++++++++++++++++++++++++++*/

int ProcessXEvents(void)
{
 XEvent event;

 status=0;

 XtAppNextEvent(app_context,&event);
 XtDispatchEvent(&event);

 return(status);
}


/*++++++++++++++++++++++++++++++++++++++
  Draw a value in the specified square.

  int x The X position.

  int y The y position.

  unsigned char value The value of the square.
  ++++++++++++++++++++++++++++++++++++++*/

void DrawSquare(int x,int y,unsigned char value)
{
 int xpos=0,ypos=0;
 static char grid_numbers[13][2]={" ","1","2","3","4","5","6","7","8","9","A","B","C"};
 int which_gc;

 /* Find the position. */

 switch(grid_type)
   {
   case GAME_HEXAGON:
    xpos=x*scalex+(y%2)*scalex/2;
    ypos=y*scaley+scaley/3;
    outline[0].x=xpos; outline[0].y=ypos;
    break;
   case GAME_SQUARE:
    xpos=x*scalex;
    ypos=y*scaley;
    break;
   case GAME_TRIANGLE:
    xpos=x*scalex/2+scalex/4;
    ypos=y*scaley-((x+y)%2)*scaley/2+scaley/2;
    if((x+y)%2)
       outline[4].x=xpos+scalex/4, outline[4].y=ypos+scaley;
    else
       outline[0].x=xpos+scalex/4, outline[0].y=ypos-scaley/2;
    break;
   }

 /* Choose the context. */

 if(value&UNSEEN)
   {
    if(value&THINK_BOMB)
       which_gc=GC_THINK_BACK;
    else
       which_gc=GC_UNSEEN;
   }
 else
   {
    if(value&ACTUAL_BOMB)
       which_gc=GC_ACTUAL_BACK;
    else
       which_gc=GC_BLANK;
   }

 /* Fill the background. */

 switch(grid_type)
   {
   case GAME_HEXAGON:
    XFillPolygon(display,play_window,gc[which_gc],outline,7,Convex,CoordModePrevious);
    break;
   case GAME_SQUARE:
    XFillRectangle(display,play_window,gc[which_gc],xpos,ypos,scalex,scaley);
    break;
   case GAME_TRIANGLE:
    if((x+y)%2)
       XFillPolygon(display,play_window,gc[which_gc],&outline[4],4,Convex,CoordModePrevious);
    else
       XFillPolygon(display,play_window,gc[which_gc],&outline[0],4,Convex,CoordModePrevious);
    break;
   }

 /* Draw the bomb or text. */

 if(value&UNSEEN)
   {
    if(value&THINK_BOMB)
       XCopyArea(display,bombpix[1],play_window,gc[GC_THINK_BACK],0,0,pixw,pixh,xpos,ypos);
   }
 else if(value&ACTUAL_BOMB)
    XCopyArea(display,bombpix[0],play_window,gc[GC_ACTUAL_BACK],0,0,pixw,pixh,xpos,ypos);
 else if((value&~CORRECT)>0 && (value&~CORRECT)<=12)
   {
    int text_xpos=xpos+pixw/2-xoffset;
    int text_ypos=ypos+pixh/2+yoffset;
    int gc_number=(value&~CORRECT)+GC_NUMBER1-1;  /* Calculate GC_NUMBERx offset. */
    XDrawString(display,play_window,gc[gc_number],text_xpos,text_ypos,grid_numbers[(value&~CORRECT)],1);
   }

 /* Draw the correct squares at the end. */

 if(value&CORRECT)
    which_gc=GC_CORRECT;
 else
    which_gc=GC_BOMB;

 switch(grid_type)
   {
   case GAME_HEXAGON:
    XDrawLines(display,play_window,gc[which_gc],outline,7,CoordModePrevious);
    break;
   case GAME_SQUARE:
    XDrawRectangle(display,play_window,gc[which_gc],xpos,ypos,scalex-1,scaley-1);
    break;
   case GAME_TRIANGLE:
    if((x+y)%2)
       XDrawLines(display,play_window,gc[which_gc],&outline[4],4,CoordModePrevious);
    else
       XDrawLines(display,play_window,gc[which_gc],&outline[0],4,CoordModePrevious);
    break;
   }

}


/*++++++++++++++++++++++++++++++++++++++
  Display the high scores.

  char *scores[11][4] The score information.

  int which_score Which score was just completed.
  ++++++++++++++++++++++++++++++++++++++*/

void DisplayHighScores(char *scores[11][4],int which_score)
{
 int i,j;
 Pixel fore,back;

 XtVaSetValues(highscores[0][0],XtNlabel,"Pos",NULL);
 XtVaSetValues(highscores[0][1],XtNlabel,"Name",NULL);
 XtVaSetValues(highscores[0][2],XtNlabel,"Time",NULL);
 XtVaSetValues(highscores[0][3],XtNlabel,"Date",NULL);

 XtVaGetValues(highscores[0][0],
               XtNbackground,&back,XtNforeground,&fore,
               NULL);

 for(j=0;j<4;j++)
    XtVaSetValues(highscores[0][j],
                  XtNforeground,fore,
                  XtNbackground,back,
                  NULL);

 for(i=0;i<11;i++)
    for(j=0;j<4;j++)
       XtVaSetValues(highscores[i+1][j],
                     XtNforeground,i==which_score?back:fore,
                     XtNbackground,i==which_score?fore:back,
                     XtNlabel,scores[i][j],
                     NULL);
}


/*++++++++++++++++++++++++++++++++++++++
  A callback that is activated by an expose event on the play area window.

  Widget w The widget that caused the callback.

  XtPointer va Not used.

  XEvent* e The event that requires action.

  Boolean* vb Not used.

  This function is only ever called from the Xt Intrinsics routines.
  ++++++++++++++++++++++++++++++++++++++*/

static void size_expose_proc(Widget w,XtPointer va,XEvent* e,Boolean* vb)
{
 if(e->type==ConfigureNotify)
    ScaleWindow();

 if(e->type==MapNotify || (e->type==Expose && !e->xexpose.count))
    DrawGrid();
}


/*++++++++++++++++++++++++++++++++++++++
  Scales the window.
  ++++++++++++++++++++++++++++++++++++++*/

void ScaleWindow(void)
{
 unsigned short old_width,old_height;
 unsigned short new_width=0,new_height=0;

 /* Get the old size. */

 XtVaGetValues(play_area,XtNwidth,&old_width,XtNheight,&old_height,NULL);

 /* Choose a new size */

 switch(grid_type)
   {
   case GAME_HEXAGON:
    scalex=(int)old_width*2/(7*(2*grid_width+1)/6);
    scaley=(int)old_height*3/(3*grid_height+1);
    scaley=6*((scalex+scaley)/12);
    if(scaley<30) scaley=18;
    scalex=(scaley*7)/6;
    new_width =scalex*(2*grid_width+1)/2;
    new_height=scaley*(3*grid_height+1)/3;
    break;
   case GAME_SQUARE:
    scalex=(int)old_width /grid_width;
    scaley=(int)old_height/grid_height;
    scalex=scaley=(scalex+scaley)/2;
    if(scalex<30) scalex=scaley=20;
    new_width =scalex*grid_width;
    new_height=scaley*grid_height;
    break;
   case GAME_TRIANGLE:
    scalex=(int)old_width*2/(grid_width+1);
    scaley=(int)old_height/(7*grid_height/8);
    scalex=4*((scalex+scaley)/8);
    if(scalex<16) scalex=16;
    scaley=(scalex*7)/8;
    new_width =scalex/2*(grid_width+1);
    new_height=scaley*grid_height;
    break;
   }

 /* If changed then re-size the window. */

 if(new_width!=old_width || new_height!=old_height)
   {
    unsigned short width,height;
    new_width-=old_width;
    new_height-=old_height;
    XtVaGetValues(XtParent(XtParent(play_area)),XtNwidth,&width,XtNheight,&height,NULL);
    XResizeWindow(display,XtWindow(XtParent(XtParent(play_area))),(unsigned)(width+new_width),(unsigned)(height+new_height));
   }
 else /* Must be here due to a correct sizing. */
   {
    int i;

    /* Get the outline of a funny shape tile. */

    if(grid_type==GAME_HEXAGON)
      {
       /* outline[0] is filled at the time of drawing */
       outline[1].x= (int)scalex/2;    outline[1].y=-(int)scaley/3;
       outline[2].x= (int)scalex/2;    outline[2].y= (int)scaley/3;
       outline[3].x= 0;                outline[3].y=-(int)scaley/3+scaley;
       outline[4].x=-(int)scalex/2;    outline[4].y= (int)scaley/3;
       outline[5].x=-(int)scalex/2;    outline[5].y=-(int)scaley/3;
       outline[6].x= 0;                outline[6].y= (int)scaley/3-scaley;
      }
    else if(grid_type==GAME_TRIANGLE)
      {
       /* outline[0] is filled at the time of drawing */
       outline[1].x=-(int)scalex/2+1;    outline[1].y= (int)scaley-1;
       outline[2].x= (int)scalex-2;      outline[2].y=0;
       outline[3].x=-(int)scalex/2+1;    outline[3].y=-(int)scaley+1;
       /* outline[4] is filled at the time of drawing */
       outline[5].x=-(int)scalex/2+1;    outline[5].y=-(int)scaley;
       outline[6].x= (int)scalex-2;      outline[6].y=0;
       outline[7].x=-(int)scalex/2+1;    outline[7].y= (int)scaley;
      }

    /* Draw the bomb and flag pixmaps. */

    for(i=0;i<2;i++)
      {
       if(grid_type==GAME_SQUARE)
          pixw=scalex,pixh=scaley;
       else if(grid_type==GAME_HEXAGON)
          pixw=scalex,pixh=scaley*2/3;
       else
          pixw=scalex/2,pixh=scaley/2;

       if(bombpix[i])
          XFreePixmap(display,bombpix[i]);

       bombpix[i]=XCreatePixmap(display,XtWindow(play_area),pixw,pixh,(unsigned)DefaultDepthOfScreen(XtScreen(play_area)));

       XFillRectangle(display,bombpix[i],gc[i+1],0,0,pixw,pixh);

       if(i==0)
         {
          XFillArc(display,bombpix[i],gc[GC_BOMB],(signed)pixw/4,(signed)pixh/2-2,pixw/2,pixh/2,0,360*64);
          XFillRectangle(display,bombpix[i],gc[GC_BOMB],3*(signed)pixw/8,3*(signed)pixh/8,pixw/4,pixh/4);
          XDrawLine(display,bombpix[i],gc[GC_BOMB],(signed)pixw/2,(signed)pixh/2,(signed)pixw/2,(signed)pixh/4);
          XDrawArc(display,bombpix[i],gc[GC_BOMB],(signed)pixw/2,2,pixw/2,pixh/2,70*64,110*64);
         }
       else
         {
          XPoint points[3];
          XFillArc(display,bombpix[i],gc[GC_BOMB],(signed)pixw/4,(signed)pixh*3/4-2,pixw/2,pixh/2,0,180*64);
          XDrawLine(display,bombpix[i],gc[GC_BOMB],(signed)pixw/2,(signed)pixh*3/4,(signed)pixw/2,(signed)pixh/4);
          points[0].x=pixw/2;   points[0].y=pixh/8;
          points[1].x=pixw*4/5; points[1].y=pixh/4;
          points[2].x=pixw/2;   points[2].y=pixh*3/8;
          XFillPolygon(display,bombpix[i],gc[GC_BOMB],points,3,Convex,CoordModeOrigin);
         }
      }

    /* Redraw the whole grid. */

    XClearWindow(display,play_window);
    DrawGrid();
   }
}


/*++++++++++++++++++++++++++++++++++++++
  A callback that is activated by a mouse press in the play area window.

  Widget w The widget that caused the callback.

  XtPointer va Not used.

  XEvent* e The event that requires action.

  Boolean* vb Not used.

  This function is only ever called from the Xt Intrinsics routines.
  ++++++++++++++++++++++++++++++++++++++*/

static void mouse_press_proc(Widget w,XtPointer va,XEvent* e,Boolean* vb)
{
 int x=-1,y=-1;
 int x_guess,y_guess,dx,dy;
 int i,j,d,dmin=1e6;

 /* Work out which tile mouse pressed in. */

 switch(grid_type)
   {
   case GAME_HEXAGON:
    y_guess=e->xbutton.y/scaley;
    x_guess=(e->xbutton.x-(y_guess%2)*scalex/2)/scalex;
    for(i=x_guess-1;i<=(x_guess+1);i++)
       for(j=y_guess-1;j<=(y_guess+1);j++)
         {
          if(i<0 || i>=grid_width || j<0 || j>=grid_height)
             continue;
          dx=e->xbutton.x-(i*scalex+(1+(j%2))*scalex/2);
          dy=e->xbutton.y-(j*scaley+2*scaley/3);
          d=dx*dx+dy*dy;
          if(d<dmin)
            {x=i;y=j;dmin=d;}
      }
    break;
   case GAME_SQUARE:
    x=e->xbutton.x/scalex;
    y=e->xbutton.y/scaley;
    break;
   case GAME_TRIANGLE:
    x_guess=e->xbutton.x*2/scalex;
    y=e->xbutton.y/scaley;
    for(i=x_guess-1;i<=(x_guess+1);i++)
      {
       if(i<0 || i>=grid_width)
          continue;
       dx=e->xbutton.x-(i*scalex/2+scalex/2);
       dy=e->xbutton.y-(y*scaley+(1+(1+i+y)%2)*scaley/3);
       d=dx*dx+dy*dy;
       if(d<dmin)
         {x=i;dmin=d;}
      }
    break;
   }

 /* Throw out errors. */

 if(x<0 || x>=grid_width || y<0 || y>=grid_height)
    {XBell(display,0);return;}

 /* Do something based on button number. */

 switch(e->xbutton.button)
   {
   case 1: SelectSquareOrAdjacent(x,y); break;
   case 2: SelectAdjacent(x,y); break;
   case 3: MarkBomb(x,y); break;
   }
}


/*++++++++++++++++++++++++++++++++++++++
  A callback that is activated by a key press in the play area window.

  Widget w The widget that caused the callback.

  XtPointer va Not used.

  XEvent* e The event that requires action.

  Boolean* vb Not used.

  This function is only ever called from the Xt Intrinsics routines.
  ++++++++++++++++++++++++++++++++++++++*/

static void key_press_proc(Widget w,XtPointer va,XEvent* e,Boolean* vb)
{
 KeySym k=XLookupKeysym((XKeyEvent*)e,0);
 Boolean shift=((XKeyEvent*)e)->state==ShiftMask || ((XKeyEvent*)e)->state==ControlMask;

 if(k==NoSymbol)return;

 /* Do an action based on which key is pressed. */

 switch(k)
   {
   case XK_1:
    status=GAME_EASY;
    break;
   case XK_2:
    status=GAME_MEDIUM;
    break;
   case XK_3:
    status=GAME_DIFFICULT;
    break;

   case XK_s:
    if(shift)
       status=GAME_SQUARE;
    else
       status=GAME_START;
    break;

   case XK_h:
    if(shift)
       status=GAME_HEXAGON;
    else
       hiscore_proc(NULL,NULL,NULL);
    break;

   case XK_q:
    do
      {
       if(w==toplevel)
         {status=GAME_QUIT;break;}
       if(w==highscore)
         {hiscore_proc(NULL,NULL,NULL);break;}
      }
    while((w=XtParent(w)));
    break;

   case XK_t:
    if(shift)
       status=GAME_TRIANGLE;
    break;

   default: ;
   }
}


/*++++++++++++++++++++++++++++++++++++++
  This function changes the state of the status flag.

  Widget widget Not used.

  XtPointer clientData The new status.

  XtPointer callData Not used.

  This function is only ever called from the Xt Intrinsics routines.
  ++++++++++++++++++++++++++++++++++++++*/

static void change_status_proc(Widget widget,XtPointer clientData,XtPointer callData)
{
 status=(int)clientData;
}


/*++++++++++++++++++++++++++++++++++++++
  This function displays the hi-scores.

  Widget widget Not used.

  XtPointer clientData Not used.

  XtPointer callData Not used.

  This function is only ever called from the Xt Intrinsics routines.
  ++++++++++++++++++++++++++++++++++++++*/

static void hiscore_proc(Widget widget,XtPointer clientData,XtPointer callData)
{
 static Boolean state=False;

 state=!state;

 if(!widget)
    XtVaSetValues(hiscore,XtNstate,state,NULL);

 if(state)
    XtPopup(highscore,XtGrabNone);
 else
    XtPopdown(highscore);
}


/*++++++++++++++++++++++++++++++++++++++
  A callback that is activated by a close window event on the toplevel window.

  Widget w The widget that caused the callback.

  XtPointer va Not used.

  XEvent* e The event that requires action.

  Boolean* vb Not used.

  This function is only ever called from the Xt Intrinsics routines.
  ++++++++++++++++++++++++++++++++++++++*/

static void close_proc(Widget w,XtPointer va,XEvent* e,Boolean* vb)
{
 XClientMessageEvent *cev=(XClientMessageEvent*)e;
 Atom atom_type=XInternAtom(display,"WM_PROTOCOLS",False);

 if(atom_type==cev->message_type)
   {
    Atom atom_proto=XInternAtom(display,"WM_DELETE_WINDOW",False);

    if(cev->format==32 && atom_proto==(Atom)cev->data.l[0])
      {
       if(w==toplevel)
          status=GAME_QUIT;
       else
          hiscore_proc(NULL,NULL,NULL);
      }
   }
}


/*++++++++++++++++++++++++++++++++++++++
  Sets the number of UXB in the grid.

  int n The number of UXB.
  ++++++++++++++++++++++++++++++++++++++*/

void SetUXB(int n)
{
 char string[16];

 sprintf(string,"UXB : %3d",n);
 XtVaSetValues(uxb_w,XtNlabel,string,NULL);
}


/*------------ The clock -------------*/

static int ticks;
static XtIntervalId id;
static struct timeval starttimeval;

/*++++++++++++++++++++++++++++++++++++++
  The function called for each clock tick.

  XtPointer p Not used.

  XtIntervalId i Not used.

  This function is only called from the Intrinsics.
  ++++++++++++++++++++++++++++++++++++++*/

static void display_clock(XtPointer p,XtIntervalId i)
{
 char string[16];
 int ticks1000=msecs();

 ticks=ticks1000/1000;
 ticks1000-=1000*ticks;

 id=XtAppAddTimeOut(app_context,(unsigned)(1000-ticks1000),(XtTimerCallbackProc)display_clock,NULL);

 sprintf(string,"Time : %4d",ticks);
 XtVaSetValues(clock_w,XtNlabel,string,NULL);
}


/*++++++++++++++++++++++++++++++++++++++
  Starts the clock

  int reset If 0 then resets the clock else if 1 then starts the clock.
  ++++++++++++++++++++++++++++++++++++++*/

void StartClock(int reset)
{
 if(reset)
   {
    gettimeofday(&starttimeval,NULL);
    display_clock(NULL,0);
   }
 else
   {
    char string[16];
    sprintf(string,"Time :    0");
    XtVaSetValues(clock_w,XtNlabel,string,NULL);
   }
}


/*++++++++++++++++++++++++++++++++++++++
  Stops the clock and returns the time in seconds.

  int StopClock Returns the time in seconds.
  ++++++++++++++++++++++++++++++++++++++*/

int StopClock(void)
{
 char string[20];

 XtRemoveTimeOut(id);
 ticks=msecs();

 sprintf(string,"Time : %8.3f",(double)ticks/1000.0);
 XtVaSetValues(clock_w,XtNlabel,string,NULL);

 return(ticks);
}


/*++++++++++++++++++++++++++++++++++++++
  Returns the number of milliseconds since starting the game.

  int msecs The number of milli-seconds.
  ++++++++++++++++++++++++++++++++++++++*/

static int msecs(void)
{
 struct timeval nowtimeval;

 gettimeofday(&nowtimeval,NULL);

 return(1000*(nowtimeval.tv_sec-starttimeval.tv_sec)+(nowtimeval.tv_usec-starttimeval.tv_usec)/1000);
}
