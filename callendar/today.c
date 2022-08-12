/**
 * today.c
 * display RFC822 format 
 * 2020-03-01 K.OHWADA
 */

// gcc today.c

#include <stdio.h>
#include <time.h>


/**
 * main
 */
int main(void)
{
   const size_t BUFSIZE = 256;
    char buf[BUFSIZE];

// RFC 822
// (wday), dd MMM YYYY HH:mm:ss +0900
// Thu, 04 Apr 2014 12:35:20 +0900
    const char* FORMAT = "%a, %d %b %Y %H:%M:%S %z";

    time_t now = time(NULL);

    struct tm tm; 
    localtime_r(&now, &tm);

    strftime(buf, BUFSIZE, FORMAT, &tm);

    printf("%s \n", buf);

    return 0;
}

// Thu, 11 Aug 2022 08:33:40 +0900 

