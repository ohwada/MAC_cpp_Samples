/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */


 // Example 20: std::ostream usage.
// https://github.com/jpbarrette/curlpp/blob/master/examples/example20.cpp

/*
 *    Copyright (c) <2002-2005> <Jean-Philippe Barrette-LaPierre>
 *    
 *    Permission is hereby granted, free of charge, to any person obtaining
 *    a copy of this software and associated documentation files 
 *    (curlpp), to deal in the Software without restriction, 
 *    including without limitation the rights to use, copy, modify, merge,
 *    publish, distribute, sublicense, and/or sell copies of the Software,
 *    and to permit persons to whom the Software is furnished to do so, 
 *    subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included
 *    in all copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 *    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
* \file
* Using WriteStream option.
* 
*/

#include <iostream>
#include <string>
#include <sstream>

#include <cstdlib>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    string url = "https://example.com";

    if(argc == 2) {
        url = argv[1];
    } else {
        cerr  << argv[0] << ": Usage: " << " url " 
	      << endl;
    }


  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    // Set the writer callback to enable cURL 
    // to write result in a memory area
    request.setOpt(new curlpp::options::WriteStream( &std::cout ));
    
    // Setting the URL to retrive.
    request.setOpt(new curlpp::options::Url(url));

    request.perform();

    return EXIT_SUCCESS;
  }
  catch ( curlpp::LogicError & e ) {
    std::cout << e.what() << std::endl;
  }
  catch ( curlpp::RuntimeError & e ) {
    std::cout << e.what() << std::endl;
  }

  return EXIT_FAILURE;
}