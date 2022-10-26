#pragma once
/**
 *  response_builder.h
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
#include "date.h"

// prototype
void build_headers(char* mime, char* headers);


/**
 *  build_headers
 */
void build_headers(char* mime, char* headers)
{
    const char FORMAT_CONTENT_TYPE[] = 
"Content-Type: %s \r\n";

    const char FORMAT_DATE[] = "Date: %s \r\n";

    const size_t BUFSIZE = 512;
    char  header_contect_type[BUFSIZE];
    char header_date[BUFSIZE];
    char date[BUFSIZE];

    snprintf( (char *)header_contect_type, BUFSIZE, 
    (char *)FORMAT_CONTENT_TYPE, mime );

    get_date_rfc5322( (char *)date);

    snprintf( (char *)header_date, BUFSIZE, 
    (char *)FORMAT_DATE, (char *)date );

    strcpy(headers, (char *)header_date);
    strcat(headers, (char *)header_contect_type);
}

/**
 *   get_date
 */
void get_date(char* datetime)
{
// RFC5322 format
// Sun, 06 Nov 1994 08:49:37 GMT

    const char FORMAT[] = "%a, %d %b %Y %H:%M:%S GMT";

    const size_t BUFSIZE = 128;
    char buf[BUFSIZE];

    time_t now = time(NULL);

    struct tm *tm_now = gmtime(&now);

    strftime( ( char *)buf, BUFSIZE, (char *)FORMAT, tm_now);

    strcpy(datetime, buf );
}

