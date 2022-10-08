#pragma once
/**
 * file_timestamp.h
 * 2022-06-01 K.OHWADA
 */


#include <stdlib.h>
#include <string.h>
#include <time.h>

// prototype
void get_timestamp_filename(char* prefix, char* ext, char* filename);
void get_timestamp(char* timestamp);



/** 
 *  get_timestamp_filename
  */ 
void get_timestamp_filename(char* prefix, char* ext, char* filename)
{
    const size_t BUFSIZE = 128;
    char timestamp[BUFSIZE];
    char buf[BUFSIZE];

    get_timestamp( (char *)timestamp );

    const char FORMAT[] = "%s_%s.%s";

    snprintf( (char *)buf, BUFSIZE, (char *)FORMAT, prefix, (char *)timestamp, ext);

    strcpy(filename, buf);

}


/** 
 *   getTimestamp
 */
void get_timestamp(char* timestamp)
{

    const char FORMAT[] = "%Y%m%d%H%M%S";

    const size_t BUFSIZE = 128;
    char buf[BUFSIZE];

    time_t now = time(NULL);

    struct tm *tm_now = localtime(&now);

    strftime( ( char *)buf, BUFSIZE, (char *)FORMAT, tm_now);

        strcpy(timestamp, buf );
}



