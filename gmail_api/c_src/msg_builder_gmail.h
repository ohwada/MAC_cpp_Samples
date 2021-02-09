#pragma once
/**
 * Gmal API sample
 * 2020-07-01 K.OHWADA
 */

// build send message


 #include "msg_builder.h"
#include "base64url.h"


// constant
const size_t REQUEST_SIZE = 10000; // 10KB
const size_t RESPONSE_SIZE = 1000; // 1KB
const size_t TOKEN_SIZE = 200;
const size_t ERROR_SIZE = 100;

// prototype
void buildDefaultBody(char *body);
char* getCurlVersion(void);
void buildRequestJson(char* msg, char* request, size_t size);



/**
 * buildDefaultBody
 */
void buildDefaultBody(char *body)
{

   size_t BUFSIZE = 200;
    char buf[BUFSIZE];

    strcpy(body,  "This is a test e-mail. ");
    strcat(body, (char *)CRLF);
    strcat(body, "This mail was sent using Gmail API ");
    strcat(body, (char *)CRLF);

    snprintf(buf, BUFSIZE, "and %s ", getCurlVersion() );
    strcat(body, (char *)buf);
    strcat(body, (char *)CRLF);

}


/**
 * getCurlVersion
 */
char* getCurlVersion(void)
{
    const size_t BUFSIZE = 100;
    static char buff[BUFSIZE];
    snprintf( buff, BUFSIZE, "libcurl %s",  LIBCURL_VERSION );
    return buff;
}


/**
 * buildRequestJson
 * base64url encoding
 */
void buildRequestJson(char* msg, char* request, size_t size)
{

    char *b64;
    b64 = base64Encode( msg,  strlen(msg),  BASE64_TYPE_URL);

    snprintf(request, size, "{ \"raw\" : \"%s\" }", b64);

    free(b64);
}

