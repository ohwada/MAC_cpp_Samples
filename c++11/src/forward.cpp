/**
 * forward.cpp
 * 2022-06-01 K.OHWADA
 */

//  g++ forward.cpp -std=c++11
// https://runebook.dev/ja/docs/cpp/utility/forward

#include <iostream>
#include <memory>
#include <utility>
 

/**
 * struct A
 */
struct A {
    A(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
    A(int& n)  { std::cout << "lvalue overload, n=" << n << "\n"; }
};
 

/**
 * class B
 */
class B {
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
        a1_{std::forward<T1>(t1)},
        a2_{std::forward<T2>(t2)},
        a3_{std::forward<T3>(t3)}
    {
    }
 
private:
    A a1_, a2_, a3_;
};
 

/**
 *  make_unique1
 */
template<class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
}
 

/**
 *  make_unique2
 */
template<class T, class... U>
std::unique_ptr<T> make_unique2(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}
 

/**
 * main
 */
int main()
{   
    std::cout << "A \n";
    auto p1 = make_unique1<A>(2); // rvalue
    int i = 1;
    auto p2 = make_unique1<A>(i); // lvalue
 
    std::cout << "B \n";
    auto t = make_unique2<B>(2, i, 3);
}


// A
// rvalue overload, n=2
// lvalue overload, n=1
// B
// rvalue overload, n=2
// lvalue overload, n=1
// rvalue overload, n=3


