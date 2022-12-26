/**
 * thread_2.cpp
 * 2022-06-01 K.OHWADA
 */


// simple example of spawning only two threads with boost::thread
// https://kaworu.jpn.org/cpp/boost::thread_%EF%BC%92%E3%81%A4%E3%81%AE%E3%82%B9%E3%83%AC%E3%83%83%E3%83%89%E3%82%92%E5%8B%95%E3%81%8B%E3%81%99%E3%82%B7%E3%83%B3%E3%83%97%E3%83%AB%E3%81%AA%E4%BE%8B

#include <boost/thread.hpp>
#include <iostream>
#define MAX 5
 

/**
 * thread_1
 */
void thread_1 () {
        for (int i = 0; i < MAX; i++) {
                std::cout << __PRETTY_FUNCTION__ << std::endl;
                boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        }
}


 /**
 * thread_2
 */
void thread_2 () {
        for (int i = 0; i < MAX; i++) {
                std::cout << __PRETTY_FUNCTION__ << std::endl;
                boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        }
}
 

/**
 * main
 */
int main(int argc, char const* argv[])
{
        boost::thread th1(thread_1);
        boost::thread th2(thread_2);
 
        th1.join ();
        th2.join ();
 
        return 0;
}
