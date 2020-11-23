#pragma once
/**
 * Gmail API sample
 * 2020-07-01 K.OHWADA
 */

// send mail with Google API

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


#include <string>
#include "curl_write_func.hpp"


// prototype
bool http_json_post_token_to_memory(std::string url, std::string postfileds, std::string access_token, std::string &response,  std::string &error, bool verbose );


/**
 *  http_json_post_token_to_memory
 */
bool http_json_post_token_to_memory(std::string url, std::string postfileds, std::string access_token, std::string &response,  std::string &error, bool verbose )
{

	bool is_error = false;

	try
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		WriterMemoryClass mWriterChunk;

		// Set the writer callback to enable cURL 
		// to write result in a memory area
		using namespace std::placeholders;
		curlpp::types::WriteFunctionFunctor functor = std::bind(&WriterMemoryClass::WriteMemoryCallback, &mWriterChunk, _1, _2, _3);

		curlpp::options::WriteFunction *test = new curlpp::options::WriteFunction(functor);
		request.setOpt(test);

		// Setting the URL to retrive.
		request.setOpt(new curlpp::options::Url(url));
		request.setOpt(new curlpp::options::Verbose(verbose));

    
        std::list<std::string> headers; 
        headers.push_back("Content-Type: application/json"); 
    
        std::string header_auth = 
		std::string( "Authorization: Bearer ") + access_token;
		if(verbose){
			std::cout << "debug: " << header_auth<< std::endl;
		}

		headers.push_back( header_auth ); 

    request.setOpt(new curlpp::options::HttpHeader(headers)); 
    
    request.setOpt(new curlpp::options::PostFields(postfileds));

    int size = postfileds.size();
    request.setOpt(new curlpp::options::PostFieldSize(size));

		request.perform();

        response = mWriterChunk.getBuffer();

	}
	
	catch ( curlpp::LogicError & e )
	{
		is_error = true;
		error = e.what();
	}
	
	catch ( curlpp::RuntimeError & e )
	{
		is_error = true;
		error = e.what();
	}


	return !is_error;
}
