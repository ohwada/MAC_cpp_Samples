#pragma once
/**
 * bese64.hpp
 * 2022-06-01 K.OHWADA
 */


// convert binary data to/from base64 encoding 

// reference : https://sanichi999.hateblo.jp/entry/2014/12/06/154356
// https://amachang.hatenablog.com/entry/20090325/1237960531

#include <sstream>
#include <string>
#include <vector>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
 #include <boost/algorithm/string/predicate.hpp>

// prototype
 std::string encode_base64( std::vector<char> vec);
std::vector<char> decode_base64(std::string str);


/**
 * encode_bese64
 */

 std::string encode_base64( std::vector<char> vec) 
{
    using InputItr  = std::istreambuf_iterator<char>;
    using OutputItr = std::ostream_iterator<char>;
    using EncodeItr = boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<InputItr, 6, 8>>;   
    std::stringstream is; 
    std::stringstream os;

    for(auto v: vec){
        is << v;
    }

  copy(EncodeItr(InputItr(is)), EncodeItr(InputItr()), OutputItr(os));

    std::string res = os.str();

// make the number of characters a multiple of four
    int remainder = res.size() % 4;

    if(remainder == 1){
// add 3 equals
        res += "===";
    }else if(remainder == 2){
// add 2 equals
        res += "==";
    }else if(remainder == 3){
// add 1 equal
        res += "=";
    }

    return res;
}


/**
 * decode_besr64
 */
std::vector<char> decode_base64(std::string str) 
{
// remove trailing equals
    size_t len = str.size();
    if( boost::algorithm::iends_with(str, "===") ){
        str.erase((len-3), 3);
    }else if( boost::algorithm::iends_with(str, "==") ){
        str.erase((len-2), 2);
    }else if( boost::algorithm::iends_with(str, "=") ){
        str.substr((len-1), 1);
    }

    using InputItr  = std::istreambuf_iterator<char>;
    using OutputItr = std::ostream_iterator<char>;
    using DecodeItr = boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<InputItr>, 8, 6, char>;
    std::stringstream is;
    std::stringstream os;

    is << str;

    copy(DecodeItr(InputItr(is)), DecodeItr(InputItr()), OutputItr(os));

    std::string data = os.str();
    std::vector<char> vec( data.begin(),  data.end());
    return vec;
}


