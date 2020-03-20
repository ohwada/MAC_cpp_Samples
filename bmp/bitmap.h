/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 * original : https://github.com/kawasin73/todai-bmp
 */

//  Copied from http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB

#ifndef __BITMAP_H_INCLUDED__
#define __BITMAP_H_INCLUDED__

#define FILEHEADERSIZE 14                    //ファイルヘッダのサイズ
#define INFOHEADERSIZE 40                    //情報ヘッダのサイズ
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

//取得に成功すればポインタを失敗すればNULLを返す
Image *Read_Bmp(char *filename);

//書き込みに成功すれば0を失敗すれば1を返す
int Write_Bmp(char *filename, Image *img);

//Imageを作成し、RGB情報もwidth*height分だけ動的に取得する。
//成功すればポインタを、失敗すればNULLを返す
Image *Create_Image(int width, int height);
//Imageを解法する
void Free_Image(Image *img);

#endif /*__BITMAP_H_INCLUDED__*/

