/**
  * abseil sample
 * 2020-07-01 K.OHWADA
 */

// exclusive access guard with MutexLock
// sample for absl::MutexLock
// https://abseil.io/docs/cpp/guides/synchronization


#include <iostream>
#include <thread>
#include "absl/synchronization/mutex.h"


using namespace std;


class Foo {
  public:
  Foo(void) {
        count_ = 0;
 }
  void countUp(void) {
    absl::MutexLock l(&lock_);
    // increment
    count_ ++; 
    cout << "countup: " << std::this_thread::get_id() << " : " << count_ << endl;
  }
  int getCount(void) {
        return count_ ;
  }
  private:
    absl::Mutex lock_;
    int count_;
};
// ----------


 

/**
 * main
 */
int main(void)
{

    Foo foo;

    cout << "main start: " << foo.getCount() << endl;

    std::thread t1([&foo]{ foo.countUp(); });
    std::thread t2([&foo]{ foo.countUp(); });
 
    t1.join();
    t2.join();
 
    cout << "main end: " << foo.getCount() << endl;

    return 0;
}


// main start: 0
// countup: 0x700009865000 : 1
// countup: 0x7000097e2000 : 2
// main end: 2

