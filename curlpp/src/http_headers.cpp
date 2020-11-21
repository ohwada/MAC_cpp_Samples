  /**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// http with custom headers to postman-echo.com
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example02.cpp


#include <iostream>
#include <string>
#include <list>

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

    string url( "https://postman-echo.com/headers" );

	bool verbose = true;


	try
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		std::list<std::string> headers;
		headers.push_back( "Host: example.com" ); 
		headers.push_back( "Another: yes" ); 
		headers.push_back( "X-silly-header: no" ); 

 		request.setOpt( new 
		curlpp::Options::Url( url ) );
		request.setOpt(  new curlpp::Options::HttpHeader( headers ));
		request.setOpt( new curlpp::Options::Verbose( verbose ) );	

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

	return EXIT_SUCCESS;
}


// {"headers":{"x-forwarded-proto":"https","x-forwarded-port":"443","host":"example.com","x-amzn-trace-id":"Root=1-5f8d12f4-07eef55215be520851553641","accept":"*/*","another":"yes","x-silly-header":"no"}}


