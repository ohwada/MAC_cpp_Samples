/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

//  Example 16: HTTP POST example with HTTP Basic Authentification.
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example16.cpp
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
* Simple POST demo.
* 
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cerrno>

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

  string url("http://localhost/echo.php");

 	string postfileds("The quick brown fox jumps over the lazy dog");

    string user_pwd("taro:123456789");

  if(argc == 2) {
        url = argv[1];
    } else {
        std::cerr << "Usage: " << argv[0] << " url"
	      << std::endl;
  }
  
  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    
    request.setOpt(new curlpp::options::Url(url)); 
    request.setOpt(new curlpp::options::Verbose(true)); 
    
    std::list<std::string> header; 
    header.push_back("Content-Type: application/octet-stream"); 
    
    request.setOpt(new curlpp::options::HttpHeader(header)); 
    
    request.setOpt(new curlpp::options::PostFields( postfileds));
    int size = postfileds.size();
    request.setOpt(new curlpp::options::PostFieldSize(size));

    request.setOpt(new curlpp::options::UserPwd(user_pwd));
    
    request.perform(); 
  }
  catch ( curlpp::LogicError & e ) {
    std::cout << e.what() << std::endl;
  }
  catch ( curlpp::RuntimeError & e ) {
    std::cout << e.what() << std::endl;
  }

  return EXIT_SUCCESS;
}


// Hello 'taro' 
// You entered '123456789' as your password. 

