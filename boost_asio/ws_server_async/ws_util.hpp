#pragma once
/**
 * ws_util.hpp
 * 2022-10-01 K.OHWADA
 */

#include <chrono>
#include <thread>
#include <boost/format.hpp>

// prototype
std::string build_msg_text(int cnt);
void thread_sleep(int milisec);


/**
 * build_msg_text
 */
std::string build_msg_text(int cnt)
{
    const std::string FORMAT("Test %03d");
    auto text = boost::str( boost::format(FORMAT) % cnt);
    return text;
}


/**
 * thread_sleep
 */
void thread_sleep( int milisec)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
}