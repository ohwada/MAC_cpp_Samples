 /**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// Example 04: GetInfo example.
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example04.cpp

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
* Getting options using curlpp::infos.
* 
*/


#include <iostream>
#include <cstdlib>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
 

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

	string url("http://localhost");

	if(argc == 2) {
	    url = argv[1];
	} else {
		cerr << "Example 04: Usage: example04 url" 
			<< endl;
	}

	try 
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		using namespace curlpp::Options;
		request.setOpt(Verbose(true));
		request.setOpt(Url(url));

		request.perform();

		std::string effURL;
		curlpp::infos::EffectiveUrl::get(request, effURL);
		cout << "Effective URL: " << effURL << endl;

		//other way to retreive URL
		cout << std::endl 
			<< "Effective URL: " 
			<< curlpp::infos::EffectiveUrl::get(request)
			<< endl;

		cout << "Response code: " 
			<< curlpp::infos::ResponseCode::get(request) 
			<< endl;

		cout << "SSL engines: " 
			<< curlpp::infos::SslEngines::get(request)
			<< endl;
	}
	catch ( curlpp::LogicError & e ) {
		cout << e.what() << endl;
	}
	catch ( curlpp::RuntimeError & e ) {
		cout << e.what() << endl;
	}

	return 0;
}

