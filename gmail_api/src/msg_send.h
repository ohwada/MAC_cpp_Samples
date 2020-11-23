#pragma once
/**
 * Gmal API sample
 * 2020-07-01 K.OHWADA
 */

// build send message

#include <stdio.h>
#include <string.h>
#include <unistd.h>


// constant
const char CONTENT_TYPE_TEXT_USASCII[] = "Content-Type: text/plain; charset=us-ascii\r\n";

const char CONTENT_TRANSFER_7BIT[] = "Content-Transfer-Encoding: 7bit\r\n";


// prototype
void buildMessage(char* subject, char* from, char* to, char* msg);
char* getDate(void);
char* getMessageID(void);
void printMessage(char *msg);


/**
 * buildMessage
 * RFC 2822 format
 * http://srgia.com/docs/rfc2822j.html
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

}


/**
 * getDate
 */
char* getDate(void)
{

// RFC 822
// (wday), dd MMM YYYY HH:mm:ss +0900
// Thu, 04 Apr 2014 12:35:20 +0900

    const char* FORMAT = "%a, %d %b %Y %H:%M:%S %z";

    const size_t BUFSIZE = 256;
    static char buf[BUFSIZE];

    time_t now = time(NULL);

    struct tm tm; 
    localtime_r(&now,&tm);

    strftime(buf, BUFSIZE, FORMAT, &tm);

    return buf;
}



/**
 * getMessageID
 */
char* getMessageID(void)
{
    const size_t BUF_SIZE = 256;
    static char buf[BUF_SIZE];

    time_t now = time(NULL);

    struct tm tm; 
    localtime_r(&now,&tm);


    const size_t HOSTNAME_SIZE = 256;
    char hostname[HOSTNAME_SIZE]; 

// function 'gethostname' is invalid in C99
    gethostname(hostname,  HOSTNAME_SIZE);

    const char* FORMAT = "%d%02d%02d%02d%02d%02d.%s";

    snprintf(buf, BUF_SIZE, 
        (char *)FORMAT,
        ( tm.tm_year+1900 ),
        (tm.tm_mon+1),
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        hostname);

    return buf;
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

