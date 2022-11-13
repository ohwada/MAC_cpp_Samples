/**
 * hello.cpp
 * 2022-06-01 K.OHWADA
 */

// desplay "Hello,World" with lambda
// https://cpplover.blogspot.com/2009/11/lambda.html

#include <iostream>


/**
 * main
 */
int main()
{
    []{ std::cout << "Hello,World" << std::endl ; }() ;

    return 0;
}
