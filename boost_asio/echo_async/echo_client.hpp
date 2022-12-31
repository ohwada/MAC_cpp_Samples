#pragma once
/**
 * echo_client.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include <thread>
#include <chrono>
#include <boost/format.hpp>

// prototype
 std::string get_write_data(int cnt);
 void thread_sleep(int miliseconds);


/**
 * build_write_data
 */
 std::string build_write_data(int cnt)
{
    const std::string FORMAT("%03d");

    auto data  = boost::str( boost::format(FORMAT) % cnt ) ;

    return data;
}


/**
 * thread_sleep
 */
 void thread_sleep(int miliseconds)
{
    std::this_thread::sleep_for(std::chrono:: milliseconds (miliseconds));
}
