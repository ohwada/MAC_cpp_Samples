#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// message build utility



#include <string>
#include "msg_builder.h"



// prototype
void buildMessageText(std::string subject, std::string to, std::string from, std::string body, std::string &msg);
void buildHeaders(std::string subject, std::string to, std::string from,  std::string &msg);
void saveMessage(std::string msg);
void printMessage(std::string msg) ;




/**
 * buildMessage
 * RFC 2822 format
 * http://srgia.com/docs/rfc2822j.html
 */
void buildMessageText(std::string subject, std::string to, std::string from, std::string body, std::string &msg)
{

    std::string  headers;
    buildHeaders(subject, to,  from,  headers);

    msg = headers;
    msg += CONTENT_TYPE_TEXT_PLANE_USASCII;
    msg += CONTENT_TRANSFER_7BIT;

    msg += CRLF;  // separetor

    msg += body + CRLF;

}


/**
 *  buildHeaders
 */
void buildHeaders(std::string subject, std::string to, std::string from,  std::string &ret_headers)
{

    char headers[ HEADERS_SIZE];

    buildHeaders(
    (char *)subject.c_str(), 
    (char *)to.c_str(), 
    (char *)from.c_str(), 
    (char *)headers );

    ret_headers = std::string(headers);

}


/**
 * printMessage
 */
void printMessage(std::string msg) 
{
        printMsg( (char *)msg.c_str() );
}


/**
 * saveMessage
 */
void saveMessage(std::string msg)
{
    saveMsg( (char *)msg.c_str() );
}

