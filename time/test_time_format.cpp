/**
 * C++ system sample
 * 2020-03-01 K.OHWADA
 */

// test for time_format.hpp

#include <iostream>
#include "time_format.hpp"

using namespace std;


/**
 * getJstTimeNowWday
 */
string getJstTimeNowWday()
{

    const size_t BUFSIZE = 100;
    static char buff[BUFSIZE];

    const string FORMAT = "%Y-%m-%d (%%s) %H:%M:%S %Z";

    std::time_t now = getNow();
    struct tm* jst;
    jst = localtime(&now);

    string format;
    formatLocalime( FORMAT, now, format );

    string week; 
    getWeekJp( jst->tm_wday, week );

    snprintf(buff,  BUFSIZE, (char *)format.c_str(),  (char *)week.c_str() );

    return string(buff);
}


/**
 * main
 */
int main(void)
{

    string format = "%Y_%m_%d_%H_%M_%S";

    string gmformat_wday = "%Y-%m-%d (%a) %T %Z";

    string gmtime_wday;
    formatGmtimeNow(gmformat_wday, gmtime_wday);

    string jsttime_wday = getJstTimeNowWday();

    string str_gmtime;
    formatGmtimeNow(format, str_gmtime );

    string str_jsttime; 
    formatLocalimeNow(format, str_jsttime);

    cout << gmtime_wday << endl;
    cout << jsttime_wday << endl;
    cout <<  "UTC: " << str_gmtime << endl;
    cout << "JST: " << str_jsttime << endl;

    return 0;
}


// 2020-08-29 (Sat) 01:52:03 UTC
// 2020-08-29 (土) 10:52:03 JST
// UTC: 2020_08_29_01_52_03
// JST: 2020_08_29_10_52_03
