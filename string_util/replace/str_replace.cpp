/**
 * str_replace.cpp
 * 2022-06-01 K.OHWADA
 */

// https://marycore.jp/prog/cpp/std-string-replace-first-all/#%E6%96%87%E5%AD%97%E5%88%97%E3%81%AE%E7%BD%AE%E6%8F%9B

#include <iostream>
#include <string>
#include <cassert>


/**
 * str_replace
 */
std::string str_replace(std::string str, std::string target,  std::string replace)
{
// position where the search string was found
    auto pos = str.find(target);
// length of search string
    auto len = target.length(); 

    if (pos != std::string::npos) {
    str.replace(pos, len, replace);
    }

    return str;
}


 using namespace std;


/**
 * main
 */
int main()
{
    string str1("a, b");
    string target(", ");
    string replace(" | ");

    string expect("a | b");

    auto str2 = str_replace(str1, target, replace);

    cout << str1 << endl;
    cout << str2 << endl;

    assert(str2 == expect);

    cout << "successful" << endl;

    return 0;
}

// a, b
// a | b

