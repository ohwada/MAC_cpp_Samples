/**
 * thread_1.cpp
 * 2022-06-01 K.OHWADA
 */

// simple example of spawning only one thread with boost::thread
// https://kaworu.jpn.org/cpp/boost::thread_%EF%BC%91%E3%81%A4%E3%81%AE%E3%82%B9%E3%83%AC%E3%83%83%E3%83%89%E3%81%A0%E3%81%91%E5%8B%95%E3%81%8B%E3%81%99%E3%82%B7%E3%83%B3%E3%83%97%E3%83%AB%E3%81%AA%E4%BE%8B

#include <boost/thread.hpp>
#include <iostream>
 

/**
 * thread_1
 */
void thread_1 () {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
}
 

/**
 * main
 */
int main(int argc, char const* argv[])
{
        boost::thread th1(thread_1);
 
        th1.join ();
 
        return 0;
}


// void thread_1()

