/**
 * time sample
 * 2020-10-01 K.OHWADA
 */


// display current time with nanoseconds  
// g++ timespec_get.cpp -std=c++17

// reference : https://cpprefjp.github.io/reference/ctime/timespec_get.html

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;




/**
 * main
 */
int main(void)
{

    const char FROMAT[] = "%Y-%m-%d %H:%M:%S %Z";

    timespec ts;
    timespec_get(&ts, TIME_UTC);

    long sec = ts.tv_sec;
    long nsec =  ts.tv_nsec;

    const size_t BUFSIZE = 100;
    char buff[BUFSIZE];
    strftime(buff, BUFSIZE, FROMAT, localtime(&sec) );

    cout << "Current time: " << buff << endl;
    cout << "nanos: " << nsec << endl;

    return EXIT_SUCCESS;
}


// Current time: 2020-09-20 13:19:59 JST
// nanos: 712627000

