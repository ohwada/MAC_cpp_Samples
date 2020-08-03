/**
 * bind sample
 * 2020-03-01 K.OHWADA
 */

// example : changing the order of arguments with placeholders
// reference : https://kaworu.jpn.org/cpp/std::bind

#include <iostream>
#include <functional>
 

/**
 *  f3
 */
void
f3(int x, int y) {
        std::cout << __PRETTY_FUNCTION__ << " " << x << " " << y << std::endl;
}
 

/**
 *  main
 */
int main(int argc, char *argv[])
{

c// unchanging the order of arguments
        auto func1 = std::bind(f3, std::placeholders::_1, std::placeholders::_2);

c// changing the order of arguments
        auto func2 = std::bind(f3, std::placeholders::_2, std::placeholders::_1);

// excute
//void f3(int, int) 1 2
//void f3(int, int) 2 1

        func1(1,2);	
        func2(1,2);	

        return 0;
}
