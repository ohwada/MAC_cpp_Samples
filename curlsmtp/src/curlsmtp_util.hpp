#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// file utility
// read write text file

#include <fstream>
#include <string>
#include <vector> 
#include <ctime>
#include <sys/stat.h>
#include <curl/curl.h>
#include "curlsmtp.h"
#include "msg_build.hpp"
#include "mail_json.hpp"
#include "file_util.hpp"
#include "mail_directory.h"


// constant
const std::string LF("\n");
const std::string USER_AGENT("CurlSmtp");


// prototype
struct MailParam getGmailParam( void );
struct MailParam getUbuntuMailParam( void );
char* getCurlVersion(void);
bool saveMail(std::string msg);


/**
* getGmailParam
 */
struct MailParam getGmailParam( void )
{
    std::string filepath = getMailDir()  + std::string( "/gmail.json" );

    MailParam p;
    std::string error;

    bool ret = readMailJsonFile(filepath, &p, error ); 
    if(!ret){
        std::cout << error << std::endl;
    }

    return p;
}


/**
* getUbuntuMailParam
 */
struct MailParam getUbuntuMailParam( void )
{
   std::string filepath = getMailDir() + std::string( "/ubuntu.json" );

    MailParam p;
    std::string error;

    bool ret = readMailJsonFile(filepath, &p, error ); 
    if(!ret){
        std::cout << error << std::endl;
    }

    return p;

}


/**
* saveMail
 */
bool saveMail(std::string msg)
{

    std::string filename;
    getTimestampFileName( "mail", "eml", filename);

    bool ret = writeTextFile(filename, msg );
    if(ret){
        std::cout <<  "saved to: " << filename << std::endl;
    }

    return ret;
}

