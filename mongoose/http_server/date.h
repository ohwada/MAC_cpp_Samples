#pragma once
/**
 *  date.h
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// prototype
void get_date_rfc5322(char* datetime);



/**
 *   get_date_rfc5322
 */
void get_date_rfc5322(char* datetime)
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


