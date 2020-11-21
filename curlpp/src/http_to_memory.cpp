/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// get web page from example.com 
// copy to memory
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example06.cpp

 
#include <iostream>
#include <string>
#include "url_write.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

	std::string url("http://example.com");

    bool verbose = false;

	if( argc == 3 ) {
	    url = argv[1];
	    verbose = (bool)stoi( argv[2] );
	} else if( argc == 2 ) {
	    url = argv[1];
    } else {
		    cout << "Usage "<< argv[0 ] << " [url] [verbose] " 
			<< endl;
	}

	string response;
	string error;
	bool ret = url_to_memory(url, response,  error, verbose);
    if(!ret){	
		cout << error << endl;
	    return EXIT_FAILURE;
    }	

 	printResponse(response);

	return EXIT_SUCCESS;
}


//  <title>Example Domain</title>


