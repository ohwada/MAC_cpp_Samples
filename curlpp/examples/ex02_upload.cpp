 /**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// Example 02: an upload example.
// https://github.com/jpbarrette/curlpp/blob/master/examples/example02.cpp

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
* Uploading of string.
* ReadFunction option using functor.
* Setting custom headers.
*/

#include <iostream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
 
/*
   anonymous namespace to prevent name clash in case other examples using the same global entities
   would be compiled in the same project
*/
namespace
{

char *g_data = NULL;

size_t readData(char *buffer, size_t size, size_t nitems)
{
	strncpy(buffer, g_data, size * nitems);
	//std::cout << buffer << std::endl;

	return size * nitems;
}

} // namespace

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    string str_url("http://localhost/echo.php");

  	string str_data("The quick brown fox jumps over the lazy dog");

	if(argc == 3) {
		str_url = argv[1];
		str_data = argv[2];
	} else {
		cerr << "Example 2: Usage: example02 url string-to-send" 
							<< endl;
	}

	int size = str_data.size();
	g_data = (char *)str_data.c_str();

	char buf[50];

	try
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		std::list<std::string> headers;
		headers.push_back("Content-Type: text/*"); 
		sprintf(buf, "Content-Length: %d", size); 
		headers.push_back(buf);

		using namespace curlpp::Options;
		request.setOpt(new Verbose(true));
		request.setOpt(new ReadFunction(curlpp::types::ReadFunctionFunctor(readData)));
		request.setOpt(new InfileSize(size));
		request.setOpt(new Upload(true));
		request.setOpt(new HttpHeader(headers));
		request.setOpt(new Url(str_url));

		request.perform();
	}
	catch (curlpp::LogicError & e)
	{
		cout << e.what() << endl;
	}
	catch (curlpp::RuntimeError & e)
	{
		cout << e.what() << endl;
	}

	return 0;
}

