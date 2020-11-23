#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// message build utility
// suport file atachment
// suport UTF-8 encoding

#include <string>
#include "base64.hpp"
#include "file_util.hpp"
#include "parse_filename.hpp"
#include "ustd_string.h"
#include "msg_send.h"
#include "media_type.hpp"


// constant
const std::string CRLF( "\r\n");

const std::string BOUNDARY_FLAG	( "--" );

const std::string MIME_VER( "Mime-Version: 1.0\r\n" );

const std::string CONTENT_TYPE_TEXT_UTF8_FLOWED( 
"Content-Type: text/plain; charset=UTF-8; format=flowed\r\n" );

const std::string CONTENT_TYPE_TEXT_USASCII_FLOWED(
"Content-Type: text/plain; charset=us-ascii;  format=flowed\r\n");

const std::string CONTENT_TYPE_OCTET_STREAM("Content-Type: application/octet-stream \r\n");


const std::string CONTENT_TRANSFER_BASE64( "Content-Transfer-Encoding: base64\r\n" );


const char CONTENT_TYPE_MULTITYPE_BOUNDARY_FORMAT[] =
"Content-Type: multipart/mixed; boundary=\"%s\"\r\n";

const char CONTENT_DISPOSITION_FORMAT[] = "Content-Disposition: attachment; filename=%s; size=%d; \r\n";

const char CONTENT_TYPE_MEDIA_TYPE_FORMAT[] = "Content-Type: %s \r\n";

const char CONTENT_TYPE_CHARSET_FORMAT[] = "Content-Type: text/plain; charset=\"%s\" \r\n";

const char SUBJECT_CHARSET_FORMAT[] = 
"Subject: =?%s?B?%s?= \r\n"; 


// prototype
bool buildMessageAttachment( std::string str_subject, std::string str_from, std::string str_to, std::string body,  std::string filename, std::string &ret_msg);
void buildMessageBase64( std::string subject, std::string charset,  std::string str_from, std::string str_to, std::string body,  std::string &ret_msg);
void buildHeaderContentTypeCharset( const std::string charset, std::string &header );
void buildHeaderSubjectBase64( const std::string subject, const std::string charset, std::string &header );
 size_t base64encode( const std::string str_data, std::string &ret_b64 );
void buildSendRequestJson(std::string msg, std::string &request);
void saveMessage(std::string msg);
void printRequrst(std::string request);
bool base64File(const std::string filepath, std::string &ret_b64) ;
std::string get_boundary(void);


/**
 * buildMessageAttachment
 * RFC 2822 format
 */
bool buildMessageAttachment( std::string str_subject, std::string str_from, std::string str_to, std::string body,  std::string filepath, std::string &ret_msg)
{

std::vector<char> filedata;
bool ret1 = readBinaryFile( filepath, filedata );
    if(!ret1){
        return false;
    }

    int filesize = filedata.size();

	std::vector<char> outdata;
	ustd::string::base64encode(&filedata[0], filedata.size(), outdata);

    size_t outdata_size = outdata.size();

    std::string b64;
    b64.resize(outdata_size);

    for(int i=0; i<outdata_size; i++){
        b64[i] = (char)outdata[i];
    }

    std::string filename = getFileNameWithExt( filepath );

    std::string ext = getFileNameExt( filepath );

    std::string media_type;
    getMediaType(ext, media_type);

    char* subject =  (char *)str_subject.c_str();
    char* from =  (char *)str_from.c_str();
    char* to =  (char *)str_to.c_str();


	// boundary
		    std::string boundary( get_boundary() );
		    std::string boundary_begin = BOUNDARY_FLAG + boundary + CRLF;
		    std::string boundary_end = BOUNDARY_FLAG + boundary + BOUNDARY_FLAG +CRLF;


    std::string msg;

   size_t BUFSIZE = 100;
    char buf[BUFSIZE];

// headers
    snprintf(buf, BUFSIZE, "Subject: %s\r\n", subject);
    msg += std::string(buf);


    snprintf(buf, BUFSIZE, "To: %s\r\n",  to);
    msg += std::string(buf);


    snprintf(buf, BUFSIZE, "From: %s\r\n",  from );
    msg += std::string(buf);

    snprintf(buf, BUFSIZE, "Date: %s\r\n",  getDate() );
    msg += std::string(buf);

    snprintf(buf, BUFSIZE, "Message-ID: <%s>\r\n", getMessageID() );
    msg += std::string(buf);

        // mime version
		    msg +=  MIME_VER;

// multitype brgin
     snprintf(buf, BUFSIZE, CONTENT_TYPE_MULTITYPE_BOUNDARY_FORMAT,
    (char *)boundary.c_str() );
		    msg += std::string( buf );
		    msg += CRLF;

		// first part of body, boundary header and message
		msg += boundary_begin;
		msg +=CONTENT_TYPE_TEXT_USASCII_FLOWED;
		msg += CONTENT_TRANSFER_7BIT;

		// split body
		msg += CRLF;

		// message
        msg += body + CRLF;

// attachment
		msg += boundary_begin;

    snprintf( buf, BUFSIZE, 
    CONTENT_TYPE_MEDIA_TYPE_FORMAT,
    (char *)media_type.c_str() );
    msg += std::string(buf);

    msg += CONTENT_TRANSFER_BASE64;

    snprintf( buf, BUFSIZE, CONTENT_DISPOSITION_FORMAT, (char *)filename.c_str(), filesize);
    msg += std::string(buf);

		// split body
		msg += CRLF;

        msg += b64 + CRLF;
    
    msg +=  boundary_end;

    ret_msg= msg;
    return true;
}


