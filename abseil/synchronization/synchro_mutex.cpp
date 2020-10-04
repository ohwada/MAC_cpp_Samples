/**
  * abseil sample
 * 2020-07-01 K.OHWADA
 */

// exclusive access guard with mutex
// sample for absl::Mutex#Lock()  and absl::Mutex#Unlock()
// https://abseil.io/docs/cpp/guides/synchronization


#include <iostream>
#include <thread>
#include "absl/synchronization/mutex.h"


using namespace std;


 // global
absl::Mutex g_mu;
int g_count = 0;

 

/**
 * countup
 */
void countup(void)
{

//lock
    g_mu.Lock();

// increment
    g_count ++; 
    cout << "countup: " << std::this_thread::get_id() << " : " << g_count << endl;

// unlock
    g_mu.Unlock();

}
 

/**
 * main
 */
int main(void)
{

    cout << "main start: " << g_count << endl;
 
    std::thread t1(countup);
    std::thread t2(countup);
 
    t1.join();
    t2.join();
 
    cout << "main end: " << g_count << endl;

    return 0;
}


// main start: 0
// countup: 0x70000c454000 : 1
// countup: 0x70000c4d7000 : 2
// main end: 2
