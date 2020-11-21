/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// HTTP Post Client
// http post to postman echo server,



#include <iostream>
#include <string>

 #include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>


// prototype
bool http_post(std::string url, std::string postfileds, std::string &error,  bool verbose);


/**
 * http_post
 */
bool http_post(std::string url, std::string postfileds, std::string &error,  bool verbose)
{

    bool is_error = false;

  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    
    request.setOpt(new curlpp::options::Url( url )); 
    request.setOpt(new curlpp::options::Verbose( verbose )); 
    
    std::list<std::string> header; 
    header.push_back("Content-Type: application/x-www-form-urlencoded"); 
    
    request.setOpt(new curlpp::options::HttpHeader(header)); 
    
    request.setOpt(new curlpp::options::PostFields(postfileds));

    int size = postfileds.size();
    request.setOpt(new curlpp::options::PostFieldSize(size));
    
    request.perform(); 
  }
  catch ( curlpp::LogicError & e ) {
		is_error = true;
		error = e.what();
  }
  catch ( curlpp::RuntimeError & e ) {
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
    bool ret = http_post( url, postfileds, error, verbose);

    if(!ret){	
		cout << error << endl;
	    return EXIT_FAILURE;
    }	

    cout << "saved to: " << filepath << endl;
	return EXIT_SUCCESS;
}


//{"project":"curl","name":"daniel","age":"20"}


