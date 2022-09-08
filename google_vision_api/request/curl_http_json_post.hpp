#pragma once
/**
 * curl_http_json_post.hpp
 * 2020-07-01 K.OHWADA
 */

// send mail with Google API

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


#include <string>
#include "curl_write_func.hpp"


// prototype
bool http_json_post_to_memory(std::string url, std::string postfileds, std::string &response,  std::string &error, bool verbose );


/**
 *  http_json_post_to_memory
 */
bool http_json_post_to_memory(std::string url, std::string postfileds, std::string &response,  std::string &error, bool verbose )
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

    std::cout << "url: " <<  url << std::endl;

        std::list<std::string> headers; 
        headers.push_back("Content-Type: application/json"); 
    
        
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
std::cout << "LogicError: " << error << std::endl;
	}
	
	catch ( curlpp::RuntimeError & e )
	{
		is_error = true;
		error = e.what();
std::cout << "RuntimeError: " << error << std::endl;
	}


	return !is_error;
}
