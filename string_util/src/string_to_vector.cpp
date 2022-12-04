/**
 * string_to_vector.cpp
 * 2022-06-01 K.OHWADA
 */

// // https://www.techiedelight.com/ja/convert-string-vector-chars-cpp/
// https://www.techiedelight.com/ja/convert-vector-chars-std-string/

#include <iostream>
#include <string>
#include <vector>
 #include <cassert>

using namespace std;


/**
 * main
 */
int main()
{
    std::string str1 = "Hello World!";
 
    std::cout << "str1: " << str1 << std::endl;

    std::vector<char> vec(str1.begin(), str1.end());
 
    std::cout << "vec: ";
    for (auto v: vec) {
        std::cout << v;
    } // for
    std::cout << std::endl;

    std::string str2(vec.begin(), vec.end());

    std::cout<< "str2: " << str2 << std::endl;

    assert(str1 == str2);

    std::cout << "successful " << std::endl;

    return 0;
}
