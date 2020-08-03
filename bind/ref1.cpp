
// example :  call by reference
// reference : https://kaworu.jpn.org/cpp/std::bind

#include <iostream>
#include <functional>
 

/**
 *  f
 * chnge the value of the argument
 * becauase call by reference
 */
void
f(int& x) {
        x = 123;
}
 

/**
 *  main
 */
int main(int argc, char *argv[])
{
// bind reference
        auto func = std::bind(f, std::ref(x) );

        int x = 0;

// change value of x
// x = 123
        func();

// 123
        std::cout<<x<<std::endl;

        return 0;
}
