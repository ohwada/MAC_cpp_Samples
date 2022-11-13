/**
 *  assign.cpp
 * 2022-06-01 K.OHWADA
 */

//  assign lambda to variable
// https://cpplover.blogspot.com/2009/11/lambda.html

#include <iostream>

// can pass to another function.
template < typename Func >
void f( Func func2 )
{
    func2() ;
}


/**
 * main
 */
int main()
{

// assign to variable
    auto func = []{ std::cout << "My hovercraft is full of eels." << std::endl ; } ;

// call
    func() ;

    f( []{std::cout << "All your lambda is belong to us." << std::endl ; } ) ;

    return 0;
}


// "My hovercraft is full of eels." 
// https://omniglot.com/language/phrases/hovercraft.htm
// https://www.youtube.com/watch?v=grA5XmBRC6g

