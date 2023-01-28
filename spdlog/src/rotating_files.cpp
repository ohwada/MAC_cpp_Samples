/**
 * rotating_files.cpp
 * 2022-06-01 K.OHWADA
 */

// Rotating files
// https://github.com/gabime/spdlog

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"


/**
 * rotating_example
 */
void rotating_example()
{
    // Create a file rotating logger with 5mb size max and 3 rotated files
    auto max_size = 1048576 * 5;
    auto max_files = 3;
    auto logger = spdlog::rotating_logger_mt("some_logger_name", "logs/rotating.txt", max_size, max_files);
}

// using namespace std;


/**
 * main
 */
int main() 
{
    rotating_example();

    return 0;
}
