/**
 * thread_sleep.cpp
 * 2022-06-01 K.OHWADA
 */

// sleep a thread in boost::thread
boost::thread_%E3%81%AE%E3%82%B9%E3%83%AC%E3%83%83%E3%83%89%E3%82%92%E3%82%B9%E3%83%AA%E3%83%BC%E3%83%97%E3%81%95%E3%81%9B%E3%82%8B%E6%96%B9%E6%B3%95

#include <iostream>
#include <boost/thread.hpp>
#include <boost/timer/timer.hpp>


using namespace std;


/**
 * main
 */
int main()
{
// 100 milliseconds
    const int SLEEP = 100;

    boost::timer::cpu_timer timer;

    boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP));

    boost::timer::cpu_times elapsed = timer.elapsed();
    cout << "wall : " << elapsed.wall << endl;

    return 0;
}

