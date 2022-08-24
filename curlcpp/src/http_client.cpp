/**
 * http_client.cpp
 * This example shows how to make a simple request with curl.
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/JosephP91/curlcpp

#include <iostream>
#include <string>
#include "curl_easy.h"

using namespace std;

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;


/**
 *  main
 */
int main(int argc, char *argv[])
{

	char* url = (char *)"http://example.com";

	if( argc == 2 ) {
	    url = argv[1];
    } else {
		    cout << "Usage "<< argv[0 ] << " <url>" 
			<< endl;
	}

    cout << url << endl;
    cout << endl;

    // Easy object to handle the connection.
    curl_easy easy;

    // Add some options.
    easy.add<CURLOPT_URL>(url);
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();
    } catch (curl_easy_exception &error) {
    	// If you want to print the last error.
        std::cerr<<error.what()<<std::endl;
    }

    return 0;
}

