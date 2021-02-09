#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// build build message

 
#include "msg_builder_base64.h"
#include "base64.hpp"


// prototype
bool getBase64Data( std::string filepath,  std::string & ret_b64, size_t &ret_filesize,   std::string &ret_error );
bool readBinaryFile(const std::string filepath, std::vector<uint8_t> &data);
void buildSubjectB64( std::string subject, std::string charset, std::string &subject_b64 );
void getContentTypeMediaType( std::string media_type, std::string &msg);
void getContentDispotition( std::string filename, size_t filesize, std::string &msg );
void getContentTypeMultipartMixed(std::string boundary, std::string &ret_content_type, std::string &ret_boundary_begin, std::string &ret_boundary_end);
void getFileName(std::string fullpath, std::string &fname);
bool getFileExt(std::string filename, std::string &ext);
bool exists_file (std::string path) ;
void getBoundary( std::string &boundary);




/**
 *  getBase64Data
 */
bool getBase64Data( std::string filepath,  std::string & ret_b64, size_t &ret_filesize,   std::string &ret_error )
{

    std::vector<uint8_t> filedata;

    bool ret1 = readBinaryFile( filepath, filedata );
    if(!ret1){
        return false;
    }

    size_t filesize = filedata.size();

    std::string data;
    data.resize(  filesize);

    for(int i=0; i<filesize; i++){
        data[i] = (char)filedata[i];
    }

    std::string b64;

    encodeB64( data, b64 );

    ret_b64 = b64;
    ret_filesize = filesize;

    return true;
}


/**
 * readBinaryFile
 */
bool readBinaryFile(const std::string filepath, std::vector<uint8_t> &data)
{

	std::ifstream file(filepath.c_str(), std::ios::binary | std::ios::in);
	if (!file){
		return false;
    }

	char c = file.get();
	for (; file.good(); c = file.get())
	{
		if (file.bad()){
			break;
        }

		data.push_back(c);

	} // for

    file.close();
    return true;
}



/**
* buildSubjectB64
 */
void buildSubjectB64( std::string subject, std::string charset, std::string &subject_b64 )
{

    std::string b64;
    encodeB64(subject, b64);

    char formated[B64_FORMATED_SIZE];

    buildFormatB64( 
    (char *)b64.c_str(),
    (char *)charset.c_str(), 
    (char *)formated );

    subject_b64 = std::string(formated);
    
}


/**
 *   getContentTypeMediaType
 */
void getContentTypeMediaType( std::string media_type, std::string &msg)
{

    char content_type[HEADER_SIZE];

    buildContentTypeMediaType(
    (char *)media_type.c_str(), 
    (char *)content_type );

    msg = std::string(content_type);

}



/**
 *   getContentDispotition
 */
void getContentDispotition( std::string filename, size_t filesize, std::string &msg )
{

    char dispotition[HEADER_SIZE];

    buildContentDispotition( 
    (char *)filename.c_str(), 
    filesize, 
    (char *)dispotition );

    msg = std::string(dispotition);

}



/**
 *  getContentTypeMultipartMixed
 */
void getContentTypeMultipartMixed(std::string boundary, std::string &ret_content_type, std::string &ret_boundary_begin, std::string &ret_boundary_end)
{

    char type[HEADER_SIZE];
    char begin[HEADER_SIZE];
    char end[HEADER_SIZE];

    buildContentTypeMultipartMixed(
    (char *)boundary.c_str(), 
    (char *)type, 
    (char *)begin, 
    (char *)end );

    ret_content_type = std::string(type);
    ret_boundary_begin = std::string(begin);
    ret_boundary_end = std::string(end);

}




/**
 *  getFileName
 */
void getFileName(std::string fullpath, std::string &fname)
{

    const char SLASH = '/';

	std::string fn(fullpath);
	std::string::size_type p = fn.find_last_of(SLASH);

	if (p == std::string::npos){
// maybe fullpath has no directory
        fname = fullpath;
	} else {
		p += 1; // get past folder delimeter
		fname = fn.substr(p, fn.length() - p);
	}

}


/**
 *  getFileExt
 */
bool getFileExt(std::string filename, std::string &ext)
{

    const char DOT = '.';

	std::string fn(filename);
	std::string::size_type p = fn.find_last_of(DOT);

	if (p == std::string::npos){
        return false;
    } else {
		p += 1; // get past folder delimeter
		ext = fn.substr(p, fn.length() - p);
	}

    return true;
}



/**
 * exists_file
 */
bool exists_file (std::string path) 
{
    return exists_file ((char *)path.c_str()) ;
}


/**
 *  getBoundary
 */
void getBoundary( std::string &boundary)
{
    char rand_boundary[200];
    getRandomBoundary( (char *)rand_boundary);
    boundary = std::string( rand_boundary );
}
