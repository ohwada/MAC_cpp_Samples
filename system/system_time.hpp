#pragma once
/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// get formated local time
// reference : https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm

#include<string>
#include <chrono>
#include <ctime>

// prototype
std::time_t getNow(void);
std::string formatGmTimeNow(std::string format );
std::string formatJstTimeNow(std::string format );
char* formatGmTime(char* format, std::time_t );
char* formatJstTime(char* format, std::time_t t );
char* getWeekJp(int wday);


/**
 *   getNow
 */
std::time_t getNow(void)
{

 	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();

  	std::time_t t = std::chrono::system_clock::to_time_t(p);
	return t;
}


/**
 *   formatGmTimenow
 */
std::string formatGmTimeNow( std::string format )
{
    static char* time;
    time = formatGmTime( (char *)format.c_str(),  getNow() );

    return std::string(time);
}

/**
 *   formatJstTimeNow
 */
std::string formatJstTimeNow(std::string format )
{
    static char* time;
    time = formatJstTime( (char *)format.c_str(),  getNow() );

    return std::string(time);
}

/**
 *   formatGmTime
 */
char* formatGmTime( char* format, std::time_t t )
{

	const  size_t bufsize = 100;
    static char buff[bufsize];

    struct tm* gm;
    gm = gmtime(&t);

    strftime(buff, bufsize, format, gm);

    return buff;
}


/**
 *   formatJstTime
 */
char*  formatJstTime(char* format, std::time_t t )
{

	 const size_t  bufsize = 100;
    static char buff[bufsize];

    struct tm* jst;
    jst = localtime(&t);

    strftime(buff, bufsize, format, jst);

    return buff;
}
 

/**
 *   getWeekJp
 */
 char* getWeekJp(int wday)
{

    const char* WEEK_JP[] = {"日", "月", "火", "水", "木", "金", "土"};

    static char* week;
    if( (wday >= 0)&&( wday < 7) ) {
        week = (char *)WEEK_JP[wday];
    } else {
        week = (char *)"";
    }

    return week;
}
