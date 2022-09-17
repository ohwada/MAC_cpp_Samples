/**
 * thread sample
 * 2020-07-01 K.OHWADA
 */

// run two threads 
// communicatebetween threads via condition variable

// reference : https://en.cppreference.com/w/cpp/thread/condition_variable


#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


// global
std::mutex g_mutex;
std::condition_variable g_cv;
std::string g_data;
bool g_ready = false;
bool g_processed = false;
 

/**
 * threadA
 */
void threadA(void)
{
 
    g_data = "A: Example data ";
    // send data to the threadB
    {
        std::lock_guard<std::mutex> lk(g_mutex);
        g_ready = true;
        cout << "A) signals data ready for processing" << endl;
    }

    cout << "A) notify" << endl;
    g_cv.notify_one();
 
    // wait for the threadB
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        g_cv.wait(lk, []{return g_processed;});
        cout << "A) wait" << endl;
    }

    cout << "A) data = " << g_data << endl;
 
}



/**
 * threadB
 */
void threadB(void)
{
    // Wait until hreadA sends data
    std::unique_lock<std::mutex> lk(g_mutex);
    g_cv.wait(lk, []{return g_ready;});
     cout << "B) wait" << endl;

    // after the wait, we own the lock.
    cout << "B) processing data" << endl;
    g_data += ", B: after processing ";
 
    // Send g_data back to threadA
    g_processed = true;
    cout << "B) thread signals g_data processing completed" << endl;
 
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();

    cout << "B) notify" << endl;
    g_cv.notify_one();
}
 

/**
 * main
 */
int main(void)
{

    std::thread th1(threadA);
    std::thread th2(threadB);
 
    th1.join();
    th2.join();

    return 0;
}


// A) signals data ready for processing
// A) notify
// B) wait
// B) processing data
// B) thread signals g_data processing completed
// B) notify
// A) wait
// A) data = A: Example data , B: after processing 

