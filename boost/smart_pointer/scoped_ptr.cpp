/**
 *  scoped_ptr.cpp
 * 2022-06-01 K.OHWADA
 */

// https://www.boost.org/doc/libs/1_81_0/libs/smart_ptr/doc/html/smart_ptr.html#scoped_ptr_example

#include <boost/scoped_ptr.hpp>
#include <iostream>


/**
 * struct Shoe
 */
struct Shoe { ~Shoe() { std::cout << "Buckle my shoe\n"; } };


/**
 * class MyClass
 */
class MyClass {
    boost::scoped_ptr<int> ptr;
  public:
    MyClass() : ptr(new int) { *ptr = 0; }
    int add_one() { return ++*ptr; }
};


using  namespace std;


/**
 * main
 */
int main()
{
    boost::scoped_ptr<Shoe> x(new Shoe);
    MyClass my_instance;
    cout << my_instance.add_one() << '\n';
    cout << my_instance.add_one() << '\n';

    return 0;
}

// Buckle my shoe  

// One two buckle my shoe  
// https://www.youtube.com/watch?v=wuJaQT7gu-w  
