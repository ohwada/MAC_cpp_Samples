/**
 *  stoi.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ stoi.cpp -std=c++11
// https://cpprefjp.github.io/reference/string/stoi.html

#include <iostream>
#include <string>


/**
 *  main
 */
int main()
{

// conversion in decimal
  {
    std::cout << "---- base = 10" << std::endl;

    int x = std::stoi("10"); // std::stoi("10", nullptr, 10);
    std::cout << x << std::endl;

    int xw = std::stoi(L"11"); // std::stoi(L"11", nullptr, 10);
    std::cout << xw << std::endl;
  }

// conversion in binary
  {
    std::cout << "---- base = 2" << std::endl;

    int x = std::stoi("1001", nullptr, 2);
    std::cout << x << std::endl;

    int xw = std::stoi(L"01001", nullptr, 2); // 先頭に0が付いていてもよい
    std::cout << xw << std::endl;
  }

  
// conversion in octal
  {
    std::cout << "---- base = 8" << std::endl;

    int x = std::stoi("10", nullptr, 8);
    std::cout << x << std::endl;

    int xw = std::stoi(L"10", nullptr, 8);
    std::cout << xw << std::endl;
  }

// conversion in hexadecimal
  {
    std::cout << "---- base = 16" << std::endl;

    int x = std::stoi("10", nullptr, 16);
    std::cout << x << std::endl;

    int xw = std::stoi(L"11", nullptr, 16);
    std::cout << xw << std::endl;
  }

// conversion in hexadecimal (with prefix)
  {
    int x = std::stoi("0x20", nullptr, 16);
    std::cout << x << std::endl;

    int xw = std::stoi(L"0x21", nullptr, 16);
    std::cout << xw << std::endl;
  }


// automatic detection of decimal, octal, and hexadecimal by base = 0
  {
    std::cout << "---- base = 0" << std::endl;

    std::cout << std::stoi("100", nullptr, 0) << std::endl;
    std::cout << std::stoi("0100", nullptr, 0) << std::endl;
    std::cout << std::stoi("0x100", nullptr, 0) << std::endl;

    std::cout << std::stoi(L"100", nullptr, 0) << std::endl;
    std::cout << std::stoi(L"0100", nullptr, 0) << std::endl;
    std::cout << std::stoi(L"0x100", nullptr, 0) << std::endl;
  }

  // example of using the second formal argument
  {
    std::cout << "---- use of idx parameter" << std::endl;

    std::string s = "30%";
    std::size_t i;
    int x = std::stoi(s, &i);
    std::cout << x << ' ' << s[i] << std::endl;

    std::wstring ws = L"31%";
    std::size_t wi;
    int xw = std::stoi(ws, &wi);
    std::cout << xw << ' ' << wi << std::endl;
  }


// if there is a space at the beginning of the string
  {
    std::cout << "---- space character before number" << std::endl;
    std::cout << std::stoi("    -1") << std::endl;
    std::cout << std::stoi(L"    -2") << std::endl;
  }

    return 0;
}

// ---- base = 10
// 10
// 11

