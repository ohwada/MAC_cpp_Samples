/**
 *  argument.cpp
 * 2022-06-01 K.OHWADA
 */

// ambda  can take arguments
// since ambda is a function object
// https://cpplover.blogspot.com/2009/11/lambda.html

#include <iostream>


int main()
{

    [](std::string const & str) /* argument */
    { std::cout << str << std::endl ; } /* funtion bpdy */
    ("Have you read your SICP today?");  /* function call */

    return 0;
}


// SICP
// https://en.wikipedia.org/wiki/Structure_and_Interpretation_of_Computer_Programs


