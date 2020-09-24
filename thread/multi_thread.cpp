/**
 * thread sample
 * 2020-07-01 K.OHWADA
 */

// run two threads 
// communicate between threads via global variables

// reference : https://en.cppreference.com/w/cpp/thread/thread/join

#include <iostream>
#include <thread>
#include <chrono>
 
using namespace std;

// global variables
bool is_running_A;
bool has_msg;


/**
 * threadA
 */
void threadA(void)
{

    cout << "A) start thred " << endl;
    is_running_A = true;

    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // simulate to send message
    cout << "A) send to B" << endl;
    has_msg = true;

    while(true){

        cout << std::boolalpha << "A) has_msg: " << has_msg << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if( !has_msg ){
            // thread B recived message
            cout << "A) maybe B recieved" << endl;
            break;
        }
    } // while

    std::this_thread::sleep_for(std::chrono::seconds(1));

    cout << "A) finish thred " << endl;
    is_running_A = false;
}


/**
 * threadB
 */
void threadB(void) 
{

    cout << "B) start thred " << endl;

    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));

    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if( has_msg ){
        // simulate to send message
            cout << endl;
            cout << "B) recieve from A" << endl;
            has_msg = false;
        }
        if( !is_running_A ){
            // fonish if A finished
            cout << endl;
            cout << "B) maybe A finished" << endl;
            break;
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    cout << "B) finish thred " << endl;

}
 

/**
 * main
 */
int main(void)
{

    cout << "main) starting first thread" << endl;
    std::thread th1(threadA);
 
    cout << "main) starting second thread" << endl;
    std::thread th2(threadB);
 
    cout << "main) waiting for threads to finish..." << std::endl;

    th1.join();
    th2.join();
 
    cout << "main) done!" << endl;

    return 0;
}


// main) starting first thread
// main) starting second thread
// main) waiting for threads to finish...
// A) start thred 
// B) start thred 
// A) send to B
// A) has_msg: true
// B) recieve from A
// A) has_msg: false
// A) maybe B recieved
// A) finish thred 
// B) maybe A finished
// B) finish thred 
// main) done!

