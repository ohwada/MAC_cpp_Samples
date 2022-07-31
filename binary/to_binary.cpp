/**
 * to_binary.cpp
 * decimal_to_binary
 * 2022-06-01 K.OHWADA
 */

// g++ to_binary.cpp

#include <iostream>
#include <bitset>
#include <string>


/**
 * to_binary
 */
std::string to_binary(unsigned int value, int const digits)
{
   return std::bitset<32>(value).to_string().substr(32-digits, digits);
}


/**
 * main
 */
int main()
{
  
   for(unsigned int n = 0; n < 32; ++n)
   {
      std::cout 
         << n << ": " << to_binary(n, 5) << std::endl;
   } // for

    return 0;
}


// 0: 00000
// 1: 00001
// 2: 00010
// 3: 00011

