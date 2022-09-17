/**
 * thread sample
 * 2020-07-01 K.OHWADA
 */

// exclusive access guard in function
// https://en.cppreference.com/w/cpp/thread/lock_guard

#include <iostream>
#include <thread>
#include <mutex>


using namespace std;


// global
std::mutex g_mutex;  
int g_count = 0; 


/**
 * safe_increment
 */
void safe_increment(void)
{

// lock_guard object,g_mutex
    const std::lock_guard<std::mutex> lock(g_mutex);
    ++g_i; // increment
 
    cout << "safe_increment: " << std::this_thread::get_id() << " : " << g_count << endl;

    // g_mutex is automatically released when lock
    // goes out of scope
}
 

/**
 * main
 */
int main(void)
{

    cout << "main: " << g_count << endl;
 
    std::thread t1(safe_increment);
    std::thread t2(safe_increment);
 
    t1.join();
    t2.join();
 
    cout << "main: " << g_count << endl;

    return 0;
}


// main: 0
// safe_increment: 0x70000b6df000 : 1
// safe_increment: 0x70000b762000 : 2
// main: 2
