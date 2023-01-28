/**
 * daily_files.cpp
 * 2022-06-01 K.OHWADA
 */

// Daily files
// https://github.com/gabime/spdlog

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"


/**
 * daily_example
 */
void daily_example()
{
    // Create a daily logger - a new file is created every day on 2:30am
    auto logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt", 2, 30);
}

// using namespace std;


/**
 * main
 */
int main() 
{
    daily_example();

    return 0;
}

