#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// function for body

#include <iostream>
#include <string>
#include "vmime/vmime.hpp"
#include "vmime_charset.hpp"




/**
* struct BodyInfo
  */
struct Bodyinfo
{
std::string type;
std::string subtype;
std::string charset;
std::string label;
size_t part_count;
};


// prototype
void getBodyInfo(
vmime::shared_ptr<vmime::body> body,  
struct Bodyinfo &info );
void getTextBody(
vmime::shared_ptr<vmime::body> body,  
std::string &content );
void printBodyInfo( struct Bodyinfo info );
bool saveBody(
vmime::shared_ptr<vmime::body> body,  
std::string filepath );


/** 
 * getBodyInfo
  */
void getBodyInfo(
vmime::shared_ptr<vmime::body> body,  
struct Bodyinfo &info )
{

    const std::string SLASH(" / "); 
    const std::string COLON(" : "); 

    vmime::mediaType media_type = body->getContentType();

    std::string type = media_type.getType();

    std::string subtype = media_type.getSubType();

    vmime::charset charset = body->getCharset();

   std::string  str_charset = charset.getName();

    size_t part_count = body->getPartCount();

    std::string label = type + SLASH + subtype;

    if(str_charset.size() > 0){
        label += COLON + str_charset;
    }

    info.type = type;
    info.subtype = subtype;
    info.charset = str_charset;
    info.part_count = part_count;
    info.label = label;

}


/** 
 * getTextBody
  */
void getTextBody(
vmime::shared_ptr<vmime::body> body,  
std::string &content )
{

    vmime::charset charset = body->getCharset();

    vmime::string str_out;
	vmime::utility::outputStreamStringAdapter out(str_out);

    vmime::shared_ptr<const vmime::contentHandler> cts  = body->getContents();

    std::string utf8;

    cts->extract(out);

    to_utf8(str_out, utf8, charset);

    content = utf8;

}


/** 
 * saveBody
  */
bool saveBody(
vmime::shared_ptr<vmime::body> body,  
std::string filepath )
{

    std::ofstream ofs;                   
    ofs.open( filepath,  ( std::ios_base::out | std::ios_base::binary) );
    vmime::utility::outputStreamAdapter file(ofs);
    if( !ofs.is_open() ){
            return false;
    }

	vmime::utility::outputStreamAdapter out(ofs);

    vmime::shared_ptr<const vmime::contentHandler> cts  = body->getContents();

    cts->extract(out);

    ofs.close();

    return true;
}

/** 
 * printBodyInfo
  */
void printBodyInfo( struct Bodyinfo info )
{

    std::cout << "type: " << info.type << std::endl;
    std::cout << "subtype: " << info.subtype << std::endl;
    std::cout << "charset: " << info.charset << std::endl;
    std::cout << "part count: " << info.part_count << std::endl;

}


