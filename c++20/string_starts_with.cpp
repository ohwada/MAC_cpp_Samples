/**
 *  string_starts_with.cpp
 * 2022-06-01 K.OHWADA
 */

// https://qiita.com/Chippppp/items/620d2e5229f5c7e93f0c
// https://cpprefjp.github.io/reference/string/basic_string/starts_with.html

#include <iostream>
#include <string>

/**
 *  main
 */
int main() {
    std::string s = "Hello world!";
    std::cout << std::boolalpha << s.starts_with("Hello") << '\n';
    // true

    return 0;
}


