/**
 *  get_id.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ get_id.cpp -std=c++11
// https://en.cppreference.com/w/cpp/thread/thread/get_id

#include <iostream>
#include <thread>
#include <chrono>
 
void foo()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

 /**
 *  main
 */
int main()
{
    std::thread t1(foo);
    std::thread::id t1_id = t1.get_id();
 
    std::thread t2(foo);
    std::thread::id t2_id = t2.get_id();
 
    std::cout << "t1's id: " << t1_id << '\n';
    std::cout << "t2's id: " << t2_id << '\n';
 
    t1.join();
    t2.join();
}

// t1's id: 0x70000d91d000
// t2's id: 0x70000d9a0000

