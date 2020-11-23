#pragma once
/**
 * Gmal API sample
 * 2020-07-01 K.OHWADA
 */

// build send message


 #include "msg_func.h"
 #include "file_util.h"
#include "base64.h"


// constant
const char CONTENT_TYPE_TEXT_USASCII[] = "Content-Type: text/plain; charset=us-ascii\r\n";

const char CONTENT_TRANSFER_7BIT[] = "Content-Transfer-Encoding: 7bit\r\n";


// prototype
void buildMessage(char* subject, char* from, char* to, char* msg);
char* getCurlVersion(void);
void build_send_request_json(char* msg, char* request, size_t size);
bool saveMessage(char* file, char* msg);
void printMessage(char *msg);


/**
 * buildMessage
 * RFC 2822 format
 */
void buildMessage(char* subject, char* from, char* to, char* msg)
{

   size_t BUFSIZE = 100;
    char buf[BUFSIZE];

// headers
     snprintf(buf, BUFSIZE, "Subject: %s\r\n", subject);
    strcpy(msg, buf);

    snprintf(buf, BUFSIZE, "To: %s\r\n",  to);
    strcat(msg, buf);

    snprintf(buf, BUFSIZE, "From: %s\r\n", from);
    strcat(msg, buf);

    snprintf(buf, BUFSIZE, "Date: %s\r\n", getDate());
    strcat(msg, buf);

    snprintf(buf, BUFSIZE, "Message-ID: <%s>\r\n", getMessageID());
    strcat(msg, buf);

    strcat(msg, (char *)CONTENT_TYPE_TEXT_USASCII );

    strcat(msg, (char *)CONTENT_TRANSFER_7BIT );

// heder part end
    strcat(msg, "\r\n");

// body
    strcat(msg,  "This is a test e-mail. \r\n");

    strcat(msg, "This mail was sent using Gmail API \r\n");

    snprintf(buf, BUFSIZE, "and %s \r\n", getCurlVersion() );
    strcat(msg, buf);

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
 * build_send_request_json
 * base64url encoding
 */
void build_send_request_json(char* msg, char* request, size_t size)
{
    char *b64;
    b64 = base64Encode( msg,  strlen(msg),  BASE64_TYPE_URL);

    snprintf(request, size, "{ \"raw\" : \"%s\" }", b64);

    free(b64);
}


/**
 * saveMessage
 */
bool saveMessage(char* file, char* msg)
{
    char error[100];

    bool ret = writeTextFile(file, msg, (char *)error );
    if(ret){
        printf("saved to: %s \n", file);
    } else {
        printf("%s \n", error);
    }

    return ret;

}


/**
 * printMessage
 */
void printMessage(char *msg)
{
    printf("\n");
    printf("----- \n");
    printf("%s \n", msg);
    printf("----- \n");
}

