/**
 *  boost_util.hpp
 * 2022-10-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string.hpp>

// prototype
std::vector<char> hex2bin(std::string hex);
std::string str_replase_all(std::string text);


/**
 * hex2bin
 */
std::vector<char> hex2bin(std::string hex)
{
    std::vector<char> vec(hex.begin(), hex.end());
    std::vector<char> bin;
    boost::algorithm::unhex(vec, std::back_inserter(bin));
    return bin;
}


/**
 * str_replase_all
 */

std::string str_replase_all(std::string text)
{
    std::string target(" ");
    std::string replace("");
    return boost::algorithm::replace_all_copy(text,  target, replace );
}


