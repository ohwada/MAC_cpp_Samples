#pragma once
/**
 * response_parser.hpp
 * 2022-06-01 K.OHWADA
 */

#include<iostream>
#include<regex>
#include<string>

// prototype
bool split_header_body(std::string text, std::string &header, std::string &body);
bool is_transfer_encoding_chunked(std::string header);
bool parse_chunked_body(std::string response,  std::string &chunk_size, std::string &body);
int hex_to_int(std::string hex);


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


/*
 *  is_transfer_encoding_chunked
*/
bool is_transfer_encoding_chunked(std::string header)
{

    const std::string FIND("Transfer-Encoding: chunked"); 

    auto pos = header.find( FIND);
    
    if(pos == std::string::npos) {
        return false;
    }

    return true;
}


/**
 *  parse_chunked_body
 */
bool parse_chunked_body(std::string response,  std::string &chunk_size, std::string &body)
{

    const std::string PATTEN = 
R"(([0-9 a-f]{4})\r\n)";


    bool is_match = false;
    bool is_error = false;


try{

    std::regex reg(PATTEN);
    std::smatch m;

    if (std::regex_search(response, m, reg)) 
    {
        chunk_size = m[1].str();
 // std::cout << "chunk size: " << chunk_size << std::endl;
        is_match = true;
    }

} catch (std::regex_error e) {
    std::cerr << e.what() << std::endl;
    is_error = true;
}

    if( is_error ){
        return false;
    }

    if( !is_match ){
        return false;
    }

    int pos1 = response.find(chunk_size);

    int start = 0;

    if(pos1 != std::string::npos) {
        start = pos1 + chunk_size.size() + 2;
    }

   // std::cout << "pos1: " << pos1 << std::endl;
   // std::cout << "start: " << start << std::endl;


    std::string FIND("\r\n0\r\n");

   int pos2 = response.find(FIND);

    int length = 0;

    if(pos2 == std::string::npos) {
        length = response.size() - start;
    } else {
        length = pos2 - start + 2;
    }

   // std::cout << "pos2: " << pos2 << std::endl;
   // std::cout << "length: " << length << std::endl;


    body = response.substr(start, length);

    return true;
}


/*
 *  hex_to_int
*/
int hex_to_int(std::string hex)
{
    return std::stoi(hex, nullptr, 16) ;
}

