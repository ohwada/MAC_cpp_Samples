/**
 * basic.c
 * 2022-10-01 K.OHWADA
 */

// Basic usage
// https://github.com/odygrd/quill

#include "quill/Quill.h"


/**
 * main
 */
int main()
{
  //quill::enable_console_colours();
  quill::start();

  quill::Logger* logger = quill::get_logger();
  logger->set_log_level(quill::LogLevel::TraceL3);

  // enable a backtrace that will get flushed when we log CRITICAL
  logger->init_backtrace(2, quill::LogLevel::Critical);

  LOG_BACKTRACE(logger, "Backtrace log {}", 1);
  LOG_BACKTRACE(logger, "Backtrace log {}", 2);

  LOG_INFO(logger, "Welcome to Quill!");
  LOG_ERROR(logger, "An error message. error code {}", 123);
  LOG_WARNING(logger, "A warning message.");
  LOG_CRITICAL(logger, "A critical error.");
  LOG_DEBUG(logger, "Debugging foo {}", 1234);
  LOG_TRACE_L1(logger, "{:>30}", "right aligned");
  LOG_TRACE_L2(logger, "Positional arguments are {1} {0} ", "too", "supported");
  LOG_TRACE_L3(logger, "Support for floats {:03.2f}", 1.23456);
}


// [8748033] basic.cpp:20                 LOG_INFO      root         - Welcome to Quill!
// [8748033] basic.cpp:21                 LOG_ERROR     root         - An error message. error code 123
// [8748033] basic.cpp:22                 LOG_WARNING   root         - A warning message.

