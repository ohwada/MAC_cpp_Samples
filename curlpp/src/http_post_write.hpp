#pragma once
/**
 * http_post_write.hpp
 * 2020-07-01 K.OHWADA
 */

// http post to file or memory

#include <iostream>
#include <string>
#include "write_func.hpp"

// prototype
bool http_post_form_to_memory(std::string url, std::string postfileds, std::string &response,  std::string &error, bool verbose);
bool http_post_json_to_memory(std::string url, std::string postfileds, std::string &response,  std::string &error, bool verbose);
bool http_post_to_memory_header(std::string url, std::string postfileds, 	std::list<std::string> header, std::string &response,  std::string &error, bool verbose);
bool http_post_to_file(std::string url,  std::string postfileds, std::string filepath, std::string &error, bool verbose);


/**
 *  http_post_form_to_memory
 */
bool http_post_form_to_memory(std::string url, std::string postfileds, std::string &response,  std::string &error, bool verbose)
{
	std::list<std::string> header; 
	header.push_back("Content-Type: application/x-www-form-urlencoded");
	return http_post_to_memory_header(url,  postfileds,  	header, response,  error,  verbose);
}


/**
 *  http_post_json_to_memory
 */
bool http_post_json_to_memory(std::string url, std::string postfileds, std::string &response,  std::string &error, bool verbose)
{
	std::list<std::string> header; 
    header.push_back("Content-Type: application/json; charset=utf-8");

	return http_post_to_memory_header(url,  postfileds,  	header, response,  error,  verbose);
}


/**
 *  http_post_to_memory_header
 */
bool http_post_to_memory_header(std::string url, std::string postfileds, 	std::list<std::string> header, std::string &response,  std::string &error, bool verbose)
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

 
    request.setOpt(new curlpp::options::HttpHeader(header)); 
    
    request.setOpt(new curlpp::options::PostFields(postfileds));

    int size = postfileds.size();
    request.setOpt(new curlpp::options::PostFieldSize(size));

		request.perform();

        response = mWriterChunk.getBuffer();
			std::cout << response << std::endl;

	}
	
	catch ( curlpp::LogicError & e )
	{
		is_error = true;
		error = e.what();
		if(verbose) {
			std::cout<< "LogicError: " << error << std::endl;
		}
	}
	
	catch ( curlpp::RuntimeError & e )
	{
		is_error = true;
		error = e.what();
		if(verbose) {
			std::cout<< "RuntimeError: " << error << std::endl;
		}
	}

	return !is_error;
}


/**
 * http_post_to_file
 */
bool http_post_to_file(std::string url,  std::string postfileds, std::string filepath, std::string &error, bool verbose)
{

		FILE *fp;
        char* filename = (char *)filepath.c_str();
		fp = fopen(filename, "wb");
		if(!fp)
		{
				error = strerror(errno);
			  return false;
		}

	bool is_error = false;

	try
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		/// Set the writer callback to enable cURL to write result in a memory area
		curlpp::options::WriteFunctionCurlFunction
			myFunction( WriteFileCallback );

		curlpp::OptionTrait<void *, CURLOPT_WRITEDATA> 
			myData(fp);

		request.setOpt(myFunction);
		request.setOpt(myData);

		/// Setting the URL to retrive.
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
	catch (curlpp::LogicError & e)
	{
		is_error = true;
		error = e.what();
	}
	catch (curlpp::RuntimeError & e)
	{
		is_error = true;
		error = e.what();
	}

	fflush(fp);
	fclose(fp);

	return !is_error;
}

