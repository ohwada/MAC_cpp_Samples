/**
 * poco_thread.cpp
 * 2022-06-01 K.OHWADA
 */

// reference:https://codezine.jp/article/detail/2626

#include <iostream>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"


/**
 * class Worker
 */
class Worker: public Poco::Runnable
{
    void run()
    {
        std::cout << "excute!" << std::endl;
    }
};

/**
 * main
 */
int main(int argc, char* argv[])
{
    Worker worker;

    Poco::Thread    thread;

    // start worker threadd
    thread.start( worker );

    // waiting for thread to end
    thread.join();

    return 0;
}
