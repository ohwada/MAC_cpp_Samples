/**
 * time sample
 * 2020-10-01 K.OHWADA
 */


// this sample demonstrates the difference between clock() time and real time
// reference : https://en.cppreference.com/w/cpp/chrono/c/clock
// https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now


#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std;


/**
 * func
 * the function does some time-consuming work
 */
void func(void)
{
    volatile double d = 0;
    for(int n=0; n<10000; ++n)
       for(int m=0; m<10000; ++m)
           d += d*n*m;
}
 

/**
 * main
 */
int main(void)
{

// get the approximate processor time
    std::clock_t c_start = std::clock();

// get time point representing the current time
     std::chrono::high_resolution_clock::time_point  t_start = std::chrono::high_resolution_clock::now();

// func() is called on two threads
    std::thread t1(func);
    std::thread t2(func); 
    t1.join();
    t2.join();

    std::clock_t c_end = std::clock();
     std::chrono::high_resolution_clock::time_point  t_end = std::chrono::high_resolution_clock::now();
 
// milli second
    double cputime =  1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;

// milli second
    double clocktime = std::chrono::duration<double, std::milli>(t_end-t_start).count();

    cout << std::fixed << std::setprecision(2) << "CPU time used: "
    << cputime << " ms \n"
    << "Wall clock time passed: "
    << clocktime
    << " ms \n" << endl;

    return EXIT_SUCCESS;
}


// CPU time used: 975.85 ms
// Wall clock time passed: 491.12 ms

