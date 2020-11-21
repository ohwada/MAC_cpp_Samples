/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

// get web page from example.com 
// save to local file
// https://github.com/jpbarrette/curlpp/blob/master/examples/example11.cpp

#include <iostream>
#include <string>
#include "url_write.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

	string url("http://example.com");

	string filepath("example_com_result.html");

    bool verbose = false;

	if(argc == 4){
		url = argv[1];
		filepath = argv[2];
	    verbose = (bool)stoi( argv[3] );
	} else if (argc == 3){
		url = argv[1];
		filepath = argv[2];
	} else {
		cout << "Usage: " << argv[0] << " [url] [file] [verbose]" 
			<< endl;
	}

	string error;
	bool ret = url_to_file(url, filepath, error, verbose);

    if(!ret){	
		cout << error << endl;
	    return EXIT_FAILURE;
    }	

    cout << "saved to: " << filepath << endl;
	return EXIT_SUCCESS;

}


// saved to: example_com_result.html


