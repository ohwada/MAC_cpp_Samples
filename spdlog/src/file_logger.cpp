/**
 * file_logger.cpp
 * 2022-06-01 K.OHWADA
 */

// Basic file logger
// https://github.com/gabime/spdlog

#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"


/**
 * basic_logfile_example
 */
void basic_logfile_example()
{
    std::string name("basic_logger");
    std::string file("logs/basic-log.txt");
    try 
    {
        auto logger = spdlog::basic_logger_mt(name, file);
        logger->info("hello");
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
}

// using namespace std;


/**
 * main
 */
int main() 
{
    basic_logfile_example();

    return 0;
}

// [basic_logger] [info] hello
// in "logs/basic-log.txt"
