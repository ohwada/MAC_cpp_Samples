 /**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// generate the locales
// https://www.boost.org/doc/libs/1_74_0/libs/locale/doc/html/locale_gen.html

#include <iostream>
#include <locale>
#include <boost/locale.hpp>

 using namespace std;

/**
 * main
 */
int main(void)
{

float num = 1234.5;

std::cout.imbue(std::locale::classic());
  std::cout << num << std::endl;
  std::cout.imbue(std::locale("en_US"));
  std::cout << num << std::endl;
  std::cout.imbue(std::locale("de_DE"));
  std::cout << num << std::endl;

// Create locale generator 
    boost::locale::generator gen;

std::locale loc_en = gen("en_US.UTF-8");
std::locale loc_de = gen("de_DE.UTF-8");

  std::cout.imbue( gen("") );
  std::cout << num << std::endl;
 std::cout.imbue( loc_en );
  std::cout << num << std::endl;
  std::cout.imbue( loc_de );
  std::cout << num << std::endl;


    return EXIT_SUCCESS;
}