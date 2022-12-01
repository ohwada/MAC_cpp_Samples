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

// prototyp
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

return os.str();
}


/**
 * decode_besr64
 */
std::vector<char> decode_base64(std::string str) 
{
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


