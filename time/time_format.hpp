#pragma once
/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// get formated local time
// reference : http://www.cplusplus.com/reference/ctime/localtime/


#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>


// prototype
std::time_t getNow(void);
void formatGmTimeNow(std::string format, std::string &str );
void formatJstTimeNow(std::string format, std::string &str );
void formatGmTime( std::string format, std::time_t, std::string &str );
void formatJstTime(std::string  format, std::time_t t, std::string &str );
bool getWeekJp(int wday, std::string &str);


/**
 *   getNow
 */
std::time_t getNow(void)
{
    return std::time(nullptr);
}


/**
 *   formatGmTimenow
 */
void formatGmTimeNow( std::string format, std::string &str1 )
{
    std::string str2;
    formatGmTime( format,  getNow(), str2 );
    str1 = str2;
    return;
}


/**
 *   formatJstTimeNow
 */
void formatJstTimeNow(std::string format, std::string &str1 )
{
    std::string str2;
    formatJstTime( format,  getNow(), str2 );
    str1 = str2;
    return;
}


/**
 *   formatGmTime
 */
void formatGmTime( std::string  format, std::time_t t, std::string &str )
{

    std::ostringstream oss;
    oss <<  std::put_time( gmtime(&t), (char *)format.c_str() );

    str = oss.str();
    return;
}


/**
 *   formatJstTime
 */
void  formatJstTime( std::string  format, std::time_t t, std::string &str )
{

    std::ostringstream oss;
    oss <<  std::put_time( localtime(&t), (char *)format.c_str() );

    str = oss.str();
    return;
}
 

/**
 *   getWeekJp
 */
bool getWeekJp(int wday, std::string &str)
{

    const std::vector<std::string> WEEK_JP = {"日", "月", "火", "水", "木", "金", "土"};

    const size_t size = WEEK_JP.size();

    bool ret = false;

    if( (wday >= 0)&&( wday < size) ) {
        str = WEEK_JP[wday];
        ret = true;
    } else {
        str = "";
    }

    return ret;
}
