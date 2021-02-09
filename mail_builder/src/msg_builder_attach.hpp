#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// message build utility
// g++ src/create_mail_attach.cpp -std=c++11 

#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include "msg_builder.hpp"
#include "base64.hpp"
#include "media_type.hpp"


// constant
const size_t BOUNDARY_SIZE = 16;


// prototype
bool buildMessageAttachment( std::string str_subject, std::string str_to,  std::string str_from, std::string body,  std::string filename, std::string &ret_msg, std::string &error );
bool buildAttachment(std::string filepath,  std::string &msg, std::string &error );
void getContentTypeMultipartMixed( std::string boundary, std::string  &ret_content_type, std::string &ret_boundary_begin, std::string &ret_boundary_end  );
void buildContentDisposition( char *filename, size_t filesize, char *disposition, size_t disposition_size );
void getBoundary( std::string &boundary);
bool existsFile (std::string path) ;
bool getBase64Data( std::string filepath,  std::string & ret_b64, size_t &ret_filesize,   std::string &ret_error );
bool readBinaryFile(const std::string filepath, std::vector<uint8_t> &data);
void getFileName(std::string fullpath, std::string &fname);
bool getFileExt(std::string filename, std::string &ext);
void buildContentTypeMultipartMixed(char *boundary, char *content_type, char *boundary_begin, char *boundary_end, size_t content_type_size );
void buildContentTypeMediaType( char *media_type, char *content_type, size_t content_type_size );
void buildContentDispotition( char *filename, size_t filesize, char *dispotition, size_t dispotition_size );
void getFileName(char *fullpath, char *filename ) ;
bool getFileExt(char *fullpath, char *ret_ext, char *error);
 uint8_t* readBinaryFile(char *file, size_t *size, char *error);
bool existsFile (char *path) ;
void getRandomBoundary( char *boundary);


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

    std::string content_type;
    std::string boundary_begin;
    std::string boundary_end;

    getContentTypeMultipartMixed( boundary, content_type, boundary_begin,  boundary_end  );



    std::string headers;
    buildHeaders(str_subject, str_to, str_from,  headers);


// build msg
    msg = headers;

// text
    msg += content_type;
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
    
    msg +=  std::string(boundary_end);

    return true;

}





/**
 * buildAttachment
 */
