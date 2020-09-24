/**
 * thread sample
 * 2020-07-01 K.OHWADA
 */

// exclusive access guard in class methed
// https://cpprefjp.github.io/reference/mutex/mutex.html


#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;


/**
 * class X
 */
class X {
  std::mutex mtx_;
  std::vector<int> data_;
public:
  void add_value(int value)
  {
// exclusive access guard  to vector objects
    std::lock_guard<std::mutex> lock(mtx_);
    data_.push_back(value);
    cout << "add_value: "<< std::this_thread::get_id() << " : " << value << endl;
  }

  void print()
  {
    for (int x : data_) {
        cout << x << endl;
    }
  }
};
// ----------


/**
 * main
 */
int main(void)
{
  
    X x;

    std::thread t1([&x]{ x.add_value(1); });
    std::thread t2([&x]{ x.add_value(2); });

    t1.join();
    t2.join();

    cout << "result: " << endl;
    x.print();

    return 0;
}


// add_value: 0x70000850e000 : 1
// add_value: 0x700008591000 : 2
// result: 
// 1
// 2

