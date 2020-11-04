#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

//  http to file or memory
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example06.cpp

 
#include <string>
#include "curl_write_func.hpp"


// prototype
bool http_token_to_file(std::string url, std::string access_token, std::string filepath, std::string &error, bool verbose);
bool http_token_to_memory(std::string url, std::string access_token, std::string &response,  std::string &error, bool verbose);


/**
 * http_token_to_file
 */
bool http_token_to_file(std::string url, std::string access_token, std::string filepath, std::string &error, bool verbose)
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
			myFunction(WriteFileCallback);

		curlpp::OptionTrait<void *, CURLOPT_WRITEDATA> 
			myData(fp);

		request.setOpt(myFunction);
		request.setOpt(myData);

		/// Setting the URL to retrive.
		request.setOpt(new curlpp::options::Url( url ));

		request.setOpt(new curlpp::options::Verbose( verbose ));

		std::list<std::string> headers;

    	std::string header_auth = 
		std::string( "Authorization: Bearer ") + access_token;
		if(verbose){
			std::cout << "debug: " << header_auth<< std::endl;
		}


		headers.push_back( header_auth ); 

		request.setOpt(  new curlpp::Options::HttpHeader( headers ));

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



/**
 *  http_token_to_memory
 */
bool http_token_to_memory(std::string url, std::string access_token, std::string &response,  std::string &error, bool verbose)
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

    	std::string header_auth = std::string("Authorization: Bearer ") + access_token;

		if(verbose){
			std::cout << "debug: " << header_auth<< std::endl;
		}

		headers.push_back( header_auth ); 

		request.setOpt(  new curlpp::Options::HttpHeader( headers ));

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

