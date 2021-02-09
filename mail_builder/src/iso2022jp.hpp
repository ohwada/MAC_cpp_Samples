#pragma once
/**
 * iconv Sample
 * 2021-02-01 K.OHWADA
 */

// ISO2022_JP library
// C++ wrapper  

#include <string.h>
#include <string>
#include "iso2022jp.h"



// prototype
bool convFromIso2022jp(const std::string str_src,  std::string &str_dst,  std::string &str_error);
bool convToIso2022jp(const std::string str_src,  std::string &str_dst,  std::string &str_error);
void dumpString( std::string text );
 void removeLastEsc(std::string line, std::string &text);


/**
 * convFromISO2022jp
 */
bool convFromIso2022jp(const std::string str_src,  std::string &str_dst,  std::string &str_error)
{

    char buf[CONV_BUFSIZE];
    char error[CONV_ERROR_SIZE];

    bool ret = iso2022jp_to_utf8( 
    (char *)str_src.c_str(),  
    str_src.length(),
    (char *)buf, 
    CONV_BUFSIZE, 
    (char *)error );

    if(ret){
        str_dst = std::string(buf);
    } else {
        str_error = std::string(error);
    }

    return ret;
}



/**
 * convToIso2022jp
 */
bool convToIso2022jp(const std::string str_src,  std::string &str_dst,  std::string &str_error)
{

    char buf[CONV_BUFSIZE];
    char error[CONV_ERROR_SIZE];

    bool ret = utf8_to_iso2022jp( 
    (char *)str_src.c_str(),  
    str_src.length(),
    (char *)buf, 
    CONV_BUFSIZE, 
    (char *)error );

    if(ret){
        str_dst = std::string(buf);
    } else {
        str_error = std::string(error);
    }

    return ret;
}


/*
 * dump_string
 */
void dumpString( std::string text )
{
    dump_string( (char *)text.c_str() );
}


/*
 *  removeLastEsc
 */
void removeLastEsc(std::string line, std::string &text)
{

    const char ESC = 0x1B;
    const char LEFT = 0x28;
    const char B = 0x42;
    const char CHAR_NULL = 0x00;

    text = line;

    int pos = line.find_last_of( ESC );
    if ( pos != std::string::npos ) {
        if ( (line[pos + 1] == LEFT)
        &&(line[pos + 2] == B) ) {
            text = line.substr(0, pos);
        }
    }

}
