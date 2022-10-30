#pragma once
/**
 * response_parser.hpp
 * 2022-06-01 K.OHWADA
 */

#include<iostream>
#include<string>

// prototype
bool split_header_body(std::string text, std::string &header, std::string &body);


/*
 *  split_header_body
*/
bool split_header_body(std::string text, std::string &header, std::string &body)
{

    const std::string FIND_WORD("\r\n\r\n"); 


    auto pos = text.find( FIND_WORD);
    
    if(pos == std::string::npos) {
        return false;
    }

    header = text.substr(0, pos);
    body = text.substr(pos+4);

    return true;
}

