/**
 *  backtrace.cpp
 * 2022-06-01 K.OHWADA
 */

// Backtrace support
// https://github.com/gabime/spdlog

#include "spdlog/spdlog.h"


/**
 * backtrace_example
 */
void backtrace_example()
{
// Debug messages can be stored in a ring buffer instead of being logged immediately.
// This is useful in order to display debug logs only when really needed (e.g. when error happens).
// When needed, call dump_backtrace() to see them.

spdlog::enable_backtrace(32); // Store the latest 32 messages in a buffer. Older messages will be dropped.
// or my_logger->enable_backtrace(32)..
for(int i = 0; i < 100; i++)
{
  spdlog::debug("Backtrace message {}", i); // not logged yet..
} // for
// e.g. if some error happened:
spdlog::dump_backtrace(); // log them now! show the last 32 messages

// or my_logger->dump_backtrace(32)..
}

// using namespace std;


/**
 * main
 */
int main() 
{
    backtrace_example();

    return 0;
}


// [info] ****************** Backtrace Start ******************
// [debug] Backtrace message 68
// [debug] Backtrace message 99
// [info] ****************** Backtrace End ********************
