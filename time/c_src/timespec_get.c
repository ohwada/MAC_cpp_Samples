/**
 * time sample
 * 2020-10-01 K.OHWADA
 */

// display current time with nanoseconds  
// gcc timespec_get.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/**
 * getJstTime
 */
void getJstTime(long time, char *jsttime)
{

    const int BUFSIZE = 100;
    char buff[BUFSIZE];

    struct tm* jst;
    jst = localtime(&time);

    strftime(buff, BUFSIZE, "%Y-%m-%d %T %Z \n", jst);

    strcpy(jsttime, buff);
}


/**
 * main
 */
int main(void) 
{

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    char time[100];
    getJstTime(  ts.tv_sec, (char *)time );

    printf("timespec: %s \n", time );

    printf("nanosec: %ld (nsec) \n", ts.tv_nsec );

    return EXIT_SUCCESS;
}


// timespec: 2020-11-30 21:18:56 JST 
// nanosec: 474710000 (nsec) 

