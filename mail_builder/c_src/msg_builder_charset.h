#pragma once
/**
 *  smtp client sample
 * 2021-02-01 K.OHWADA
 */

// build build message


#include "msg_builder.h"
#include "base64.h"


// constant
const char CHARSET_UTF8[] = "utf-8";
const char CHARSET_ISO2022JP[] = "iso-2022-jp";


// prototype
void buildMessageUtf8( char *subject, char *to, char *from,  char *body, char *msg );
void buildMessageCharset( char *subject, char *to, char *from,  char *body, char *charset, char *msg );
void base64encode(char *encoded, const char *string, size_t encoded_size );
void buildContentTypeTextPlainCharset(char *charset, char *content_type, size_t content_type_size );
void buildFormatB64Charset( char *b64, char *charset, char *formatted, size_t formatted_size );


/**
 * buildMessageUtf8
 */
void buildMessageUtf8( char *subject,  char *to, char *from, char *body,  char *msg )
{
    buildMessageCharset( subject,  to, from, body,   
    (char *)CHARSET_UTF8, msg );
}


/**
 * buildMessageCharset
 */
void buildMessageCharset( char *subject,  char *to, char *from, char *body,   char *charset, char *msg )
{

    const size_t ENCODED_SIZE = 1024;

    const size_t formatted_SIZE = 200;

    const size_t HEADER_SIZE = 200;

    const char CONTENT_TRANSFER_BASE64[] = 
    "Content-Transfer-Encoding: base64\r\n" ;



    char subject_b64[ENCODED_SIZE];

    base64encode( (char *)subject_b64, (char *)subject, ENCODED_SIZE );


    char subject_formatted[formatted_SIZE];

    buildFormatB64Charset( 
    (char *)subject_b64,  charset, 
    (char *)subject_formatted, 
    formatted_SIZE );


    char body_b64[ENCODED_SIZE];

    base64encode( (char *)body_b64, (char *)body, ENCODED_SIZE );

    char headers[HEADERS_SIZE];

    buildHeaders( 
    (char *)subject_formatted, 
    (char *)to, 
    (char *)from,  
    (char *)headers );

    char content_type[HEADER_SIZE];
    buildContentTypeTextPlainCharset( charset, 
    (char *)content_type, HEADER_SIZE );

    strcpy(msg, (char *)headers);

    strcat(msg, (char *)content_type );

    strcat(msg, (char *)CONTENT_TRANSFER_BASE64 );

    strcat(msg, (char *)CRLF );  // separater

    strcat(msg, (char *)body_b64 );

     strcat(msg, (char *)CRLF );

}


/**
 * base64encode
 */
void base64encode(char *encoded, const char *string, size_t encoded_size )
{

    const char CHAR_NULL = '\0';

// clrear buffer
    for(int i=0; i<encoded_size; i++){
        encoded[i] = CHAR_NULL;
    }

    int len = strlen(string);
    Base64encode( encoded, string, len );

}


/**
 *   buildFormatB64Charset
 */
void buildFormatB64Charset( char *b64, char *charset, char *formatted, size_t formatted_size )
{
    const char FORMAT_B64_CHARSET[] = 
    "=?%s?B?%s?="; 

    snprintf( formatted, formatted_size,  
    (char *)FORMAT_B64_CHARSET, charset, b64 );

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
