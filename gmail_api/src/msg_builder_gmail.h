#pragma once
/**
 * Gmal API sample
 * 2020-07-01 K.OHWADA
 */

// build send message


 #include "msg_builder.h"


// prototype
void buildDefaultBody(char *body);
char* getCurlVersion(void);


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

