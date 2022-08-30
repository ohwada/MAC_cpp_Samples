/**
 * sin_wave.cpp
 * 2022-06-01 K.OHWADA
 */

// create sin wave PNG
// reference : http://pngwriter.sourceforge.net/

#include <iostream>
#include <string>
#include <pngwriter.h>

/**
 * main
 */
int main()
{

const char* FILE = (char *)"sin_wave.png";
const int W = 300; 
const int H = 300;

// bgbackgroundcolour : black
const int BG= 0;
   
// colour : blue
const double R= 0.0;
const double G= 0.0;
const double B= 1.0;

   pngwriter png(W, H, BG,  FILE);
   
   for(int x = 1; x <300; x++)
     {
     	int y = 150+100*sin((double)x*9/300.0);
        png.plot(x, y, R, G, B);
     } // for
     
   png.close();
   
std::cout << "created: " << FILE << std::endl;

   return 0;
}

// created: sin_wave.png

