/**
 *  lockfree_queue.cpp
 * 2022-06-01 K.OHWADA
 */


// https://boostjp.github.io/tips/lockfree-queue.html

#include <iostream>
#include <thread>
#include <boost/lockfree/queue.hpp>

boost::lockfree::queue<int> que(128);


/**
 *  producer
 */
void producer()
{
    for (int i = 0; i<10; ++i) {
// add value to queue
        while (!que.push(i)) {} 
    } // for
}


/**
 *  consumer
 */
void consumer()
{
    for (;;) {
        int x = 0;
        if (que.pop(x)) {
// get the value from the queue
            std::cout << x << std::endl;
        }
    } // for
}


using  namespace std;


/**
 * main
 */
int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}

// 0
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
//9

