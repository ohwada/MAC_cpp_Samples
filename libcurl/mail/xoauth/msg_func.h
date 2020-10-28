#pragma once
/**
 * libcurl Sample
 * 2020-07-01 K.OHWADA
 */

// function for  send message

#include <stdio.h>
#include <string.h>
#include <unistd.h>



// prototype
char* getDate(void);
char* getMessageID(void);
char* getMailer(void);


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
 * getMailer
 */
char* getMailer(void)
{
    const size_t BUFSIZE = 100;
    static char buff[BUFSIZE];
    snprintf( buff, BUFSIZE, "libcurl %s",  LIBCURL_VERSION );
    return buff;
}
