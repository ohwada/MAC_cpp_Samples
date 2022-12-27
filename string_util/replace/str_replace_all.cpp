/**
 * str_replace_all.cpp
 * 2022-06-01 K.OHWADA
 */

// https://marycore.jp/prog/cpp/std-string-replace-first-all/#%E6%96%87%E5%AD%97%E5%88%97%E3%81%AE%E7%BD%AE%E6%8F%9B

#include <iostream>
#include <string>
#include <cassert>


/**
 * str_replace_all
 */
std::string str_replace_all(std::string str, std::string target,  std::string replace)
{
  std::string::size_type pos = 0;
  while ((pos = str.find(target, pos)) != std::string::npos) {
    str.replace(pos, target.length(), replace);
    pos += replace.length();
  } // while

    return str;
}


 using namespace std;


/**
 * main
 */
int main()
{
    string str1("a, b, c, d");    
    string target(", ");     
    string replace("---"); 

    string expect("a---b---c---d");


    auto str2 = str_replace_all(str1, target,  replace);

    cout << str1 << endl;
    cout << str2 << endl;


    assert(str2 == expect);

    cout << "successful" << endl;

    return 0;
}



