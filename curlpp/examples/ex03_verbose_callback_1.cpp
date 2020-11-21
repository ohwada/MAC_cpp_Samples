/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

//  Example 03: verbose callback example.

// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example03.cpp
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
* DebugFunction option using functor as a callback.
*/

#include <iostream>
#include <cstdlib>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

class MyWindow
{
public:
	int writeDebug(curl_infotype, char *data, size_t size)
	{
		fprintf(stderr, "Debug: ");
		fwrite(data, size, 1, stderr);
		return size;
	}
};


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

	string url("localhost");

	if(argc == 2){
		url = argv[1];
	} else {
		std::cerr	<< "Example 3: Wrong number of arguments" << std::endl 
							<< "Example 3: Usage: example3 url" 
							<< std::endl;
	}

	MyWindow myWindow;

	try 
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		using namespace curlpp::Options;
		request.setOpt(Verbose(true));
		using namespace std::placeholders;
		request.setOpt(DebugFunction(std::bind(&MyWindow::writeDebug, &myWindow, _1, _2, _3)));
		request.setOpt(Url(url));

		request.perform();
	}

	catch ( curlpp::LogicError & e ) 
	{
		cout << e.what() << endl;
	}

	catch ( curlpp::RuntimeError & e )
	{
		cout << e.what() << endl;
	}

	return 0;
}

