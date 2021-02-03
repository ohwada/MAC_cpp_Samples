#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// message build utility


#include <fstream>
#include <string>
#include <vector>
#include "msg_builder.h"
#include "msg_builder_base64.h"
#include "media_type.hpp"


// prototype
bool buildMessageAttachment( std::string str_subject, std::string str_to,  std::string str_from, std::string body,  std::string filename, std::string &ret_msg, std::string &error );
void buildMessageUtf8( std::string subject, std::string to, std::string from,  std::string body,  std::string &msg );
void buildMessageCharset( std::string subject,  std::string to, std::string from, std::string body,   std::string charset,  std::string &ret_msg );
void buildSubjectB64( const std::string subject, const std::string charset, std::string &subject_b64 );
void buildMessageText(std::string subject, std::string to, std::string from, std::string body, std::string &msg);
void buildHeaders(std::string subject, std::string to, std::string from,  std::string &msg);
void saveMessage(std::string msg);
void printMessage(std::string msg) ;
 int base64encode( const std::string str_data, std::string &ret_b64 );
bool getBase64Data(std::string filepath, std::string &ret_b64, size_t &filesize );
bool buildAttachment(std::string filepath,  std::string &msg, std::string &error );
void getBoundary( std::string &boundary);
void getContentTypeMediaType( std::string media_type, std::string &msg);
void getContentDispotition( std::string filename, size_t filesize, std::string &msg);
void getContentTypeMultipartMixed(std::string boundary, std::string &content_type, std::string &boundary_begin, std::string &boundary_end);
void getFileName(std::string fullpath, std::string &fname);
bool getFileExt(std::string filename, std::string &ext);
bool readBinaryFile(const std::string filepath, std::vector<char> &data);


/**
 * buildMessage
 * RFC 2822 format
 * http://srgia.com/docs/rfc2822j.html
 */
void buildMessageText(std::string subject, std::string to, std::string from, std::string body, std::string &msg)
{

    std::string  headers;
    buildHeaders(subject, to,  from,  headers);

    msg = headers;
    msg += CONTENT_TYPE_TEXT_PLANE_USASCII;
    msg += CONTENT_TRANSFER_7BIT;

    msg += CRLF;  // separetor

    msg += body + CRLF;

}


/**
 *  buildHeaders
 */
void buildHeaders(std::string subject, std::string to, std::string from,  std::string &ret_headers)
{

    char headers[ HEADERS_SIZE];

    buildHeaders(
    (char *)subject.c_str(), 
    (char *)to.c_str(), 
    (char *)from.c_str(), 
    (char *)headers );

    ret_headers = std::string(headers);

}


/**
 * printMessage
 */
void printMessage(std::string msg) 
	{
        printMsg( (char *)msg.c_str() );
	}


/**
 * readBinaryFile
 */
bool readBinaryFile(const std::string filepath, std::vector<char> &data)
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
 * saveMessage
 */
void saveMessage(std::string msg)
{
    saveMsg( (char *)msg.c_str() );
}


/**
 * buildMessageUtf8
 */
void buildMessageUtf8( std::string subject, std::string to, std::string from,  std::string body,  std::string &msg )
{

    buildMessageCharset( subject, to, from, body,  CHARSET_UTF8,  msg );

}


/**
 * buildMessageCharset
 */
void buildMessageCharset( std::string subject,  std::string to, std::string from, std::string body,   std::string charset,  std::string &msg )
{

    std::string subject_b64;

    buildSubjectB64( subject, charset, subject_b64 );

    std::string headers;
    buildHeaders(subject_b64, to, from,  headers);

    std::string body_b64;
    base64encode( body, body_b64 );


// build msg
    msg += headers;

    msg += CONTENT_TYPE_TEXT_PLANE_UTF8;

    msg +=  CONTENT_TRANSFER_BASE64;

    msg += CRLF;  // separater

    msg += body_b64;

    msg += CRLF;

}


/**
* buildSubjectB64
 */
void buildSubjectB64( const std::string subject, const std::string charset, std::string &subject_b64 )
{

    std::string b64;
    base64encode( subject, b64 );


    char formated[200];

    buildFormatB64(
    (char *)b64.c_str(), 
    (char *)charset.c_str(), 
    (char *)formated );

    subject_b64 =  std::string( formated );

}


/**
 * buildMessageAttachment
 * RFC 2822 format
 */
bool buildMessageAttachment( std::string str_subject, std::string str_to, std::string str_from, std::string body,  std::string filepath, std::string &msg, std::string &ret_error )
{

    std::string attach;
    std::string error;

    bool ret = buildAttachment( filepath,  attach, error );

    if(!ret){
        ret_error = error;
        return false;
    }

	// boundary
    std::string boundary;
    getBoundary( boundary );

    std::string content_type_multipart;
    std::string boundary_begin;
    std::string boundary_end;
    getContentTypeMultipartMixed( boundary,  content_type_multipart,  boundary_begin, boundary_end );


    std::string headers;
    buildHeaders(str_subject, str_to, str_from,  headers);


// build msg
    msg = headers;

// text
    msg += content_type_multipart;
    msg += CRLF;
    msg += boundary_begin;
    msg += CONTENT_TYPE_TEXT_PLANE_USASCII;
    msg += CONTENT_TRANSFER_7BIT;

	msg += CRLF; // saparator

    msg += body + CRLF;


// attachment
    msg += boundary_begin;
    msg += attach;
    msg += CRLF;
    
    msg +=  boundary_end;

    return true;

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


/**
 *  getBase64Data
 */
bool getBase64Data(std::string filepath, std::string &ret_b64, size_t &ret_filesize)
{

    std::vector<char> filedata;

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

    base64encode( data, b64 );

    ret_b64 = b64;
    ret_filesize = filesize;

    return true;
}



/**
 * buildAttachment
 */
bool buildAttachment(std::string filepath,  std::string &msg, std::string &error )
{

    if( !existsFile( (char *)filepath.c_str() ) ) {
        error = "not found: " + filepath;
        return false;
    }

    std::string b64;
    size_t filesize;

    bool ret1 = getBase64Data(filepath, b64, filesize);

    if(!ret1){
        error = "getBase64Data faild";
        return false;
    }

    std::string filename;
    getFileName( filepath, filename );

    std::string ext;
    bool ret2 = getFileExt( filepath, ext );
    if(!ret2){
        error = " getFileExt faild";
        return false;
    }

    std::string media_type;
    getMediaType(ext, media_type);

    std::string content_type_file;	
    getContentTypeMediaType( media_type, content_type_file );

    std::string content_disposition;	
    getContentDispotition( filename, filesize, content_disposition );

// build msg
    msg = content_type_file;
    msg += CONTENT_TRANSFER_BASE64;
    msg += content_disposition;

	msg += CRLF; // separator

    msg += b64 + CRLF;

    return true;
}


/**
 *   getContentTypeMediaType
 */
void getContentTypeMediaType( std::string media_type, std::string &msg)
{

    char content_type[200];

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

    char dispotition[200];
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

    char type[200];
    char begin[200];
    char end[200];

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
* base64encode
 */
 int base64encode( const std::string str_data, std::string &ret_b64 )
{

    const char *data = (char *)str_data.c_str();
    const int len = str_data.length();

	std::string encode;
	encode.resize( Base64encode_len(len) );
	int size = Base64encode( &encode[0], data, len );

    std::string b64;
    b64.resize(size);

    for(int i=0; i<size; i++){
        b64[i] = encode[i];
    }

    ret_b64 = b64;

    return size;
}

