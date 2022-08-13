/**
 *  async.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  async.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/future/async.html'
#include <iostream>
#include <future>
#include <thread>


/**
 *  foo
 */
int foo() { std::cout << "executes foo()\n"; return 3; }


/**
 *  main
 */
int main()
{
  // asynchronous execution of function foo() in new thread
  {
    std::cout << "invokes std::async(std::launch::async, foo)" << std::endl;
    std::future<int> f = std::async(std::launch::async, foo);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "main thread: slept for 10 msec\n";

    // get result of asynchronous execution
    int result = f.get();
    std::cout << "foo() = " << result << std::endl;
  }

  std::cout << std::endl;

  // asynchronous execution of function f in delayed state
  {
    // do not execute function foo() at this stage
    std::cout << "invokes std::async(std::launch::deferred, foo)" << std::endl;
    std::future<int> f = std::async(std::launch::deferred, foo);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "main thread: slept for 10 msec\n";

    // get result of asynchronous execution
    // Execute function foo() at this stage
    int result = f.get();
    std::cout << "foo() = " << result << std::endl;
  }

  return 0;
}


// invokes std::async(std::launch::async, foo)
// executes foo()
// main thread: slept for 10 msec
// foo() = 3


