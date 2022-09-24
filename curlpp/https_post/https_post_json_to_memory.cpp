/**
 * https_post_json_to_memory.cpp
 * 2020-07-01 K.OHWADA
 */

// http post to postman echo server,  copy response to memory 
// test for http_post_to_memory

#include <iostream>
#include <string>
#include "https_post_write.hpp"


using namespace std;



/**
 * main
 */
int main(int argc, char *argv[])
{

	string url("https://postman-echo.com/post");

    string postfileds =
    R"( { "project" : "curl_file", "name": "michael" "age": 30 } )";


    bool is_verify = true;
    bool is_verbose = false;

	if( argc == 5 ) {
	    url = argv[1];
	    postfileds = argv[2];
	    is_verify = (bool)stoi( argv[3] );
	    is_verbose = (bool)stoi( argv[4] );
	}else if( argc == 4 ) {
	    url = argv[1];
	    postfileds = argv[2];
	    is_verify = (bool)stoi( argv[3] );
	} else if( argc == 3 ) {
	    url = argv[1];
	    postfileds = argv[2];
    } else {
		    cout << "Usage "<< argv[0 ] << " [url] [postfileds] [verbose] " 
			<< endl;
	}


    string response;
    string error;
    bool ret = https_post_json_to_memory( url, postfileds, response, error, is_verify, is_verbose );

    if(!ret){	
		cout << error << endl;
	    return EXIT_FAILURE;
    }	

    printResponse(response);
	return EXIT_SUCCESS;

}
