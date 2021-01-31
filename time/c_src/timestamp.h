#pragma once
/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// time utility

#include <string.h>
#include <time.h>


// prototype
void getTimestampFileName( char *prefix, char *ext,  char *filename);
void getTimestamp(char *timestamp);


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