bool buildAttachment(std::string filepath,  std::string &msg, std::string &ret_error )
{

    const std::string CONTENT_TRANSFER_BASE64( 
    "Content-Transfer-Encoding: base64\r\n");

    if( !existsFile(filepath) ) {
        ret_error = "not found: " + filepath;
        return false;
    }

    std::string b64;
    size_t filesize;
  std::string error;

    bool ret1 = getBase64Data( filepath, b64, filesize,  error );

    if(!ret1){
        ret_error = error;
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

    char content_type[HEADER_SIZE];

    buildContentTypeMediaType( 
    (char *)media_type.c_str(), 
    (char *)content_type, 
    HEADER_SIZE  );

    char disposition[HEADER_SIZE];

    buildContentDisposition( 
    (char *)filename.c_str(), 
    filesize, 
    (char *)disposition,
    HEADER_SIZE );


// build msg
    msg = std::string(content_type);
    msg += CONTENT_TRANSFER_BASE64;
    msg += std::string(disposition);

	msg += CRLF; // separator

    msg += b64 + CRLF;

    return true;
}



/**
 *   buildContentDisposition
 */
void buildContentDisposition( char *filename, size_t filesize, char *disposition, size_t disposition_size )
{

    const char FORMAT_CONTENT_DISPOSITION[] = "Content-Disposition: attachment; filename=%s; size=%zu; \r\n";

    snprintf( disposition, disposition_size, FORMAT_CONTENT_DISPOSITION, filename, filesize );

}


/**
 *  getContentTypeMultipartMixed
 */
void getContentTypeMultipartMixed( std::string boundary, std::string  &ret_content_type, std::string &ret_boundary_begin, std::string &ret_boundary_end  )
{

    char content_type[HEADER_SIZE];
    char boundary_begin[HEADER_SIZE];
    char boundary_end[HEADER_SIZE];

    buildContentTypeMultipartMixed(
    (char *)boundary.c_str(), 
    (char *)content_type, 
    (char *)boundary_begin, 
    (char *)boundary_end, 
    HEADER_SIZE );

    ret_content_type = std::string( content_type );
    ret_boundary_begin = std::string(boundary_begin);
    ret_boundary_end = std::string(boundary_end);

}



/**
 *  getBoundary
 */
void getBoundary( std::string &boundary)
{

    char rand_boundary[HEADER_SIZE];

    getRandomBoundary( (char *)rand_boundary);

    boundary = std::string( rand_boundary );
}


/**
 * existsFile
 */
bool existsFile (std::string path) 
{
    return existsFile ((char *)path.c_str()) ;
}



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
 *  buildContentTypeMediaType
 */
void buildContentTypeMediaType( char *media_type, char *content_type, size_t content_type_size  )
{

    const char FORMAT_CONTENT_TYPE_MEDIA_TYPE[] = "Content-Type: %s \r\n";

    snprintf( content_type, content_type_size, 
    FORMAT_CONTENT_TYPE_MEDIA_TYPE,
    media_type );

}


/**
 *   buildContentDispotition
 */
void buildContentDispotition( char *filename, size_t filesize, char *dispotition, size_t dispotition_size )
{

    const char FORMAT_CONTENT_DISPOSITION[] = "Content-Disposition: attachment; filename=%s; size=%zu; \r\n";

    snprintf( dispotition, dispotition_size, FORMAT_CONTENT_DISPOSITION, filename, filesize );

}



/**
 *  buildContentTypeMultipartMixed
 */
void buildContentTypeMultipartMixed(char *boundary, char *content_type, char *boundary_begin, char *boundary_end, size_t content_type_size )
{

    const char CRLF[] = "\r\n";

    const char FORMAT_CONTENT_TYPE_MULTIPART_MIXED_BOUNDARY[] =
    "Content-Type: multipart/mixed; boundary=\"%s\"\r\n";

    const char BOUNDARY_FLAG[] =	"--" ;


// content type
     snprintf(content_type, content_type_size, FORMAT_CONTENT_TYPE_MULTIPART_MIXED_BOUNDARY,
    boundary );
    
	// boundary brgin
    strcpy(boundary_begin, (char *)BOUNDARY_FLAG);
    strcat(boundary_begin,    boundary);
    strcat(boundary_begin,    (char *)CRLF);


	// boundary end
    strcpy(boundary_end, (char *)BOUNDARY_FLAG);
    strcat(boundary_end,    boundary);
    strcat(boundary_end, (char *)BOUNDARY_FLAG);
    strcat(boundary_end,    (char *)CRLF);

}


/**
 *   getFileName
 */
void   getFileName(char *fullpath, char *filename ) 
{

    const char SLASH = '/';

    int len = strlen(fullpath);
    char buf[len+1];

    strcpy(buf, fullpath);

    char *basename = strrchr(buf, SLASH);
    if(basename) {
        // omit the first SLASH
        strcpy(filename, &basename[1]);
    } else {
// maybe fullpath has no directory
        strcpy(filename, fullpath);
    }

}


/**
 *   getFileExt
 */
bool getFileExt(char *fullpath, char *ret_ext, char *error) 
{

    const char DOT = '.';

    int len = strlen(fullpath);
    char buf[len+1];
    strcpy(buf, fullpath);

    char *ext = strrchr(buf, DOT);
    if(!ext) {
        strcpy(error, "not find dot");
        return false;
    }

    // omit the first DOT
    strcpy( ret_ext, &ext[1] );

    return true;
}


/**
 * readBinaryFile
 */
 uint8_t* readBinaryFile(char *file, size_t *size, char *error)
{

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "rb");
    if(!fp){

        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );

        *size = 0;
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
     
    size_t file_size = ftell(fp);

    rewind(fp);

    uint8_t* buffer = ( uint8_t *) calloc( file_size, sizeof( uint8_t) );

    if(!buffer){
        strcpy( error, " readBinaryFile calloc faild" );
        return NULL;
    }

    int read_size = fread(buffer, sizeof( uint8_t), file_size, fp);

    if (file_size == read_size){
            *size = read_size;
    } else {

            free(buffer);

            saved_errno = errno;
            strcpy( error, strerror(saved_errno) );

            *size = 0;
            buffer = NULL;
    }

    fclose(fp);

    return buffer;
}


/**
 * existsFile
 */
bool existsFile (char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    bool res = ( ret == 0 )? true: false;
    return res;
}



/**
 * getRandomBoundary
 */
void getRandomBoundary( char *boundary)
{

    const char CHAR_NULL = '\0';

    static int flag;
	
	if (flag == 0) {
		srand( (unsigned int)time(NULL) );
        rand();
		flag = 1;
	}

	char buf[BOUNDARY_SIZE + 1];
	
	const char hex[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < BOUNDARY_SIZE; i++) {
			int x = rand() % 62;
			buf[i] = hex[x];
	}

    buf[BOUNDARY_SIZE] =  CHAR_NULL;

    strcpy(boundary, (char *)buf );
}

