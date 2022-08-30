/**
 * românia_flag.cpp
 * 2022-06-01 K.OHWADA
 */

// Creating a PNG that represents a national flag of România
// https://en.wikipedia.org/wiki/Romania 
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_82/main.cpp

#include <iostream>
#include <string>

#include "pngwriter.h"


/**
 * create_flag
 */
void create_flag(int const width, int const height, std::string filepath)
{
// bgbackgroundcolour : black
const int BG= 0;

   pngwriter flag{ width, height,BG, filepath.c_str() };

    const unsigned short MAX = 65535;
   const int size = width / 3;

   // Blue
   flag.filledsquare(0, 0, size, 2 * size, 0, 0, MAX);
   // Yellow 
   flag.filledsquare(size, 0, 2 * size, 2 * size, MAX, MAX, 0);
   // Red 
   flag.filledsquare(2 * size, 0, 3 * size, 2 * size, MAX, 0, 0);

   flag.close();
}


/**
 * main
 */
int main()
{
    const int W = 600;
    const int H = 400;
    const std::string FILE("românia_flag.png");

   create_flag(W, H, FILE);

    std::cout << "created: " << FILE << std::endl;

    return 0;
}
