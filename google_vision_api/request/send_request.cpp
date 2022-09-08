/**
 * send_request.hpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include "vision_api_request.hpp"
#include "build_request.hpp"


/**
 * saveRequest
 */
bool  saveRequest( std::string request )
{
    std::string prefix("request");
    std::string ext("json");
    std::string filename;
    getTimestampFileName( prefix, ext, filename );

    bool ret =  writeTextFile( filename,  request );

    if(ret){
        std::cout << "saved to: " << filename << std::endl;
    } else {
        std::cerr << "writeTextFile failed: " << filename << std::endl;
    }

    return ret;
}


/**
 * saveResponse
 */
bool saveResponse( std::string response )
{
    std::string prefix("response");
    std::string ext("json");
    std::string filename;
    getTimestampFileName( prefix, ext, filename );

    bool ret =  writeTextFile( filename,  response );

    if(ret){
        std::cout << "saved to: " << filename << std::endl;
    } else {
        std::cerr << "writeTextFile failed: " << filename << std::endl;
    }

    return ret;
}


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

	string file("res/albert_and_elsa.jpg");

    if(argc == 2) {
    		file = argv[1];
	} else {
        cout << "Usage: " <<  argv[0] << " <imageFile> " << endl;
    }

const int  RESULTS_INT = 2;

string request;
bool ret1 = build_request_from_file(file, RESULTS_INT, request);
if(!ret1){
    return EXIT_FAILURE;
}


    saveRequest(request);
    

    string response;
    string error;
    bool is_verbose_send = true;


bool ret2 = api_annotate_request(request, response, error, is_verbose_send);

    if(!ret2 ){
            cout << "send error: " << error  << endl;
            return EXIT_FAILURE;
    }

    cout << response << endl;

    saveResponse( response );

    cout << "send request sucessful"<< endl;

    return EXIT_SUCCESS;
}


