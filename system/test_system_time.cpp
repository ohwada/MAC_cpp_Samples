/**
 * C++ system sample
 * 2020-03-01 K.OHWADA
 */

// test for system_time.hpp

#include <iostream>
#include "system_time.hpp"

using namespace std;


/**
 * getJstTime
 */
string getJstTimeNow()
{

    const size_t formatsize = 100;
    char format[formatsize ];

    const size_t bufsize = 100;
    static char buff[bufsize];

    const char timeformat[] = "%Y-%m-%d (%%s) %T %Z";

    std::time_t now = getNow();
  struct tm* jst;
  jst = localtime(&now);

    strftime(format, formatsize , timeformat, jst);

    char * week = getWeekJp( jst->tm_wday );
    snprintf(buff,  bufsize, format,  week );

    return string(buff);
}


/**
 * main
 */
int main(void)
{

    string format = "%Y_%m_%d_%H_%M_%S";

    string gmformat = "%Y-%m-%d (%a) %T %Z";

    string gmtime = formatGmTimeNow(gmformat);

    string jsttime = getJstTimeNow();

    string format_gmtime = formatGmTimeNow(format);

    string format_jsttime = formatJstTimeNow(format);

    cout << gmtime << endl;
    cout << jsttime << endl;
    cout <<  "UTC: " << format_gmtime << endl;
    cout << "JST: " << format_jsttime << endl;

    return 0;
}

// 2020-08-29 (Sat) 01:52:03 UTC
// 2020-08-29 (土) 10:52:03 JST
// UTC: 2020_08_29_01_52_03
// JST: 2020_08_29_10_52_03