/**
 * buildMessageBase64
 * RFC 2822 format
 */
void buildMessageBase64( std::string subject, std::string charset,  std::string str_from, std::string str_to, std::string body,  std::string &ret_msg)
{

    char* from =  (char *)str_from.c_str();
    char* to =  (char *)str_to.c_str();

    std::string msg;

   size_t BUFSIZE = 100;
    char buf[BUFSIZE];

// headers

    std::string header_subject;
    buildHeaderSubjectBase64( subject, charset, header_subject );

    msg += header_subject;


    snprintf(buf, BUFSIZE, "To: %s\r\n",  to);
    msg += std::string(buf);


    snprintf(buf, BUFSIZE, "From: %s\r\n", from);
    msg += std::string(buf);

    snprintf(buf, BUFSIZE, "Date: %s\r\n",  getDate() );
    msg += std::string(buf);

    snprintf(buf, BUFSIZE, "Message-ID: <%s>\r\n", getMessageID() );
    msg += std::string(buf);


    std::string header_cotent_type;
    buildHeaderContentTypeCharset( charset,  header_cotent_type );
    msg += header_cotent_type;

    msg +=  CONTENT_TRANSFER_BASE64;

// heder part end
    msg += CRLF;

    std::string b64;
    base64encode( body, b64 );

    msg += b64 + CRLF;

    ret_msg= msg;
}


/**
* buildHeaderContentTypeCharset
 */
void buildHeaderContentTypeCharset( const std::string charset, std::string &header )
{
    const size_t BUFSIZE = 200;
    char buf[BUFSIZE];

    snprintf(buf, BUFSIZE,  CONTENT_TYPE_CHARSET_FORMAT, 
    (char *)charset.c_str() );

    header =  std::string( buf );

}


/**
* buildHeaderSubjectBase64
 */
void buildHeaderSubjectBase64( const std::string subject, const std::string charset, std::string &header )
{
    const size_t BUFSIZE = 200;
    char buf[BUFSIZE];

    std::string b64;
    base64encode( subject, b64 );

    snprintf(buf, BUFSIZE, SUBJECT_CHARSET_FORMAT,     (char *)charset.c_str(), 
    (char *)b64.c_str() );

    header =  std::string( buf );

}


/**
* base64encode
 */
 size_t base64encode( const std::string str_data, std::string &ret_b64 )
{
    const char *chars_data = (char *)str_data.c_str();
    const int len = str_data.length();
    std::vector<char> vec_b64;  
    size_t size = ustd::string::base64encode( chars_data, len, vec_b64);



    size_t vec_size = vec_b64.size();
    std::string b64;
    b64.resize(vec_size);

    for(int i=0; i<vec_size; i++){
        b64[i] = (char)vec_b64[i];;
    }

    ret_b64 = b64;

    return size;
}



/**
 * buildSendRequestJson
 * base64url encoding
 */
void buildSendRequestJson(std::string msg, std::string &request)
{

// over 1MB when image
    std::string b64 = base64_encode(msg);

    request = std::string( "{ \"raw\": \"" ) 
    + b64 + std::string( "\" }" );

}


/**
* base64File
 */
bool base64File(const std::string filepath, std::string &ret_b64)
{

    std::vector<char> filedata;
    bool ret = readBinaryFile(filepath, filedata);
    if(!ret){
        return false;
    }

	std::vector<char> outdata;
	ustd::string::base64encode(&filedata[0], filedata.size(), outdata);

    size_t outdata_size = outdata.size();
    std::string b64;
    b64.resize(outdata_size);

    for(int i=0; i<outdata_size; i++){
        b64[i] = (char)outdata[i];
    }

    ret_b64 = b64;
    return true;
}



/**
 * get_boundary
 */
std::string get_boundary(void)
{
		std::string boundary;
		boundary.reserve(16);
		const char hex[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < 16; ++i)
		{
			int x = rand() % 62;
			boundary.append(1, hex[x]);
		}

		return boundary;
}


/**
 * saveMessage
 */
void saveMessage(std::string msg)
{
    std::string file;
    getTimestampFileName("mail",  "eml",  file);
    bool ret = writeTextFile( file, msg );
    if(ret){
         std::cout << "saved to: " << file << std::endl;
    }
}


/**
 * printRequrst
 */
void printRequrst(std::string request) 
	{
	    std::cout << std::endl;
	    std::cout << "----------" << std::endl;
        std::cout << request << std::endl;
 	   std::cout << "----------" << std::endl;
	}