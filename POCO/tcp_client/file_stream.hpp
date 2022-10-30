#pragma once
/**
 *  file_stream.cpp
 * 2022-06-01 K.OHWADA
 */

// https://docs.pocoproject.org/current/Poco.FileInputStream.html
// https://docs.pocoproject.org/current/Poco.FileOutputStream.html

#include <iostream>
#include <string>
#include "Poco/FileStream.h"
 #include "Poco/Exception.h"

// prototype
std::string file_text_read( std::string inpath);
bool file_text_write(std::string outpath, std::string text);
std::string file_binary_read( std::string inpath, size_t &data_size);
bool file_binary_write(std::string outpath, std::string data, size_t data_size);


/**
 *  file_text_read
 */
std::string file_text_read( std::string inpath)
{
    const char NUL = '\0';

    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];

    Poco::FileInputStream fis;

try {
    fis.open(inpath, std::ios::in);
	fis.read((char*)buf, BUFSIZE);
	std::streamsize len = fis.gcount();
	if (len>0) {
			buf[len]= NUL;
    }
    fis.close();
}
catch( Poco::FileException e)
{
    std::cerr << e.what() << std::endl;
}

    std::string text(buf);

    return text;
}


/**
 *  file_text_write
 */

bool file_text_write(std::string outpath, std::string text)
{
    bool is_error = false;

    Poco::FileOutputStream fos;

try {

    fos.open(outpath, std::ios::out);

    fos.write((char*)text.c_str(), text.size() );

    fos.close();

}
catch( Poco::FileException e)
{
    is_error = true;
    std::cerr << e.what() << std::endl;
}

    return ! is_error;
}


/**
 *  file_binary_read
 */
std::string file_binary_read( std::string inpath, size_t &data_size)
{

    const size_t BUFSIZE = 1024; 
    int count = 0;
    std::string data;

    Poco::FileInputStream fis;

try {
    fis.open(inpath, std::ios::in);

    while(!fis.eof())
    {
        char buf[BUFSIZE];
	    fis.read((char*)buf, BUFSIZE);
	    std::streamsize len = fis.gcount();
	    if (len>0) {
            std::string str(buf, len);
            data += str;
            count += len;
            // std::cout << "len: " << len << std::endl;
        } else {
            break;
        }
    } // while

    fis.close();
}
catch( Poco::FileException e)
{
    std::cerr << e.what() << std::endl;
}

    data_size = count;
    return data;
}


/**
 *  file_binary_write
 */

bool file_binary_write(std::string outpath, std::string data, size_t data_size)
{
    bool is_error = false;

    Poco::FileOutputStream fos;

try {

    fos.open(outpath, std::ios::out);

    fos.write( (char *)data.c_str(), data_size);

    fos.close();

}
catch( Poco::FileException e)
{
    is_error = true;
    std::cerr << e.what() << std::endl;
}

    return ! is_error;
}
