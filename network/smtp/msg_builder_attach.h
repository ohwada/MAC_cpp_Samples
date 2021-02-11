#pragma once
/**
 *  smtp client sample
 * 2021-02-01 K.OHWADA
 */


// build build message


#include <sys/stat.h>
#include "msg_builder.h"
#include "base64.h"
#include "media_type.h"


// constant
const size_t ATTACH_ERROR_SIZE = 100;
const size_t BOUNDARY_SIZE = 16;
const char SUBTYPE_MIXED[] = "mixed";
const char SUBTYPE_ALTERNATIVE[] = "alternative";


// prototype
char* buildMsgAttachment( char *subject, char *to, char *from, char *body,  char *filepath, char *ret_error );
char* buildAttachment(char *filepath,  size_t *msg_size, char *ret_error );
void buildContentTypeMultipartMixed( char *boundary, char *content_type, char *boundary_begin, char *boundary_end, size_t content_type_size );

void buildContentTypeMultipart( char *subtype, char *boundary, char *content_type, char *boundary_begin, char *boundary_end, size_t content_type_size );
void buildContentTypeMediaType( char *media_type, char *content_type, size_t content_type_size );
void buildContentDispotition( char *filename, size_t filesize, char *dispotition, size_t dispotition_size );
void getFileName(char *fullpath, char *filename ) ;
bool getFileExt(char *fullpath, char *ret_ext, char *error);
 uint8_t* readBinaryFile(char *file, size_t *size, char *error);
bool existsFile (char *path) ;
void getRandomBoundary( char *boundary);
char* getBase64Data( char *filepath,  size_t *ret_filesize,      int *ret_encode_len, char *ret_error);
 char* base64encode( char *data, int *ret_size, char *error );




/**
 * buildMsgAttachment
 */
char* buildMsgAttachment( char *subject, char *to, char *from, char *body,  char *filepath, char *ret_error )
{

   size_t attach_size;
    char error[ATTACH_ERROR_SIZE];

    char *attachment = buildAttachment( filepath,  &attach_size, (char *)error );

    if( !attachment ) {
        strcpy(ret_error, error);
        return NULL;
    }


    size_t size = attach_size + HEADERS_SIZE + BODY_SIZE  ;  char *msg = (char *)calloc( size, sizeof(char) );

    if(!msg){
        strcpy( ret_error, "buildMessageAttachment calloc faild");
        free(attachment);
        return NULL;
    }


	// boundary
   char boundary[BOUNDARY_SIZE + 1];
    getRandomBoundary( (char *)boundary );

    char content_type_multipart[HEADER_SIZE];
    char * boundary_begin[HEADER_SIZE];
    char * boundary_end[HEADER_SIZE];

    buildContentTypeMultipartMixed( 
    (char *)boundary,  
    (char *)content_type_multipart,  
    (char *)boundary_begin, 
    (char *)boundary_end, HEADER_SIZE );


    char * headers[HEADERS_SIZE];
    buildHeaders( subject, to, from,  (char *)headers );


// build msg
    strcpy( msg,  (char *)headers);
    strcat(msg, (char *)content_type_multipart);


// body
    strcat(msg, (char *)boundary_begin);
    strcat(msg, 
    (char *)CONTENT_TYPE_TEXT_PLANE_USASCII);
    strcat(msg, (char *)CONTENT_TRANSFER_7BIT);

    strcat(msg, (char *)CRLF ); // saparator

    strcat(msg, (char *)body);
    strcat(msg, (char *)CRLF ); 

// attachment
    strcat(msg, (char *)boundary_begin );

   strcat( msg, (char *)attachment );
    strcat(msg, (char *)CRLF ); 

    strcat(msg, (char *)boundary_end );


    free(attachment);

    return msg;

}



/**
 * buildAttachment
 */
