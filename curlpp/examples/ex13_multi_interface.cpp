/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

//  Example 13: Simple Multi interface example.
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example13.cpp
/*
 *    Copyright (c) <2002-2006> <Jean-Philippe Barrette-LaPierre>
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
* Simple Multi demo.
* 
*/


#include <iostream>
#include <string>

#include <cstdlib>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Multi.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#pragma comment(lib, "Ws2_32.lib")
#endif // WIN32

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

  
  string url1("https://example.com");

  string url2("https://www.google.com");

  if(argc == 3) {
      url1 = argv[1];
      url2 = argv[2];
} else {
    std::cerr << "Example 13: Usage: example13 url1 url2" 
	      << std::endl;
  }
  
  try {
    curlpp::Cleanup cleaner;
    
    curlpp::Easy request1;
    curlpp::Easy request2;
    
    request1.setOpt(new curlpp::options::Url(url1)); 
    request1.setOpt(new curlpp::options::Verbose(true)); 
    
    request2.setOpt(new curlpp::options::Url(url2)); 
    request2.setOpt(new curlpp::options::Verbose(true)); 
    
    int nbLeft;
    curlpp::Multi requests;
    requests.add(&request1);
    requests.add(&request2);
    
    /* we start some action by calling perform right away */
    while(!requests.perform(&nbLeft)) {};
    
    while(nbLeft) {
      struct timeval timeout;
      int rc; /* select() return code */
      
      fd_set fdread;
      fd_set fdwrite;
      fd_set fdexcep;
      int maxfd;
      
      FD_ZERO(&fdread);
      FD_ZERO(&fdwrite);
      FD_ZERO(&fdexcep);
      
      /* set a suitable timeout to play around with */
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      
      /* get file descriptors from the transfers */
      requests.fdset(&fdread, &fdwrite, &fdexcep, &maxfd);
      
      rc = select(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);
      
      switch(rc) {
      case -1:
	/* select error */
	nbLeft = 0;
	printf("select() returns error, this is badness\n");
	break;
      case 0:
      default:
	/* timeout or readable/writable sockets */
	while(!requests.perform(&nbLeft)) {};
	break;
      }
    }
    
    cout << "NB lefts: " << nbLeft << endl;
  }
  catch ( curlpp::LogicError & e ) {
    cout << e.what() << endl;
  }
  catch ( curlpp::RuntimeError & e ) {
    cout << e.what() << endl;
  }

  return EXIT_SUCCESS;
}

  
