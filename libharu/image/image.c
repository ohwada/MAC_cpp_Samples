/**
 * image.c
 * 2022-06-01 K.OHWADA
 */

// Creating a PDF from a collection of images  
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter09/problem_78/main.cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "file_list.h"


jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif


/**
 * error_handler
 */
error_handler  (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}


/**
 * print_pdf
 */
bool print_pdf(
   char* pdfpath,
   char* dirpath)
{
    const char* FILE_SEPARATOR = "/";

const int BUFSIZE = 256;
char error[BUFSIZE];
char path[BUFSIZE];

    HPDF_Doc  pdf;
    HPDF_Page page1;
    HPDF_Page page2;
    HPDF_Destination dst;

  
    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return false;
    }

    /* error-handler */
    if (setjmp(env)) {
        HPDF_Free (pdf);
        return false;
    }

    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);

    /* add a new page object. */
    page1 = HPDF_AddPage (pdf);
    page2 = HPDF_AddPage (pdf);

// A4 Portrait
    HPDF_Page_SetSize( page1,
        HPDF_PAGE_SIZE_A4,
        HPDF_PAGE_PORTRAIT );

// A4 Portrait
    HPDF_Page_SetSize( page2,
        HPDF_PAGE_SIZE_A4,
        HPDF_PAGE_PORTRAIT );
 
    HPDF_REAL width;
    HPDF_REAL height;
    width = HPDF_Page_GetWidth (page1);
    height = HPDF_Page_GetHeight (page1);

printf("width: %.1f \n", width);
printf("height: %.1f \n", height);

    HPDF_REAL cx = width /2;

    dst = HPDF_Page_CreateDestination (page1);
    HPDF_Destination_SetXYZ (dst, 0, HPDF_Page_GetHeight (page1), 1);
    HPDF_SetOpenAction(pdf, dst);


int num; 
int size;
char** list = get_file_list_ext(dirpath, "jpg", &num, &size, error );


  HPDF_Image image1;
  HPDF_Image image2;
   HPDF_REAL w1;
    HPDF_REAL h1;
 HPDF_REAL w2;
    HPDF_REAL h2;
    HPDF_REAL margin;

    HPDF_REAL x1;
    HPDF_REAL x2;
    HPDF_REAL y1;
    HPDF_REAL y2;

for(int i=0; i<size; i++)
{
    printf( "%d : %s \n", i, list[i]);
    strcpy(path, dirpath);
    strcat(path, FILE_SEPARATOR);
    strcat(path, list[i]);

    int mod = i%2;
    if( mod == 0 ){
// even
        image1 = HPDF_LoadJpegImageFromFile(pdf, path);
        w1 = HPDF_Image_GetWidth (image1);
        h1 = HPDF_Image_GetHeight (image1);  
        x1 = cx - w1/2;
    }else if( mod == 1 ){
// odd
        image2 = HPDF_LoadJpegImageFromFile(pdf, path);
        w2 = HPDF_Image_GetWidth (image1);
        h2 = HPDF_Image_GetHeight (image1);
        margin = (height - h1 - h2)/4;
        x2 = cx - w2/2;
        y1 = h2 + 3*margin;
        y2 = margin;
    }

    if( i == 1 ){
        HPDF_Page_DrawImage (page1, image1, x1, y1, w1, h1);
        HPDF_Page_DrawImage (page1, image2, x2, y2, w2, h2);
    }else if( i == 3 ){
        HPDF_Page_DrawImage (page2, image1, x1, y1, w1, h1);
        HPDF_Page_DrawImage (page2, image2, x2, y2, w2, h2);
    }else if( i == 4 ){
            break;
    }

} // for


    /* save the document to a file */
    HPDF_SaveToFile (pdf, pdfpath);

    /* clean up */
    HPDF_Free (pdf);

    return true;
}


/**
 * main
 */
int main()
{
    char* FILEPATH = "einstein.pdf";

   char* DIRPATH =  "images";

   print_pdf(FILEPATH, DIRPATH);

    printf("created: %s \n", FILEPATH);

    return 0;
}

// 0 : Einstein4.jpg 
// 1 : Einstein2.jpg 
// 2 : Einstein3.jpg 
// 3 : Einstein1.jpg
// created einstein.pdf

