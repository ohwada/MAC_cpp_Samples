#pragma once
/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// get formated local time
// reference : http://www.cplusplus.com/reference/ctime/localtime/


#include <string>
#include <vector>
#include <ctime>


// prototype
std::time_t getNow(void);
void formatTime(std::string format , std::tm* tm, std::string &str );
void formatGmtimeNow(std::string format, std::string &str );
void formatLocalimeNow(std::string format, std::string &str );
void formatGmtime( std::string format, std::time_t, std::string &str );
void formatLocalime(std::string  format, std::time_t t, std::string &str );
bool getWeekJp(int wday, std::string &str);


/**
 *   getNow
 */
std::time_t getNow(void)
{
    return std::time(nullptr);
}


/**
 * formatTime
 */
void formatTime(std::string format , std::tm* tm, std::string &str ) 
{
    size_t BUFSIZE = 100;
    char buf[BUFSIZE];
    std::strftime(buf, BUFSIZE, (char *)format.c_str(), tm);
    str = buf;
  return ;
}


/**
 *   formatGmtimenow
 */
void formatGmtimeNow( std::string format, std::string &str1 )
{
    std::string str2;
    formatGmtime( format,  getNow(), str2 );
    str1 = str2;
    return;
}


/**
 *   formatLocalimeNow
 */
void formatLocalimeNow(std::string format, std::string &str1 )
{
    std::string str2;
    formatLocalime( format,  getNow(), str2 );
    str1 = str2;
    return;
}


/**
 *   formatGmtime
 */
void formatGmtime( std::string  format, std::time_t t, std::string &str1 )
{

    std::string str2;
    formatTime(format , std::gmtime(&t), str2 ); 

    str1 = str2;
    return;
}


/**
 *   formatLocalime
 */
void  formatLocalime( std::string  format, std::time_t t, std::string &str1)
{

    std::string str2;
    formatTime(format , std::localtime(&t), str2 ); 

    str1 = str2;
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
