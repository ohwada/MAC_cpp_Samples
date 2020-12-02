#pragma once
/**
 *  network sample
 * 2020-07-01 K.OHWADA
 */

// function for  smtp client message

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// constant
const char HELO_FORMAT[] = "HELO %s \r\n";
 
const char MAIL_FROM_FORMAT[] = "MAIL FROM: %s \r\n";

const char RCPT_TO_FORMAT[] = "RCPT TO: %s \r\n";

const char CMD_DATA[] = "DATA\r\n";

const char FROM_FORMAT[] = "From: %s \r\n";

const char TO_FORMAT[] = "To: %s \r\n";

const char END_OF_MESSAGE[] = ".\r\n";

const char CMD_QUIT[] = "QUIT\r\n";

const char CRLF[] = "\r\n";


// prototype
void buildMessage(char *from, char *to, char *subject, char *body, char *message);
char* getDate(void);
char* getMessageID(void);


/**
 * buildMessage
 * RFC 2822 format
 */
void buildMessage(char *from, char *to, char *subject, char *body, char *message)
{

const size_t BUFSIZE = 100;
char buf[BUFSIZE];

// date
    snprintf(buf, BUFSIZE, "Date: %s \r\n",  getDate() );
    strcat(message, buf);

//  MessageID
    snprintf(buf, BUFSIZE, "Message-Id: %s \r\n",   getMessageID() );
    strcat(message, buf);

// from
    snprintf(buf, BUFSIZE, "From: %s \r\n", from);
    strcat(message, buf);

// to
    snprintf(buf, BUFSIZE, "To: %s \r\n", to);
    strcat(message, buf);

// subject
    snprintf(buf, BUFSIZE, "Subject: %s \r\n", subject);
    strcat(message, buf);

// split body
    strcat(message, (char *)CRLF );

// body
    strcat(message, body);

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