char* buildAttachment(char *filepath,  size_t *msg_size, char *ret_error )
{

const char CONTENT_TRANSFER_BASE64[] = 
"Content-Transfer-Encoding: base64\r\n" ;


    const size_t ATTACH_HEADER_SIZE = 1024;

    const size_t FILENAME_SIZE = 100;
    char filename[FILENAME_SIZE];  
    char ext[FILENAME_SIZE]; 


   const size_t MEDIATYPE_SIZE = 100;
    char media_type[MEDIATYPE_SIZE];


    if( !existsFile( filepath ) ) {
        strcpy(ret_error,  "not found: ");
        strcat(ret_error, filepath);
        return NULL;
    }

    size_t filesize;
    int b64_len;
    char error[ATTACH_ERROR_SIZE];

    char* b64 = getBase64Data( filepath,  &filesize, &b64_len, (char *)error );

    if(!b64){
        strcpy( ret_error, (char *)error );
        return NULL;
    }

    size_t size = b64_len +  ATTACH_HEADER_SIZE;

    char* msg = (char *)calloc( size, sizeof(char) );

    if(!msg){
        strcpy( ret_error, "getBase64Data calloc faild" );
        free(b64);
        return NULL;
    }


    getFileName( filepath, (char *)filename ) ;


    bool ret = getFileExt( filepath, (char *)ext, (char *)error );

    if(!ret){
        strcpy( ret_error, (char *)error );
        return NULL;
    }

    getMediaType( (char *)ext, (char *)media_type);


// content_type_file
    char content_type_file[HEADER_SIZE];	

    buildContentTypeMediaType( (char *)media_type, (char *)content_type_file, HEADER_SIZE );

//  content_disposition
    char content_disposition[HEADER_SIZE];

    buildContentDispotition( (char *)filename,  filesize, (char *) content_disposition, HEADER_SIZE );

// build msg
    strcpy( msg, (char *)content_type_file );
    strcat(msg, (char *)CONTENT_TRANSFER_BASE64 );
    strcat( msg, (char *)content_disposition );

	strcat(msg, (char *)CRLF); // separator

    strcat(msg, (char *)b64);
	strcat(msg, (char *)CRLF); 

    *msg_size = size;

    free(b64);

    return msg;
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
void buildContentTypeMultipartMixed( 
char *boundary, char *content_type, char *boundary_begin, char *boundary_end, size_t content_type_size )
{

    buildContentTypeMultipart( 
    (char *)SUBTYPE_MIXED, 
    boundary, content_type, boundary_begin, boundary_end, content_type_size );

}



/**
 *  buildContentTypeMultipart
 */
void buildContentTypeMultipart( char *subtype, 
char *boundary, char *content_type, char *boundary_begin, char *boundary_end, size_t content_type_size )
{

    const char FORMAT_CONTENT_TYPE_MULTIPART_BOUNDARY[] =
    "Content-Type: multipart/%s; boundary=\"%s\"\r\n";

    const char BOUNDARY_FLAG[] =	"--" ;

// content type
     snprintf(content_type, content_type_size, FORMAT_CONTENT_TYPE_MULTIPART_BOUNDARY,
    subtype, boundary );
    

// RFC 822 
// The CRLF preceding the boundary delimiter line is 
// conceptually attached to the boundary 

	// boundary brgin
    strcpy(boundary_begin,    (char *)CRLF);
    strcat(boundary_begin, (char *)BOUNDARY_FLAG);
    strcat(boundary_begin,    boundary);
    strcat(boundary_begin,    (char *)CRLF);


	// boundary end    
    strcpy(boundary_end,    (char *)CRLF);
    strcat(boundary_end, (char *)BOUNDARY_FLAG);
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



/**
 *  getBase64Data
 */
char* getBase64Data( char *filepath,  size_t *ret_filesize,      int *ret_encode_len, char *ret_error)
{


    uint8_t *filedata;
    size_t filesize;
    char error[ATTACH_ERROR_SIZE];

    filedata = readBinaryFile( filepath, &filesize, (char *)error );

    if(!filedata){
        strcpy(ret_error, error);
        return NULL;
    }


    int encode_len = Base64encode_len(filesize);

    char *encode = (char *)calloc( encode_len, sizeof(char) );

    if(!encode){
        strcpy(ret_error, "getBase64Data calloc faild");
        return NULL;
    }

    int ret = Base64encode( encode,  (char *)filedata,  filesize );
    

    *ret_filesize = filesize;

    *ret_encode_len = encode_len;

    free(filedata);

    return encode;
}



/**
* base64encode
 */
 char* base64encode( char *data, int *ret_size, char *error )
{

    size_t len = strlen(data);


	int encode_len = Base64encode_len(len);


    char *encode = (char *)calloc( encode_len, sizeof(char) );

    if(!encode){
        strcpy(error, "calloc faild");
        return NULL;
    }

	int size = Base64encode( encode, data, len );

    *ret_size = size;

    return encode;
}


