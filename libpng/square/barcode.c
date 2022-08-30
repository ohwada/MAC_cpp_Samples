/**
 * barcode.c
 * 2022-06-01 K.OHWADA
 */

// EAN-13 barcode generator 
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_84/main.cpp

#include<stdio.h>
#include <string.h> 
 #include "png_square.h"
#include "decimal_to_binary.h"



/**
 * encodings
 */
   const unsigned char ENCODINGS[10][3] =
   {
      { 0b0001101, 0b0100111, 0b1110010 },
      { 0b0011001, 0b0110011, 0b1100110 },
      { 0b0010011, 0b0011011, 0b1101100 },
      { 0b0111101, 0b0100001, 0b1000010 },
      { 0b0100011, 0b0011101, 0b1011100 },
      { 0b0110001, 0b0111001, 0b1001110 },
      { 0b0101111, 0b0000101, 0b1010000 },
      { 0b0111011, 0b0010001, 0b1000100 },
      { 0b0110111, 0b0001001, 0b1001000 },
      { 0b0001011, 0b0010111, 0b1110100 },
   };


/**
 * eandigits
 */
  const unsigned char EANDIGITS[10][6] =
   {
      { 0,0,0,0,0,0 },
      { 0,0,1,0,1,1 },
      { 0,0,1,1,0,1 },
      { 0,0,1,1,1,0 },
      { 0,1,0,0,1,1 },
      { 0,1,1,0,0,1 },
      { 0,1,1,1,0,0 },
      { 0,1,0,1,0,1 },
      { 0,1,0,1,1,0 },
      { 0,1,1,0,1,0 },
   };


/**
 * marker
 */
const unsigned char MARKER_START = 0b101;
const unsigned char MARKER_END = 0b101;
const unsigned char MARKER_CENTER = 0b01010;


/**
 * black_bar
 */
bool black_bar( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
// black
    return square(x1, y1, x2, y2, 0, 0, 0, CMAX);
}


/**
 * draw_digit
 */
   int draw_digit(
      unsigned char code, unsigned int size,
      int const x, int const y,
      int const digit_width, int const height)
   {
    // std::bitset<7> bits(code);
const int DIGITS = 7;
int bits[DIGITS];
decimal_to_binary(bits, DIGITS, code, DIGITS);

      int pos = x;
      for (int i = size - 1; i >= 0; --i)
      {
         if (bits[i])
         {
            black_bar(pos, y, pos + digit_width, y + height);
         }

         pos += digit_width;
      } // for

      return pos;
   }


/**
 * create_barcode
 */
  bool create_barcode(char*ean13,
      char* filepath,
      int const digit_width,
      int const digit_height,
      int const margin)
   {

    int img_width = margin * 2 + 95 * digit_width;
    int img_height = digit_height + margin * 2;
    create_image_bgcolor( img_width, img_height,
    CMAX, CMAX, CMAX, CMAX);

      int x = margin;
      x = draw_digit(MARKER_START, 3, x, margin, digit_width, digit_height);

int len =strlen(ean13);
unsigned char digits[len];

for(int i=0; i<len; i++) {
        digits[i] = ean13[i] - '0';
}

    for (int i = 0; i < 6; ++i)
    {
         int code = ENCODINGS[digits[1 + i]][EANDIGITS[digits[0]][i]];

         x = draw_digit(code, 7, x, margin, digit_width, digit_height);
    } // for

      x = draw_digit(MARKER_CENTER, 5, x, margin, digit_width, digit_height);

      for (int i = 0; i < 6; ++i)
      {
         int code = ENCODINGS[digits[7 + i]][2];
         x = draw_digit(code, 7, x, margin, digit_width, digit_height);
      } // for

      x = draw_digit(MARKER_END, 3, x, margin, digit_width, digit_height);

    return save_image(filepath);
}


/**
 * main
 */
int main()
{
    const int BUFSIZE = 256;
    char file[BUFSIZE];

    const int DIGIT_WIDTH = 5;
    const int DIGIT_HEIGHT = 150;
    const int MARGIN = 30;

    char* CODE = "8711253001202";

    strcpy(file, CODE);
    strcat(file, ".png");
    printf("%s \n", file);

    bool ret = create_barcode(
      CODE, file, 
       DIGIT_WIDTH, DIGIT_HEIGHT, MARGIN);
    if(!ret){
        return EXIT_FAILURE;
    }

    printf("created: %s \n", file);
 
    return EXIT_SUCCESS;
}
