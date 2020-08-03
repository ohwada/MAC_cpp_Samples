/**
 * bind sample
 * 2020-03-01 K.OHWADA
 */

// example : bind function
// reference : https://kaworu.jpn.org/cpp/std::bind

#include <iostream>
#include <functional>


/**
 *  f1
 */
void
f1() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
}


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
        using namespace std::placeholders;

//  bind
        auto func1 = std::bind(f1);     // no argument
        auto func2 = std::bind(f2,_1);  // one argument
        auto func3 = std::bind(f3,_1,_2);       // two arguments

// excute
// void f1()
// void f2(int) 123
// void f3(int, int) 467 789

        func1();                        
        func2(123);                     
        func3(467, 789);               

        return 0;
}
