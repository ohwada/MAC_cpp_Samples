/**
 *  lockfree_stack.cpp
 * 2022-06-01 K.OHWADA
 */


// https://boostjp.github.io/tips/lockfree-stack.html

#include <iostream>
#include <thread>
#include <boost/lockfree/stack.hpp>

boost::lockfree::stack<int> stk(128);


/**
 *  producer
 */
void producer()
{
    for (int i = 0; i<10; ++i) {
// add value to stack
        while (!stk.push(i)) {} 
    }
}


/**
 *  consumer
 */
void consumer()
{
    for (;;) {
        int x = 0;
        if (stk.pop(x)) { 
// get value from stack
            std::cout << x << std::endl;
        }
    }
}


/**
 *  main
 */
int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}