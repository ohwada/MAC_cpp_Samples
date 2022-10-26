#pragma once
/**
 * http_cookie_server.h
 * 2022-06-01 K.OHWADA
 */

// function for HTTP Server


#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "http_server.h"
#include "response_builder.h"
#include "date.h"


// prototype
void build_cookie_response(char *text, char* mime, int visits, char *response);
void build_cookie_header(int length, char* mime, 
char* cookie_value, char *header);
void build_header_set_cookie(char* name, char* value, char *path,  char* expires, char* header);
void get_expires(char* datetime);
void build_msg_visits(int visits, char* msg);


/**
 *  build_response
 */
void build_cookie_response(char *text, char* mime, int visits, char *response)
{
    const char CRLF[] = "\r\n";

    const size_t BUFSIZE = 512;
    char header[BUFSIZE];
    char cookie_value[BUFSIZE];

    int length = strlen(text);

    const char FORMAT[] = "%d";
    snprintf( cookie_value, BUFSIZE, (char *)FORMAT, visits);

    build_cookie_header(length, mime, (char *)cookie_value, (char *)header);


    strcpy( (char *)response,  (char *)header );
    strcat( (char *)response, (char *)CRLF);
    strcat( (char *)response, text);
    strcat( (char *)response, (char *)CRLF);
}


/**
 *  build_header
 */
void build_cookie_header(int length, char* mime,  char* cookie_value,
char *header)
{

    const char HEADER_OK[] = "HTTP/1.1 200 OK\r\n";

    const char FORMAT_CONTENT_TYPE[] = "Content-Type: %s \r\n";

    const char FORMAT_CONTENT_LENGTH[] = "Content-Length: %d \r\n";

      const char FORMAT_DATE[] = "Date: %s \r\n";

    const size_t BUFSIZE = 512;
    char header_content_type[BUFSIZE];
    char header_content_length[BUFSIZE];
   char header_date[BUFSIZE];
   char date[BUFSIZE];
    char header_set_cookie[BUFSIZE];
   char expires[BUFSIZE];

    snprintf( header_content_type, BUFSIZE, 
    (char *)FORMAT_CONTENT_TYPE, mime );

    snprintf( header_content_length, BUFSIZE, 
    (char *)FORMAT_CONTENT_LENGTH, length );

   get_date_rfc5322( (char *)date);

    snprintf( header_date, BUFSIZE, 
    (char *)FORMAT_DATE, (char *)date );

    char* name = "visits";
    char* path = "/";

    get_expires( (char *)expires);

    build_header_set_cookie(name, cookie_value, path,  (char *) expires, (char *)header_set_cookie);

    strcpy( (char *)header, (char *)HEADER_OK );
    strcat( (char *)header,  (char *) header_date );
    strcat( (char *)header,  (char *) header_set_cookie );
    strcat( (char *)header,  (char *) header_content_type );
    strcat( (char *)header, (char *)header_content_length );
}


/**
 *   build_header_cookie
 */
void build_header_set_cookie(char* name, char* value, char *path,  char* expires, char* header)
{
   const char FORMAT_SET_COOKIE[] = 
"Set-Cookie: %s=%s; path=%s; expires=%s \n";

    const size_t BUFSIZE = 512;
    char buf[BUFSIZE];


    snprintf(buf, BUFSIZE, FORMAT_SET_COOKIE, name, value, path, expires);

    strcpy(header, buf);
}


/**
 *   et_expires
 */
void get_expires(char* datetime)
{
// RFC5322 format
// Sun, 06 Nov 1994 08:49:37 GMT

    const char FORMAT[] = "%a, %d %b %Y %H:%M:%S GMT";

    const long ONE_YEAR = 365*24*3600;

    const size_t BUFSIZE = 128;
    char buf[BUFSIZE];

    time_t now = time(NULL);
    long expire = now + ONE_YEAR;

    struct tm *tm_expire = gmtime(&expire);

    strftime( ( char *)buf, BUFSIZE, (char *)FORMAT, tm_expire);

    strcpy(datetime, buf );
}


/**
 *  build_msg_visits
 */
void build_msg_visits(int visits, char* msg)
{
    const char FORMAT[] =
"<html><head></head><body><h1>Cookie Server demo</h1><font size='+2'>Your Visits: %d<br/></font></body></html>";

const size_t BUFSIZE = 512;
char buf[BUFSIZE];

    snprintf( (char *)buf, BUFSIZE, (char *)FORMAT, visits);

    strcpy(msg, buf);
}
