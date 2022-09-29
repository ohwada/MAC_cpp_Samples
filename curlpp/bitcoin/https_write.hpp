#pragma once
/**
 * https_write.hpp
 * 2020-07-01 K.OHWADA
 */

//  url to file or memory
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example06.cpp


#include "write_func.hpp"


// prototype
bool https_get(std::string url, std::string &error,  bool is_verify, bool is_verbose);
bool https_to_file(std::string url, std::string filepath, std::string &error, bool verbose);
bool https_to_memory(std::string url, std::string &response,  std::string &error, bool verbose);


/**
 * https_get
 */
bool https_get(std::string url, std::string &error,  bool is_verify, bool is_verbose)
{

	bool is_error = false;

	try
	{

		// That's all that is needed to do cleanup of used resources (RAII style).
		curlpp::Cleanup myCleanup;

		// Our request to be sent.
		curlpp::Easy myRequest;

		// Set the URL
		myRequest.setOpt(curlpp::Options::Url( url ));



		myRequest.setOpt(curlpp::Options::SslVerifyPeer(is_verify));

		if(is_verify){
			myRequest.setOpt(curlpp::Options::SslVerifyHost(2L) );
		} else {
			myRequest.setOpt(curlpp::Options::SslVerifyHost(0L) );
		}

		myRequest.setOpt(curlpp::Options::Verbose(is_verbose) );

		// Send request and get a result.
		myRequest.perform();
	}

	catch(curlpp::RuntimeError & e)
	{
		is_error = true;
		error = e.what();
	}

	catch(curlpp::LogicError & e)
	{
		is_error = true;
		error = e.what();
	}
    
  return !is_error;
}


/**
 * https_to_file
 */
bool https_to_file(std::string url, std::string filepath, std::string &error, bool is_verify, bool verbose)
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

		request.setOpt(curlpp::Options::SslVerifyPeer(is_verify));

		if(is_verify){
			request.setOpt(curlpp::Options::SslVerifyHost(2L) );
		} else {
			request.setOpt(curlpp::Options::SslVerifyHost(0L) );
		}

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
 *  https_to_memory
 */
bool https_to_memory(std::string url, std::string &response,  std::string &error, bool is_verify, bool verbose)
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

		request.setOpt(curlpp::Options::SslVerifyPeer(is_verify));

		if(is_verify){
			request.setOpt(curlpp::Options::SslVerifyHost(2L) );
		} else {
			request.setOpt(curlpp::Options::SslVerifyHost(0L) );
		}
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
