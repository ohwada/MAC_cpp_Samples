/*
 * split.hpp
 * 2022-06-01 K.OHWADA 
*/

// split using stringstream
// https://qiita.com/iseki-masaya/items/70b4ee6e0877d12dafa8

#include <vector>
#include <string>
#include <sstream>

// prototype
std::vector<std::string> split(const std::string &s, char delim);


 /*
 * split
*/
std::vector<std::string> split(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
    if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
}

