/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// The most simple http get example.
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example00.cpp

/**
* \file
* The most simple example.
* 
*/

#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace std;
using namespace curlpp::options;


/**
 * main
 */
int main(void)
{

	const string URL("http://example.com");

	try
	{
		// That's all that is needed to do cleanup of used resources (RAII style).
		curlpp::Cleanup myCleanup;

		// Our request to be sent.
		curlpp::Easy myRequest;

		// Set the URL.
		myRequest.setOpt<Url>(URL);

		// Send request and get a result.
		// By default the result goes to standard output.
		myRequest.perform();
	}

	catch(curlpp::RuntimeError & e)
	{
		cout << e.what() << endl;
	}

	catch(curlpp::LogicError & e)
	{
		cout << e.what() << endl;
	}
    
  return 0;
}
