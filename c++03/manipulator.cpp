/**
 * bin2hex.cpp
 * 2022-06-01 K.OHWADA
 */

// manipulator.cpp
// https://cpprefjp.github.io/reference/ios/dec.html
// https://marycore.jp/prog/cpp/print-binary-octal-decimal-hex/

#include <iostream>


/**
 * main
 */
int main()
{
    bool val = false;
    std::cout << val << " : " <<std::boolalpha << val << std::endl;

    val = true;
    std::cout << std::noboolalpha << val << " : " <<std::boolalpha << val << std::endl;


   std::cout << std::endl;

    std::cout << "dec \t";
    std::cout << "oct \t";
    std::cout << "hex \t";
    std::cout << "bitset<5>" << std::endl;

  for (int i = 0; i < 20; ++i) {
    std::cout << std::dec << i << '\t';
    std::cout << std::showbase << std::oct << i << '\t';
    std::cout << std::showbase << std::hex << i << '\t';
    std::cout << std::bitset<5>(i) << std::endl;
  }

    return 0;
}


