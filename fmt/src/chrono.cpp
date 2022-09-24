/**
 *  chrono.cpp
 * 2022-06-01 K.OHWADA
 */

// Print chrono durations 

#include <fmt/chrono.h>

using namespace std::literals::chrono_literals;


/**
 *  main
 */
int main() 
{
// Print chrono durations 
  fmt::print("Default format: {} {}\n", 42s, 100ms);
  fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);

    return 0;
}

