/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

#ifndef __BITMAP_H_INCLUDED__
#define __BITMAP_H_INCLUDED__

#define FILEHEADERSIZE 14
#define INFOHEADERSIZE 40
#define HEADERSIZE (FILEHEADERSIZE+INFOHEADERSIZE)

typedef struct{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}Rgb;

typedef struct{
    unsigned int height;
    unsigned int width;
    Rgb *data;
}Image;

Image *Read_Bmp(char *filename);

int Write_Bmp(char *filename, Image *img);

Image *Create_Image(int width, int height);

void Free_Image(Image *img);

#endif // __BITMAP_H_INCLUDED__

