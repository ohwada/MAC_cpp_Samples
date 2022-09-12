/**
 *  invoke.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ invoke.cpp -std=c++17 

// rference : https://faithandbrave.hateblo.jp/entry/2016/09/07/173344

#include <iostream>
#include <functional>


/**
 *  func
 */
void func(int, char, double)
{
    std::cout << "func" << std::endl;
}


/**
 * struct Functor
 */
struct Functor {
    void operator()(int, char, double)
    {
        std::cout << "functor" << std::endl;
    }
};


/**
 * struct X
 */
struct X {
    int member_variable = 3;

    void member_function(int, char, double)
    {
        std::cout << "member_function" << std::endl;
    }
};


/**
 *  main
 */
int main()
{
    // function
    std::invoke(func, 1, 'a', 3.14);

    // function object
    std::invoke(Functor(), 1, 'a', 3.14);

    // member variable
    X x;
    std::cout << std::invoke(&X::member_variable, x) << std::endl;

    // member function
    std::invoke(&X::member_function, x, 1, 'a', 3.14);

    return 0;
}


// func
// functor
// 3
// member_function


