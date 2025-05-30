/**
 * barcode.cpp
 * 2022-06-01 K.OHWADA
 */

// EAN-13 barcode generator 
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_84/main.cpp

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <assert.h>

#include "pngwriter.h"


/**
 * struct ean13
 */
struct ean13
{
public:
   ean13(std::string code)
   {
      if (code.length() == 13)
      {
         if (code[12] != '0' + get_crc(code.substr(0,12)))
            throw std::runtime_error("Not an EAN-13 format.");

         number = code;
      }
      else if (code.length() == 12)
      {
         number = code.data() + std::string(1, '0' + get_crc(code));
      }
   }

   ean13(unsigned long long code)
      :ean13(std::to_string(code))
   {
   }

   std::array<unsigned char, 13> to_array() const
   {
      std::array<unsigned char, 13> result;
      for (int i = 0; i < 13; ++i)
         result[i] = static_cast<unsigned char>(number[i] - '0');
      return result;
   }
   
   std::string to_string() const noexcept
   {
      return number;
   }

private:
   unsigned char get_crc(std::string code)
   {
      unsigned char weights[12] = { 1,3,1,3,1,3,1,3,1,3,1,3 };
      size_t index = 0;
      auto sum = std::accumulate(
         std::begin(code), std::end(code), 0,
         [&weights, &index](int const total, char const c) {
         return total + weights[index++] * (c - '0'); });

      return 10 - sum % 10;
   }

   std::string number;
};


/**
 * t ean13_barcode_generator
 */
struct ean13_barcode_generator
{
   void create(ean13 const & code,
      std::string filename,
      int const digit_width = 3,
      int const height = 50,
      int const margin = 10)
   {
const int BG = 65535; // white
      pngwriter image(
         margin * 2 + 95 * digit_width,
         height + margin * 2,
         BG,
         filename.data());

      std::array<unsigned char, 13> digits = code.to_array();

      int x = margin;
      x = draw_digit(marker_start, 3, image, x, margin, digit_width, height);

      for (int i = 0; i < 6; ++i)
      {
         int code = encodings[digits[1 + i]][eandigits[digits[0]][i]];
         x = draw_digit(code, 7, image, x, margin, digit_width, height);
      }

      x = draw_digit(marker_center, 5, image, x, margin, digit_width, height);

      for (int i = 0; i < 6; ++i)
      {
         int code = encodings[digits[7 + i]][2];
         x = draw_digit(code, 7, image, x, margin, digit_width, height);
      }

      x = draw_digit(marker_end, 3, image, x, margin, digit_width, height);

      image.close();
   }

private:
   int draw_digit(
      unsigned char code, unsigned int size,
      pngwriter& image,
      int const x, int const y,
      int const digit_width, int const height)
   {
      std::bitset<7> bits(code);
      int pos = x;
      for (int i = size - 1; i >= 0; --i)
      {
         if (bits[i])
         {
// black
const int R = 0;
const int G = 0;
const int B = 0;

            image.filledsquare(pos, y, pos + digit_width, y + height, R, G, B);
         }

         pos += digit_width;
      }

      return pos;
   }

   unsigned char encodings[10][3] =
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

   unsigned char eandigits[10][6] =
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

   unsigned char marker_start = 0b101;
   unsigned char marker_end = 0b101;
   unsigned char marker_center = 0b01010;
};


/**
 * main
 */
int main()
{
const std::string EXT(".png");
const std::string CODE1("8711253001202"); 
const std::string FILE1 = CODE1 + EXT;
const std::string CODE2("5901234123457"); 
const std::string FILE2 = CODE2 + EXT;

const int W = 5;
const int H = 150;
const int M = 30;


   assert("4006381333931" == ean13("400638133393").to_string());
   assert("0012345678905" == ean13("001234567890").to_string());
   assert("0012345678905" == ean13("001234567890").to_string());
   assert("8711253001202" == ean13("8711253001202").to_string());
   assert("5901234123457" == ean13("5901234123457").to_string());

   ean13_barcode_generator generator;

   generator.create(
      ean13(CODE1), 
      FILE1, 
      W, H, M);

std::cout << "created: " << FILE1 << std::endl;

   generator.create(
      ean13(CODE2),
      FILE2,
      W, H, M);

std::cout << "created: " << FILE2 << std::endl;

    return 0;
}
