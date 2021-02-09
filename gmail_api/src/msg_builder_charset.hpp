#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// message build utility


#include <string>
#include <stdlib.h>
#include "msg_builder.hpp"
#include "base64.hpp"


// constant
const std::string CHARSET_UTF8("utf-8");
const std::string CHARSET_ISO2022JP("iso-2022-jp");


// prototype
void buildMessageUtf8( std::string subject,  std::string to, std::string from, std::string body,  std::string &msg );
void buildMessageCharset( std::string subject,  std::string to, std::string from, std::string body,   std::string charset,  std::string &ret_msg );
void buildSubjectB64( std::string subject, std::string charset, std::string &subject_b64 );
void buildFormatB64(char *b64, char *charset, char *formated, size_t formated_size );
void getContentTypeTextPlainCharset( std::string charset, std::string &ret_content_type );
void buildContentTypeTextPlainCharset(char *charset, 
char *content_type,  size_t  content_type_size );


/**
 * buildMessageUtf8
 */
void buildMessageUtf8( std::string subject,  std::string to, std::string from, std::string body,  std::string &msg )
{
    buildMessageCharset( subject,  to, from, body,   CHARSET_UTF8,  msg );
}


/**
 * buildMessageCharset
 */
void buildMessageCharset( std::string subject,  std::string to, std::string from, std::string body,   std::string charset,  std::string &msg )
{

    const std::string CONTENT_TYPE_TEXT_PLANE_UTF8(
    "Content-Type: text/plain; charset=utf-8; \r\n");

    const std::string CONTENT_TRANSFER_BASE64(
    "Content-Transfer-Encoding: base64\r\n") ;


    std::string subject_b64;

    buildSubjectB64( subject, charset, subject_b64 );

    std::string headers;
    buildHeaders(subject_b64, to, from,  headers);

    std::string body_b64;
    encodeB64( body, body_b64 );

    std::string content_type;
    getContentTypeTextPlainCharset( charset, content_type );


// build msg
    msg += headers;

    msg += content_type;

    msg +=  CONTENT_TRANSFER_BASE64;

    msg += CRLF;  // separater

    msg += body_b64;

    msg += CRLF;

}


/**
* buildSubjectB64
 */
void buildSubjectB64( std::string subject, std::string charset, std::string &subject_b64 )
{

    const size_t B64_FORMATED_SIZE = 200;

    std::string b64;
    encodeB64(subject, b64);

    char formated[B64_FORMATED_SIZE];

    buildFormatB64( 
    (char *)b64.c_str(),
    (char *)charset.c_str(), 
    (char *)formated,
    B64_FORMATED_SIZE );

    subject_b64 = std::string(formated);
    
}


/**
 *   buildFormatB64
 */
void buildFormatB64(char *b64, char *charset, char *formated, size_t formated_size )
{

    const char FORMAT_B64_CHARSET[] = 
    "=?%s?B?%s?="; 

    snprintf( formated, formated_size,  (char *)FORMAT_B64_CHARSET, charset, b64 );
}


/**
 *   getContentTypeTextPlainCharset
 */
void getContentTypeTextPlainCharset( std::string charset, std::string &ret_content_type )
{

    const size_t HEADER_SIZE = 200;
    char content_type[HEADER_SIZE];

    buildContentTypeTextPlainCharset( 
    (char *)charset.c_str(), 
    (char *)content_type, 
    HEADER_SIZE );

    ret_content_type = std::string(content_type );

}


/**
 *   buildContentTypeTextPlainCharset
 */
void buildContentTypeTextPlainCharset(char *charset, char *content_type, size_t content_type_size )
{

    const char FORMAT_CONTENT_TYPE_TEXT_PLANE_CHARSET[] =
    "Content-Type: text/plain; charset=%s; \r\n";

    snprintf( content_type, content_type_size,  (char *)FORMAT_CONTENT_TYPE_TEXT_PLANE_CHARSET, charset );

}