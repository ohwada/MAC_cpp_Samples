/**
 *  op_s.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ op_s.cpp -std=c++14
// reference : https://cpprefjp.github.io/reference/string/basic_string/op_s.html

#include <iostream>
#include <string>


/**
 *  main
 */
int main()
{
  using namespace std::literals::string_literals;


// string literal with unspecified character code
  std::string s1 = "hello"s; 

#if defined(__cpp_char8_t) && 201803L <= __cpp_char8_t
// UTF-8 string literal (C++20)
  std::u8string s2 = u8"hello"s; 
#else
// UTF-8 string literal (C++11-C++17)
  std::string s2 = u8"hello"s; 
#endif
// u16string literal
  std::u16string s3 = u"hello"s; 
// u32string literal
  std::u32string s4 = U"hello"s; 
// wstring literal with unspecified character code
  std::wstring s5 = L"hello"s; 

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    // std::cout << "s3: " << s3 << std::endl;
    // std::cout << "s4: " << s4 << std::endl;
    // std::cout << "s5: " << s5 << std::endl;

    return 0;
}

// s1: hello
// s2: hello

