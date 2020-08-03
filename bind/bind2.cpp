/**
 * bind sample
 * 2020-03-01 K.OHWADA
 */

// example : bind the arguments
// reference : https://kaworu.jpn.org/cpp/std::bind

#include <iostream>
#include <functional>
 

/**
 *  f2
 */
void
f2(int x) {
        std::cout << __PRETTY_FUNCTION__ << " " << x << std::endl;
}
 

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


// bind one argument in a function with one argument
        auto func2 = std::bind(f2, 123); 

// bind two argument in a function with two arguments
        auto func3 = std::bind(f3, 123, 456);

// bind one argument in a function with two arguments
        auto func4 = std::bind(f3, 789, std::placeholders::_1);

// excute
// void f2(int) 123
// void f3(int, int) 123 456
// void f3(int, int) 789 1000

        func2();                        
        func3();                       
        func4(1000);  

        return 0;
}
