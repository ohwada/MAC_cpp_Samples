/**
 * poco_request_saver.hpp
 * 2022-06-01 K.OHWADA
 */

#include <fstream>
#include <string>
#include "Poco/Net/HTTPServerRequest.h"
#include "poco_timestamp.hpp"


// prototype
bool save_request( HTTPServerRequest& request, bool is_verbose );
bool save_http_server_request(HTTPServerRequest& request, std::string fpath,  bool is_verbose );
void print_request(HTTPServerRequest& request);


/**
 * save_request
 */
bool save_request( HTTPServerRequest& request, bool is_verbose )
{
    std::string dir("log");
    std::string prefix("server_request");
    std::string ext("txt");

    std::string fpath = build_timestamp_file_path(dir, prefix, ext);

     return save_http_server_request(request,  fpath, is_verbose );
}


/**
 *   save_http_server_request
 */
bool save_http_server_request(HTTPServerRequest& request, std::string fpath,  bool is_verbose )
{

    std::ofstream ofs(fpath);
    if(!ofs){
        if(is_verbose ) {
            std::cerr << "cannot open: " << fpath << std::endl;
        }
        return false;
    }

	request.write(ofs);

    if(is_verbose ) {
        std::cout << "saved: " << fpath << std::endl;
    }

    ofs.close();

    return true;
}


/**
 *   print_request
 */
// header parts only
// not include body parts
void print_request(HTTPServerRequest& request )
{
	request.write(std::cout);
}
