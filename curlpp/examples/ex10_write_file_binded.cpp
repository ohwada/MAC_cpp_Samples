/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// Example 10: Binded function functor for WriteFunction example.
// https://github.com/jpbarrette/curlpp/blob/master/examples/example10.cpp
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
* WriteFunction option using functor.
* Writing to FILE*
* 
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


#define MAX_FILE_LENGTH 20000

using namespace std;


/**
 * FileCallback
 */
size_t 
FileCallback(FILE *f, char* ptr, size_t size, size_t nmemb)
{
	return fwrite(ptr, size, nmemb, f);
};


/**
 * main
 */
int main(int argc, char *argv[])
{

	string str_url("http://example.com");
	string str_filepath("example_com_result_10.txt");

	if(argc == 3){
		str_url = argv[1];
		str_filepath = argv[2];
	} else {
		cerr << argv[0] << ": Usage: " << " url file" 
			<< endl;
	}

    char* filename = (char *)str_filepath.c_str();

	FILE * file = fopen(filename, "w");
	if (!file)
	{
		cerr << "Error opening " << filename << endl;
		return EXIT_FAILURE;
	}

	cout << "open: " << filename << endl;

    bool ret;
	try
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		// Set the writer callback to enable cURL to write result in a memory area
		using namespace std::placeholders;
		curlpp::options::WriteFunction *test = new curlpp::options::WriteFunction(std::bind(&FileCallback, file, _1, _2, _3));
		request.setOpt(test);

		// Setting the URL to retrive.
		request.setOpt(new curlpp::options::Url(str_url));
		request.setOpt(new curlpp::options::Verbose(true));
		request.perform();

        ret = true;

	}

	catch ( curlpp::LogicError & e )
	{
        ret = false;
		cout << e.what() << endl;
	}

	catch ( curlpp::RuntimeError & e )
	{
        ret = false;
		cout << e.what() << endl;
	}

    if(!ret){	
	    return EXIT_FAILURE;
    }	

    cout << "saved to: " << filename << endl;
	return EXIT_SUCCESS;

}
