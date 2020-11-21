#pragma once
/**
 * curlpp sample
 * 2020-07-01 K.OHWADA
 */

//  url to file or memory
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example06.cpp

 
#include <string>
#include "write_func.hpp"


// prototype
bool url_to_file(std::string url, std::string filepath, std::string &error, bool verbose);
bool url_to_memory(std::string url, std::string &response,  std::string &error, bool verbose);



/**
 * url_to_file
 */
bool url_to_file(std::string url, std::string filepath, std::string &error, bool verbose)
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
 *  url_to_memory
 */
bool url_to_memory(std::string url, std::string &response,  std::string &error, bool verbose)
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
