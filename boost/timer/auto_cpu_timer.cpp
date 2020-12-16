/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// auto cpu timer
// When the auto_cpu_timer object is created, it starts timing. 
//When it is destroyed at the end of the scope,  its destructor stops the timer and displays timing information on the default output stream, std::cout.

// reference : https://www.boost.org/doc/libs/1_54_0/libs/timer/doc/cpu_timers.html

#include <boost/timer/timer.hpp>
#include <cmath>


/**
 * main
 */
int main(void)
{

  boost::timer::auto_cpu_timer t;

// burn some time
    for (long i = 0; i < 100000000; ++i) {
        std::sqrt(123.456L); 
    }

    return EXIT_SUCCESS;
}


 // 0.642409s wall, 0.640000s user + 0.000000s system = 0.640000s CPU (99.6%)

