 /**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// Basic example of using various functions provided by locale library

// reference : https://www.boost.org/doc/libs/1_74_0/libs/locale/doc/html/hello_8cpp-example.html

//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <ctime>
#include <boost/locale.hpp>


using namespace boost::locale;
using namespace std;


/**
 * main
 */
int main(void)
{

    generator gen;
    locale loc = gen("en_US.UTF-8"); 

  // Make it system global
    locale::global(loc); 
  
    // Set locale for output
    cout.imbue(loc);
    
    cout <<format("Today {1,date} at {1,time} we had run our first localization example") % time(0) 
          <<endl;
   
    cout<<"This is how we show numbers in this locale "<<as::number << 12345.6 <<endl; 
    cout<<"This is how we show currency in this locale "<<as::currency << 123.4 <<endl; 
    cout<<"This is typical date in the locale "<<as::date << std::time(0) <<endl;
    cout<<"This is typical time in the locale "<<as::time << std::time(0) <<endl;
    cout<<"This is upper case "<<to_upper("Hello World!")<<endl;
    cout<<"This is lower case "<<to_lower("Hello World!")<<endl;
    cout<<"This is title case "<<to_title("Hello World!")<<endl;
    cout<<"This is fold case "<<fold_case("Hello World!")<<endl;
   
    return EXIT_SUCCESS;
}



// Today Dec 15, 2020 at 8:57:50 AM we had run our first localization example
// This is how we show numbers in this locale 12,345.6
// This is how we show currency in this locale $123.40
// This is typical date in the locale Dec 15, 2020
// This is typical time in the locale 8:57:50 AM
// This is upper case HELLO WORLD!
// This is lower case hello world!
// This is title case Hello World!
// This is fold case hello world!


