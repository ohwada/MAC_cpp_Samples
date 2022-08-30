/**
 * capcha.cpp
 * 2022-06-01 K.OHWADA
 */

// Creating verification text PNG images  
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_83/main.cpp

#include <iostream>
#include <string>
#include <random>
#include <array>

#include "pngwriter.h"

/**
 * create_image
 */
void create_image(
   int const width, int const height, 
   std::string font, int const font_size,
   std::string filepath)
{
// bgbackgroundcolour : black
const int BG= 0;

// colour : black
const int R= 0;
const int G= 0;
const int B= 0;

   pngwriter image{ width, height, BG, filepath.data() };

   std::random_device rd;
   std::mt19937 mt;
   auto seed_data = std::array<int, std::mt19937::state_size> {};
   std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
   std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
   mt.seed(seq);
   std::uniform_int_distribution<> udx(0, width);
   std::uniform_int_distribution<> udy(0, height);
   std::uniform_int_distribution<> udc(0, 65535);
   std::uniform_int_distribution<> udt(0, 25);

   // gradient background
   for (int iter = 0; iter <= width; iter++)
   {
      image.line(
         iter, 0, iter, height,
         65535 - int(65535 * ((double)iter) / (width)),
         int(65535 * ((double)iter) / (width)),
         65535);
   }

   // random text
   for (int i = 0; i < 6; ++i)
   {

      image.plot_text(
         // font
         (char *)font.c_str(), font_size,

         // position
         (int)(i*width / 6 + 10), (int)(height / 2 - 10),
         // angle
         (double)( (i % 2 == 0 ? -1 : 1)*(udt(mt) * 3.14) / 180),
         // text
         // std::string(1, char('A' + udt(mt))).data(),
         (char *)(std::string(1, char('A' + udt(mt))).c_str()),
         // color
         R, G, B);
   }

   // random lines
   for (int i = 0; i < 4; ++i)
   {
      image.line(udx(mt), 0, udx(mt), height,
         udc(mt), udc(mt), udc(mt));

      image.line(0, udy(mt), width, udy(mt),
         udc(mt), udc(mt), udc(mt));
   }

   image.close();
}


/**
 * main
 */
int main()
{
const std::string FILE("captcha.png");
const int W = 200;
const int H = 50;
const int SIZE = 8;

   std::string font_path;

#ifdef _WIN32
      font_path = R"(c:\windows\fonts\arial.ttf)";
#elif defined (__APPLE__)
      font_path = R"(/Library/Fonts/Arial Unicode.ttf)";
#else
   std::cout << "Font path: ";
   std::cin >> font_path;
#endif



   create_image(W, H, 
                font_path, SIZE,
                FILE);

std::cout << "created: " << FILE << std::endl;

    return 0;
}
