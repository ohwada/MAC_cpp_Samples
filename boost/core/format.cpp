/**
 * format.cpp
 * 2020-07-01 K.OHWADA
 */

// output with formating like prinf() 
// reference : https://www.boost.org/doc/libs/1_66_0/libs/format/doc/format.html


#include <iostream>
#include <string>
#include <boost/format.hpp>

 using namespace std;


/**
 * main
 */
int main(void) 
{

// classical printf directive, no reordering :
    char toto[] = "toto";
    float x = 40.25;
    int step = 50;
    cout << "classical print stlye" << endl;
    cout << boost::format("writing %s,  x=%.2f : %d-th step \n") % toto % x % step; 


// Simple output, with reordering :
char s1[] = "11";
char s2[] = "22";
char s3[] = "33";
    cout << "boost stlye with reordering" << endl;
    cout << boost::format("%1% %2% %3% %2% %1% \n") % s1 % s2 % s3;

    return EXIT_SUCCESS;
}


// classical print stlye
// writing toto,  x=40.25 : 50-th step 
// boost stlye with reordering
// 11 22 33 22 11 

