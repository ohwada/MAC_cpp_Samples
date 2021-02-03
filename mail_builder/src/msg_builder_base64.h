#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// build build message

#include <sys/stat.h>
#include "base64.h"



// constant
const size_t BOUNDARY_SIZE = 16;
const char BOUNDARY_FLAG[] =	"--" ;
const char CHARSET_UTF8[] = "UTF-8";
const char CONTENT_TYPE_TEXT_PLANE_UTF8[] =
"Content-Type: text/plain; charset=utf-8; \r\n";
const char CONTENT_TRANSFER_BASE64[] = 
"Content-Transfer-Encoding: base64\r\n" ;

const char FORMAT_CONTENT_TYPE_MULTIPART_MIXED_BOUNDARY[] =
"Content-Type: multipart/mixed; boundary=\"%s\"\r\n";
const char FORMAT_CONTENT_DISPOSITION[] = "Content-Disposition: attachment; filename=%s; size=%zu; \r\n";
const char FORMAT_CONTENT_TYPE_MEDIA_TYPE[] = "Content-Type: %s \r\n";
const char FORMAT_B64[] = 
"=?%s?B?%s?="; 



// prototype
char* buildAttachment(char *filepath,  size_t *msg_size, char *ret_error );
char* getBase64Data( char *filepath,  size_t *ret_filesize,      int *ret_encode_len, char *ret_error);
void buildContentTypeMultipartMixed(char *boundary, char *content_type, char *boundary_begin, char *boundary_end);
void buildContentTypeMediaType( char *media_type, char *content_type );
void buildContentDispotition( char *filename, size_t filesize, char *dispotition );
void getFileName(char *fullpath, char *filename ) ;
bool getFileExt(char *fullpath, char *ret_ext, char *error);
 uint8_t* readBinaryFile(char *file, size_t *size, char *error);
bool existsFile (char *path) ;
void getRandomBoundary( char *boundary);
bool buildSubjectB64( char *subject, char *charset, char *subject_b64, char *ret_error );
void buildFormatB64(char *b64, char *charset, char *formated );
 char* base64encode( char *data, int *ret_size, char *error );


/**
 *  buildContentTypeMediaType
 */
void buildContentTypeMediaType( char *media_type, char *content_type )
{

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    snprintf( buf, BUFSIZE, 
    FORMAT_CONTENT_TYPE_MEDIA_TYPE,
    media_type );

    strcpy(content_type, (char *)buf );

}


/**
 *   buildContentDispotition
 */
void buildContentDispotition( char *filename, size_t filesize, char *dispotition )
{

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    snprintf( buf, BUFSIZE, FORMAT_CONTENT_DISPOSITION, filename, filesize );

    strcpy(dispotition, (char *)buf );

}


/**
 *  getBase64Data
 */
char* getBase64Data( char *filepath,  size_t *ret_filesize,      int *ret_encode_len, char *ret_error)
{


    uint8_t *filedata;
    size_t filesize;
    char error[100];

    filedata = readBinaryFile( filepath, &filesize, (char *)error );

    if(!filedata){
        strcpy(ret_error, error);
        return NULL;
    }


    int encode_len = Base64encode_len(filesize);


    char *encode = (char *)malloc(encode_len);

    if(!encode){
        strcpy(ret_error, "getBase64Data malloc faild");
        return NULL;
    }

    int ret = Base64encode( encode,  (char *)filedata,  filesize );
    

    *ret_filesize = filesize;

    *ret_encode_len = encode_len;

    free(filedata);

    return encode;
}



/**
 *  buildContentTypeMultipartMixed
 */
void buildContentTypeMultipartMixed(char *boundary, char *content_type, char *boundary_begin, char *boundary_end)
{

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

// content type
     snprintf(buf, BUFSIZE, FORMAT_CONTENT_TYPE_MULTIPART_MIXED_BOUNDARY,
    boundary );
    
    strcpy(content_type, (char *)buf );

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

    uint8_t* buffer = ( uint8_t *) malloc(sizeof( uint8_t) * file_size );

    if(!buffer){
        strcpy( error, " readBinaryFile malloc faild" );
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


/**
* buildSubjectB64
 */
bool buildSubjectB64( char *subject, char *charset, char *subject_b64, char *ret_error )
{
    const size_t BUFSIZE = 200;
    char buf[BUFSIZE];

    int b64_size;
    char error[100];

    char* b64 = base64encode( subject, &b64_size, (char *)error );

    if(!b64){
        strcpy(ret_error, error);
        return false;
    }

    char formated[200];
    buildFormatB64( (char *)b64, (char *)charset, (char *)formated );

    strcpy(subject_b64, (char *)formated );
    free(b64);

    return true;
}


/**
*  buildFormatB64
 */
void buildFormatB64(char *b64, char *charset, char *formated )
{

    const size_t BUFSIZE = 200;
    char buf[BUFSIZE];

    snprintf(buf, BUFSIZE,  (char *)FORMAT_B64, charset, 
    b64 );

    strcpy( formated, buf );
}


/**
* base64encode
 */
 char* base64encode( char *data, int *ret_size, char *error )
{

    size_t len = strlen(data);


	int encode_len = Base64encode_len(len);


    char *encode = (char *)malloc(encode_len);

    if(!encode){
        strcpy(error, "malloc faild");
        return NULL;
    }

	int size = Base64encode( encode, data, len );

    *ret_size = size;

    return encode;
}


