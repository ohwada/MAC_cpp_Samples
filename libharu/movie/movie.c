/**
 *  movie.c
 * 2022-06-01 K.OHWADA
 */

// printing a list of movies to a PDF  
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter09/problem_77/main.cpp

// TODO:
// draw a dividing line

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 #include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "movies.h"


#ifdef _WIN32
static const char* FONT_PATH = 
"c\windows\fonts\Arial.ttf";
#elif defined (__APPLE__)
static const char* FONT_PATH = 
"/Library/Fonts/Arial Unicode.ttf";
#else
static const char* FONT_PATH = 
"/usr/share/fonts/Arial.ttf";
#endif


jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif


/**
 *  error_handler
 */
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}


/**
 *  struct movie MOVIES
 */
const struct movie MOVIES[] =
   {
      { 1, "The Matrix", 1999, 136 },
      { 2, "Forrest Gump", 1994, 142 },
      { 3, "The Truman Show", 1998, 103 },
      { 4, "The Pursuit of Happyness", 2006, 117 },
      { 5, "Fight Club", 1999, 139 },
      { 6, "Inglourious Basterds", 2009, 153 },
      { 7, "The Dark Knight Rises", 2012, 164 },
      { 8, "The Dark Knight", 2008, 152 },
      { 9, "Pulp Fiction", 1994, 154 },
      { 10, "Inception", 2010, 148 },
      { 11, "The Shawshank Redemption", 1994, 142 },
      { 12, "The Silence of the Lambs", 1991, 118 },
      { 13, "Philadelphia", 1993, 125 },
      { 14, "One Flew Over the Cuckoo's Nest", 1975, 80 },
      { 15, "Memento", 2000, 113 },
      { 16, "Trainspotting", 1996, 94 },
      { 17, "Fargo", 1998, 98 },
      { 18, "Reservoir Dogs", 1992, 99 },
      { 19, "The Departed", 2006, 151 },
      { 20, "Se7en", 1995, 127 },
      { 21, "American History X", 1998, 119 },
      { 22, "Silver Linings Playbook", 2012, 122 },
      { 23, "2001: A Space Odyssey", 1968, 149 },
      { 24, "Monty Python and the Holy Grail", 1975, 91 },
      { 25, "Life of Brian", 1979, 94 },
      { 26, "Children of Men", 2006, 109 },
      { 27, "Sin City", 2005, 124 },
      { 28, "L.A. Confidential", 1997, 138 },
      { 29, "Shutter Island", 2010, 138 },
   };


const int TOP = 770;
const int BOTTOM = 60;
const int LEFT = 60;
const int RIGHT = 535;
const int LINE_HEIGHT = 28;
const int TITLE_FONT_SIZE = 20;
const int YEAR_FONT_SIZE = 18;

char buf1[BUFSIZE];
char buf2[BUFSIZE];
char buf3[BUFSIZE];


/**
 *  write_movie
 */
void write_movie(HPDF_Page page, HPDF_Font font, int i, int start, HPDF_REAL y0, HPDF_REAL length_x)
{
// title
    strcpy(buf1, MOVIES[i].title);

// tyear
    snprintf(buf2, BUFSIZE-1, " (%4d)", MOVIES[i].year);

// length
    int h = MOVIES[i].length / 60;
    int m = MOVIES[i].length % 60;
    snprintf(buf3, BUFSIZE-1, "%d:%02d", h, m);

    printf("%d: %s %s %s \n", i, buf1, buf2, buf3);

    int dif = i - start;
    HPDF_REAL y = y0 - LINE_HEIGHT*dif;

    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, TITLE_FONT_SIZE);
    HPDF_REAL tw = HPDF_Page_TextWidth(page, buf1);
    HPDF_REAL year_x = LEFT + tw;
    HPDF_Page_TextOut (page, LEFT, y, buf1);
   HPDF_Page_EndText (page);

    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, YEAR_FONT_SIZE);
    HPDF_Page_TextOut (page, year_x, y, buf2);
    HPDF_Page_TextOut (page, length_x, y, buf3);
   HPDF_Page_EndText (page);
}


/**
 *  print_pdf
 */
bool print_pdf(char* filepath)
{
  const char* PAGE_TITLE = "List of movies";

    const int PAGE_TITLE_FONT_SIZE = 26;

    const int NUM = (TOP - BOTTOM -  PAGE_TITLE_FONT_SIZE)/ LINE_HEIGHT;

    printf("num: %d \n", NUM);

    HPDF_Doc  pdf;
    HPDF_Page page1;
    HPDF_Page page2;
    HPDF_Font font;

    const int SIZE = sizeof(MOVIES)/sizeof(MOVIES[0]);
    printf("size: %d \n", SIZE);

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return false;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return false;
    }



    char* font_name = (char *)HPDF_LoadTTFontFromFile(pdf,  (char*)FONT_PATH , true);

    printf("font: %s \n", font_name);

    font = HPDF_GetFont (pdf,  font_name , NULL);

    /* Add a new page object. */
    page1 = HPDF_AddPage (pdf);

// A4 Portrait
    HPDF_Page_SetSize( page1,
        HPDF_PAGE_SIZE_A4,
        HPDF_PAGE_PORTRAIT );

    // title
    HPDF_Page_BeginText (page1);
    HPDF_Page_SetFontAndSize (page1, font,  PAGE_TITLE_FONT_SIZE);
    HPDF_Page_TextOut (page1, LEFT, TOP, PAGE_TITLE);
    HPDF_Page_EndText (page1);

// movie list
    HPDF_Page_BeginText (page1);
    HPDF_Page_SetFontAndSize (page1, font, TITLE_FONT_SIZE);

    HPDF_REAL y0 = TOP - PAGE_TITLE_FONT_SIZE - LINE_HEIGHT;

    HPDF_REAL tw = HPDF_Page_TextWidth (page1, "1;30");
    HPDF_REAL length_x = RIGHT - tw;

    HPDF_Page_EndText (page1);

for(int i=0; i<NUM; i++)
{
    write_movie(page1, font, i, 0, y0, length_x);
} // for

    // HPDF_Page_EndText (page1);

   page2 = HPDF_AddPage (pdf);

// A4 Portrait
    HPDF_Page_SetSize( page2,
        HPDF_PAGE_SIZE_A4,
        HPDF_PAGE_PORTRAIT );

  //HPDF_Page_BeginText (page2);
    //HPDF_Page_SetFontAndSize (page2, font, TITLE_FONT_SIZE);

for(int i=NUM; i<SIZE; i++)
{
    write_movie(page2, font, i, NUM, y0, length_x);
} // for

    //HPDF_Page_EndText (page2);


    HPDF_SaveToFile (pdf, filepath);

    /* clean up */
    HPDF_Free (pdf);

    return true;
}


/**
 *  main
 */
int main()
{
    char* FILEPATH = "movies.pdf";

   print_pdf(FILEPATH);

    printf("created: %s \n", FILEPATH);

    return 0;
}

// 0: The Matrix  (1999) 2:16 
// 1: Forrest Gump  (1994) 2:22 
// created: movies.pdf 

