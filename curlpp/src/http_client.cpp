/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// simple HTTP Client
// get from example.com

// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example04.cpp

#include <iostream>
#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>


// prototype
bool http_get(std::string url, std::string &error,  bool is_verbose);



/**
 * http_get
 */
bool http_get(std::string url, std::string &error,  bool is_verbose)
{

	bool is_error = false;

	try
	{

		// That's all that is needed to do cleanup of used resources (RAII style).
		curlpp::Cleanup myCleanup;

		// Our request to be sent.
		curlpp::Easy myRequest;

		// Set the URL
		myRequest.setOpt(curlpp::Options::Url( url ));

		myRequest.setOpt(curlpp::Options::Verbose(is_verbose));

		// Send request and get a result.
		myRequest.perform();
	}

	catch(curlpp::RuntimeError & e)
	{
		is_error = true;
		error = e.what();
	}

	catch(curlpp::LogicError & e)
	{
		is_error = true;
		error = e.what();
	}
    
  return !is_error;
}


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

	string url("http://example.com");

	bool is_verbose = false;

	if( argc == 3 ) {
	    url = argv[1];
	    is_verbose = (bool)stoi( argv[2] );
	} else if( argc == 2 ) {
	    url = argv[1];
    } else {
		    cout << "Usage "<< argv[0 ] << " [url] [verbose] " 
			<< endl;
	}

	string error;
	bool ret = http_get(url, error, is_verbose);

    if(!ret){	
		cout << error << endl;
	    return EXIT_FAILURE;
    }	

	return EXIT_SUCCESS;
}


// <title>Example Domain </title>
