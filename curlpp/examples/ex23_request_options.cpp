 /**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// Example 23: Setting request options using iterators to custom container of curlpp options.

// https://github.com/jpbarrette/curlpp/blob/master/examples/example23.cpp

/**
* \file
* Setting request options using iterators to custom container of curlpp options.
* 
*/

#include <iostream>
#include <string>
#include <vector>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>


using namespace std;
using namespace curlpp::options;


/**
 * main
 */
int main(int, char **)
{

	const string URL("http://example.com");
	const int PORT = 80;

	try
	{

		// That's all that is needed to do cleanup of used resources (RAII style).
		curlpp::Cleanup myCleanup;

		// Our request to be sent.
		curlpp::Easy myRequest;

		// Container of our choice with pointers to curlpp options.
		vector<curlpp::OptionBase *> options;

		options.push_back(new Url( URL ));
		options.push_back(new Port( PORT ));

		// Set all options in range to the Easy handle.
		myRequest.setOpt(options.begin(), options.end());

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
