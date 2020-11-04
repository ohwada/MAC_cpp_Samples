#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// function for charset

#include <string>
#include "vmime/vmime.hpp"
 
// prototype
void iso2022jp_to_utf8(std::string src, std::string &utf8);
void utf8_to_iso2022jp(std::string src, std::string &iso2022);


// global
const std::string CHARSET_UTF8 = "UTF-8";
const std::string CHARSET_ISO2022JP = "ISO-2022-JP";


/** 
 * iso2022jp_to_utf8
  */
void iso2022jp_to_utf8(std::string src, std::string &utf8)
{
    vmime::string dst;
    vmime::charset::convert( src, dst, CHARSET_ISO2022JP, CHARSET_UTF8 );
    utf8 = dst;
}


/** 
 * utf8_to_iso2022jp
  */
void utf8_to_iso2022jp(std::string src, std::string &iso2022)
{
    vmime::string dst;
    vmime::charset::convert( src, dst, CHARSET_UTF8, CHARSET_ISO2022JP );
    iso2022 = dst;
}
