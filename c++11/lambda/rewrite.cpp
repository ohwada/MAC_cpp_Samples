/**
 * rewrite.cpp
 * 2022-06-01 K.OHWADA
 */


 // rewriting variables  by reference capture
// https://cpplover.blogspot.com/2009/11/lambda.html

#include <iostream>


/**
 * f
 */
template < typename Func >
void f( Func func )
{
    func(" and I'm OK.") ;
}

using namespace std;


/**
 * main
 */
int main()
{
    string x = "I'm a lumberjack" ;
    cout << x << endl ;

    f( [&](std::string const & str){ x += str ;} ) ;

    // The variable has been rewritten.
    cout << x << endl ;
    // "I'm a lumberjack and I'm OK."

    return 0;
}
