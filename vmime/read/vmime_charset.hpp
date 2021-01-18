#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// function for charset

#include <string>
#include "vmime/vmime.hpp"

 
// prototype
void to_utf8(std::string src, std::string &utf8, vmime::charset charset);
void from_utf8(std::string utf8, std::string &dst,  vmime::charset charset );


// global
const vmime::charset CHARSET_UTF8( vmime::charsets::UTF_8 );
const char CHARS_ISO2022JP[] = "ISO-2022-JP";
const vmime::charset CHARSET_ISO2022JP( CHARS_ISO2022JP );



/** 
 * to_utf8
  */
void to_utf8(std::string src, std::string &utf8, vmime::charset charset )
{
    vmime::charset::convert( src, utf8, charset, CHARSET_UTF8 );
}


/** 
 * from_utf8
  */
void from_utf8(std::string utf8, std::string &dst, vmime::charset charset )
{
    vmime::charset::convert( utf8, dst, CHARSET_UTF8, charset );
}
