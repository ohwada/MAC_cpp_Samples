/**
 * C time sample
 * 2020-03-01 K.OHWADA
 */

//  RFC822 / ISO 8601datetime

#include <stdio.h>
#include <time.h>


// prototype
char* getDateRfc822(void);
char* getDateIso8601(void);
char* getFormatedDate(char *format);


/**
 * getDateRfc822
 */
char* getDateRfc822(void)
{

// RFC 822
// (wday), dd MMM YYYY HH:mm:ss +0900
// Thu, 04 Apr 2014 12:35:20 +0900

    const char* FORMAT = "%a, %d %b %Y %H:%M:%S %z";

    return getFormatedDate( (char *)FORMAT );

}



/**
 * getDateIso8601
 */
char* getDateIso8601(void)
{

// ISO 8601
// YYYYMMDDThhmmss+0900
// 20201017T234436+0900

    const char* FORMAT = "%Y%m%dT%H%M%S%z";

   return getFormatedDate( (char *)FORMAT );

}


/**
 * getFormatedDate
 */
char* getFormatedDate(char *format)
{

    const size_t BUFSIZE = 256;
    static char buf[BUFSIZE];

    time_t now = time(NULL);

    struct tm tm; 
    localtime_r(&now,&tm);

    strftime(buf, BUFSIZE, format, &tm);

    return buf;
}

