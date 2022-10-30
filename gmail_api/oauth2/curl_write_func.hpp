#pragma once
/**
 * curl_write_func.hpp
 * 2022-06-01 K.OHWADA
 */

//  save response to file or memory
// original : https://github.com/jpbarrette/curlpp/blob/master/examples/example06.cpp

 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>


// prototype
size_t WriteFileCallback(char* ptr, size_t size, size_t nmemb, void *f);
void printResponse(std::string response);


/**
 * class WriterMemoryClass
 */
class WriterMemoryClass
{
public:
	// Helper Class for reading result from remote host
	WriterMemoryClass()
	{
// 20 KB
        const int MAX_FILE_LENGTH = 20000;

		this->m_pBuffer = NULL;
		this->m_pBuffer = (char*) malloc(MAX_FILE_LENGTH * sizeof(char));
		this->m_Size = 0;
	};

// destractor
	~WriterMemoryClass()
	{
		if (this->m_pBuffer)
			free(this->m_pBuffer);
	};

/**
 * Realloc
 */
	void* Realloc(void* ptr, size_t size)
	{
		if(ptr)
			return realloc(ptr, size);
		else
			return malloc(size);
	};


/**
 *  WriteMemoryCallback
 */
	// Callback must be declared static, otherwise it won't link...
	size_t WriteMemoryCallback(char* ptr, size_t size, size_t nmemb)
	{
		// Calculate the real size of the incoming buffer
		size_t realsize = size * nmemb;

		// (Re)Allocate memory for the buffer
		m_pBuffer = (char*) Realloc(m_pBuffer, m_Size + realsize);

		// Test if Buffer is initialized correctly & copy memory
		if (m_pBuffer == NULL) {
			realsize = 0;
		}

		memcpy(&(m_pBuffer[m_Size]), ptr, realsize);
		m_Size += realsize;


		// return the real size of the buffer...
		return realsize;
	};


char* getBuffer()
{
    return m_pBuffer;
}

size_t getBufferSize()
{
    return m_Size;;
}

	// Public member vars
	char* m_pBuffer;
	size_t m_Size;
}; // class



/**
 * WriteFileCallback
 */
//Callback must be declared static, otherwise it won't link...
size_t WriteFileCallback(char* ptr, size_t size, size_t nmemb, void *f)
{
	FILE *fp = (FILE *)f;
	return fwrite(ptr, size, nmemb, fp);
};


/**
 * printResponse
 */
void printResponse(std::string response) 
	{
	    std::cout << std::endl;
	    std::cout << "----------" << std::endl;
        std::cout << response << std::endl;
 	   std::cout << "----------" << std::endl;
	}

