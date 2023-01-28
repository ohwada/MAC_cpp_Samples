/**
 * stdout_logger.cpp
 * 2022-06-01 K.OHWADA
 */

// Create stdout/stderr logger object
// https://github.com/gabime/spdlog

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


/**
 * stdout_example
 */
void stdout_example()
{
    // create color multi threaded logger
    auto console = spdlog::stdout_color_mt("console");    
    auto err_logger = spdlog::stderr_color_mt("stderr");    
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
}

// using namespace std;


/**
 * main
 */
int main() 
{
    stdout_example();

    return 0;
}

// [console] [info] loggers can be retrieved from a global registry using the spdlog::get(logger_name)
