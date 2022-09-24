/**
 * https_post_form_to_file.cpp
 * 2020-07-01 K.OHWADA
 */


// http post to postman echo server,  save response to local file
// test for http_post_to_file


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

    string postfileds( "project=curl&name=daniel&age=20" );

    string filepath("https_post_form_to_file_result.txt");

    bool is_verify = true;
    bool is_verbose = false;

	if( argc == 6 ) {
	    url = argv[1];
	    postfileds = argv[2];
	    filepath = argv[3];
	    is_verify = (bool)stoi( argv[4] );
	    is_verbose = (bool)stoi( argv[5] );
	}else if( argc == 5 ) {
	    url = argv[1];
	    postfileds = argv[2];
	    filepath = argv[3];
	    is_verify = (bool)stoi( argv[4] );
	}else if( argc == 4 ) {
	    url = argv[1];
	    postfileds = argv[2];
	    filepath = argv[3];
	} else if( argc == 3 ) {
	    url = argv[1];
	    postfileds = argv[2];
    } else {
		    cout << "Usage "<< argv[0 ] << " [url] [postfileds] [filepath]  [verify] [verbose] " 
			<< endl;
	}


    string error;
    bool ret = https_post_form_to_file( url, postfileds, filepath, error,  is_verify, is_verbose);

    if(!ret){	
		cout << error << endl;
	    return EXIT_FAILURE;
    }	

    cout << "saved to: " << filepath << endl;
	return EXIT_SUCCESS;
}


// saved to: http_post_to_file_result.txt 

