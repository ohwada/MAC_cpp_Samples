#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// build build message

#include <stdio.h>
#include <stdlib.h>
 #include <stdbool.h>
 #include <string.h>
 #include <time.h>
#include <errno.h> 
#include <unistd.h>


// constant
const size_t MSG_SIZE = 1024;
const size_t BODY_SIZE = 512;
const size_t HEADER_SIZE = 200;
const size_t HEADERS_SIZE = 1024;
const char CRLF[] = "\r\n";
const char MIME_VER[] ="Mime-Version: 1.0\r\n" ;
const char CONTENT_TYPE_TEXT_PLANE_USASCII[] =
"Content-Type: text/plain; charset=us-ascii; \r\n";
const char CONTENT_TRANSFER_7BIT[] = "Content-Transfer-Encoding: 7bit\r\n";


// prototype
void buildMsgText(char* subject, char* to, char* from, char *body, char* msg);
void buildHeaders(char* subject, char* to, char* from, char* msg);
char* getDate(void);
char* getMessageID(void);
bool saveMsg( char* msg );
void printMsg( char *msg );
void getTimestampFileName( char *prefix, char *ext,  char *filename);
void getTimestamp(char *timestamp);
bool write_text_file(char* file, char* data, char *error);




/**
 * buildMsgText
 * RFC 2822 format
 */
void buildMsgText(char* subject, char* to, char* from, char *body, char* msg)
{

// headers
    char headers[ HEADERS_SIZE];
    buildHeaders( subject,  to,  from, (char *)headers );

    strcpy(msg,  (char *)headers );

    strcat(msg, (char *)CONTENT_TYPE_TEXT_PLANE_USASCII );

    strcat(msg, (char *)CONTENT_TRANSFER_7BIT );

// heder part end
    strcat(msg,  CRLF); 

// body
    strcat( msg, body );

    strcat(msg,  CRLF);

}


/**
 * buildHeaders
 */
void buildHeaders(char* subject, char* to, char* from, char* msg)
{

    char buf[HEADER_SIZE];

// headers
     snprintf(buf, HEADER_SIZE, "Subject: %s\r\n", subject);
    strcpy(msg, buf);

    snprintf(buf, HEADER_SIZE, "To: %s\r\n",  to);
    strcat(msg, buf);

    snprintf(buf, HEADER_SIZE, "From: %s\r\n", from);
    strcat(msg, buf);

    snprintf(buf, HEADER_SIZE, "Date: %s\r\n", getDate());
    strcat(msg, buf);

    snprintf(buf, HEADER_SIZE, "Message-ID: <%s>\r\n", getMessageID());
    strcat(msg, buf);

    strcat(msg, (char *)MIME_VER);

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
 * saveMsg
 */
bool saveMsg( char* msg )
{

    const char prefix[] = "mail";
    const char ext[] = "eml";

    char file[100];

    getTimestampFileName( (char *)prefix,  (char *)ext,  (char *)file );

    char error[100];

    bool ret = write_text_file( file, msg, (char *)error );

    if(ret){
        printf("saved to: %s \n", file);
    } else {
        printf("%s \n", error);
    }

    return ret;
}


/**
 * printMsg
 */
void printMsg(char *msg)
{
    printf("\n");
    printf("----- \n");
    printf("%s \n", msg);
    printf("----- \n");
}


/** 
 *  getTimestampFileName
  */ 
void getTimestampFileName( char *prefix, char *ext,  char *filename)
{

    const char UNDERBAR[] = "_";
    const char DOT[] = ".";

    char timestamp[100];

    getTimestamp( timestamp );

    strcpy(filename,  prefix);
    strcat(filename,  UNDERBAR);
    strcat(filename,  timestamp);
    strcat(filename,  DOT);
    strcat(filename,  ext);

}


/** 
 *   getTimestamp
 */
void getTimestamp(char *timestamp)
{

    const char FORMAT[] = "%Y%m%d%H%M%S";

    const size_t BUFSIZE = 100;
    static char buf[BUFSIZE];

    time_t now = time(NULL);

    struct tm tm; 
    localtime_r(&now,&tm);

    strftime(buf, BUFSIZE, FORMAT, &tm);

    strcpy(timestamp, buf);

}


/**
 * write_text_file
 */
bool write_text_file(char* file, char* data, char *error)
{

    FILE *fp;
    int saved_errno;
    bool res;

    fp = fopen(file, "w");
    if(!fp) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return false;
    }

    int ret = fputs( data , fp );
    if( ret == EOF ) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        res = false;
    } else {
        res = true;
    }

    fclose(fp);
    return res;
}


