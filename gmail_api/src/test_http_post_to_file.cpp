/**
  * Gmal API sample
 * 2020-07-01 K.OHWADA
 */


// post to postman echo server,  save response to local file
// test for http_post_to_file

// g++ src/test_http_post_to_file.cpp -std=c++11  `pkg-config --cflags --libs curlpp`

#include <iostream>
#include <string>
#include "curl_http_post_write.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

	string url("https://postman-echo.com/post");

    string postfileds( "project=curl&name=daniel&age=20" );

    string filepath("http_post_to_file_result.txt");

    bool verbose = false;


	if( argc == 4 ) {
	    url = argv[1];
	    filepath = argv[2];
	    postfileds = argv[3];
	    verbose = (bool)stoi( argv[4] );
    } else {
		    cout << "Usage "<< argv[0 ] << " [url] [postfileds] [verbose] " 
			<< endl;
	}


    string error;
    bool ret = http_post_to_file( url, postfileds, filepath, error, verbose);

    if(!ret){	
		cout << error << endl;
	    return EXIT_FAILURE;
    }	

    cout << "saved to: " << filepath << endl;
	return EXIT_SUCCESS;
}


// saved to: http_post_to_file_result.txt 

