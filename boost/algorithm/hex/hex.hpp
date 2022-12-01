#pragma once
/**
 * hex.hpp
 * 2022-06-01 K.OHWADA
 */

// convert binary data to/from hex string 
// reference : https://faithandbrave.hateblo.jp/entry/20120706/1341558540

#include <string>
#include <vector>
#include <iterator>
#include <boost/algorithm/hex.hpp>

// prototype
std::string bin2hex(std::vector<char> bin);
std::vector<char> hex2bin(std::string hex);


/**
 * bin2hex
 */
std::string bin2hex(std::vector<char> bin)
{
    std::vector<char> hex;
    boost::algorithm::hex(bin, std::back_inserter(hex));
    std::string str(hex.begin(), hex.end());
    return str;
}


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

