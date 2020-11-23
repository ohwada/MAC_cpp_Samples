#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// utility for message part


#include <iostream>
#include <string>
#include "response_msg_json.hpp"
#include "ustd_string.h"



// prototype
void printMailPartBody(struct MailPart part);
bool decodeB64(std::string src, std::string &dest);
bool hasAttachmentId(struct MailPart part);
bool isTextPlain(struct MailPart part);



/**
 * printMailPartBody
 */
void printMailPartBody(struct MailPart part)
{

    std::string data( part.data );

    std::string dest;

    bool ret = decodeB64(data, dest);

    if(!ret){
        return;
    }

    if( isTextPlain(part) ) {
        std::cout << "----------" << std::endl;
        std::cout << dest << std::endl;
        std::cout << "----------" << std::endl;
    }

}


/**
 * decodeB64
 */
bool decodeB64(std::string src, std::string &dest)
{
    int len = src.length();
    if(len == 0){
        return false;
    }

    char *data =  (char *)src.c_str();

    std::vector<char> vec;

    size_t size = ustd::string::base64decode( data, len, vec);

    if(size == 0){
        return false;
    }

    for(auto c: vec) {
        dest += c;
    }

    return true;
}


/**
 * hasAttachmentId
 */
bool hasAttachmentId(struct MailPart part)
{
    std::string attachmentId = part.attachmentId;
    if ( attachmentId.length() > 0 ) {
        return true;
    }
    return false;
}



/**
 *  isTextPlain
 */
bool isTextPlain(struct MailPart part)
{
    const std::string MIME_TEXT_PLAIN("text/plain");

    std::string mimeType = part.mimeType;

    if(mimeType == MIME_TEXT_PLAIN ){
        return true;
    }

    return false;
}


