/**
 * C sample
 * 2020-03-01 K.OHWADA
 */


// display current time
// since C11
// reference : https://en.cppreference.com/w/c/chrono/timespec_get


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 *  printGmTime
 */
void printGmTime(long time)
{
  struct tm* gm;
    char buff[100];

    gm = gmtime(&time);
    strftime(buff, sizeof buff, "%Y-%m-%d (%a) %T %Z", gm);
    printf("Time: %s \n", buff);
}


/**
 * printJstTime
 */
void printJstTime(long time)
{
  char* WEEK[] = {"日", "月", "火", "水", "木", "金", "土"};

    char buff[100];

  struct tm* jst;
  jst = localtime(&time);

    strftime(buff, sizeof buff, "時刻: %Y-%m-%d (%%s) %T %Z \n", jst);
    printf(buff, WEEK[jst->tm_wday] );
}


/**
 * main
 */
int main(void) 
{

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    printf("timespec: %ld (sec) : %ld (nsec) \n", ts.tv_sec, ts.tv_nsec);

    printGmTime(ts.tv_sec);
    printJstTime(ts.tv_sec);

// timespec: 1597124880 (sec) ; 247937000 (nsec) 
// Time: 2020-08-11 (Tue) 05:48:00 UTC 
// 時刻: 2020-08-11 (火) 14:48:00 JST 

    return EXIT_SUCCESS;
}
