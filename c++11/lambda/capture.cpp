/**
 *  capture.cpp
 * 2022-06-01 K.OHWADA
 */


// lambda can capture variables 
// within the scope of the function in which it is defined.
// https://cpplover.blogspot.com/2009/11/lambda.html

#include <iostream>


/**
 * main
 */
int main()
{

    std::string x = "I'm a lumberjack and I'm OK." ;

// capture by reference
    [&]{ std::cout << x << std::endl ; }() ;

// capture by copy
    [=]{ std::cout << x << std::endl ; }() ;

    return 0;
}


// "I'm a lumberjack and I'm OK."
// https://en.wikipedia.org/wiki/The_Lumberjack_Song
// https://www.youtube.com/watch?v=6tFJQ-LIAkI


