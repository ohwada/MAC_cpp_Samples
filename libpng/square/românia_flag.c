/**
 * românia_flag.c
 * 2022-06-01 K.OHWADA
 */

// Creating a PNG that represents a national flag of România
// https://en.wikipedia.org/wiki/Romania 
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_82/main.cpp


#include <stdio.h>
 #include "png_square.h"


/**
 * create_flag
 */
bool create_flag(int const width, int const height, char* filepath)
{

    create_image(width, height);

   const int SIZE = width / 3;

   // Blue
   square(0, 0, SIZE, height, 0, 0, CMAX, CMAX);
   // Yellow
   square(SIZE, 0, 2 * SIZE, height, CMAX, CMAX, 0,  CMAX);
   // Red
   square(2 * SIZE, 0, 3 * SIZE, height, CMAX, 0, 0, CMAX);

    return save_image(filepath);
}


/**
 * main
 */
int main()
{
const int WIDTH = 600;
const int HEIGHT = 400;

    char* FILEPATH = "românia_flag.png";

   bool ret = create_flag(WIDTH, HEIGHT, FILEPATH);
    if(!ret){
        return EXIT_FAILURE;
    }

    printf("created: %s \n", FILEPATH);

    return EXIT_SUCCESS;
}
