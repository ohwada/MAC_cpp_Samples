 /**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

//Example 15: Simple example for demonstrating the NoValueOptionTrait. (SslEngineDefault)
// https://github.com/jpbarrette/curlpp/blob/master/examples/example15.cpp
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
* Using options.
* 
*/


#include <string>
#include <iostream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace std;


/**
 * main
 */
int main(int, char **)
{

    const string URL("https://example.com");

  try
  {
      curlpp::Cleanup myCleanup;
      
      // Creation of the URL option.
      curlpp::Easy myRequest;
      myRequest.setOpt(new curlpp::options::Url(URL));
      myRequest.setOpt(new curlpp::options::SslEngineDefault());
      myRequest.perform();
    }
  catch( curlpp::RuntimeError &e )
    {
      cout << e.what() << endl;
    }
  catch( curlpp::LogicError &e )
    {
      cout << e.what() << endl;
    }
    
  return 0;
}
