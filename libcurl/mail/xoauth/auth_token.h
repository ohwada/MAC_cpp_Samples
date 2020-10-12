#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// function for oauth

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8

#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include  <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "http_post.h"



// prototype
int getRefreshTokenToFile(char * client_id, char * client_secret,  char * refresh_file, int verbose);
void buildAuthorizationCodeUrl(char * client_id, char * buf, size_t bufsize );
int getEnterAuthorizationCode(char * url, char * auth_code);
void  buildRefreshTokenRequest(char * client_id, char * client_secret, char * auth_code, char * buf, size_t bufsize);
void buildAccessTokenRequest( char * client_id, char * client_secret, char * refresh_token, char * data, size_t bufsize );
int  getRefreshToken(char * data, char * file, int verbose);
int  getAccessToken(char * data, char * response, int verbose);
int existsFile (char *filename) ;
char* readTextFile(char *file, char *error);
int writeTextFile(char* file, char* data, char *error);
int getInputChars(char* buf, size_t size);


// global
const char URL_TOKEN[] = 
"https://accounts.google.com/o/oauth2/token";

const char REDIRECT_URI[] = 
"urn:ietf:wg:oauth:2.0:oob";


/**
 *  getRefreshTokenToFile
 */
int getRefreshTokenToFile(char * client_id, char * client_secret,  char * refresh_file, int verbose)
{

    const size_t BUFSIZE = 300;
    char auth_url[BUFSIZE];

    char auth_code[200];
    char refresh_request[200];

    buildAuthorizationCodeUrl(client_id, auth_url, BUFSIZE);

    int ret1 = getEnterAuthorizationCode(auth_url, auth_code);
    if(ret1 != 0) {
        return 1;
    }

    if ( strlen(auth_code) == 0 ){
        printf("Please enter Authorization Code \n");
        return 1;
    }

    if(verbose){
        printf("auth_code: %s \n", auth_code);
    }

     buildRefreshTokenRequest(client_id, client_secret, auth_code, refresh_request, BUFSIZE);

    if(verbose){
        printf( "refresh_request: %s \n", refresh_request);
    }

    int  ret2 = getRefreshToken(refresh_request, refresh_file, verbose);
    if(ret2 != 0) {
        return 1;
    }

    return 0;
}



/**
 * buildAuthorizationCodeUrl
 */
void buildAuthorizationCodeUrl(char * client_id, char * buf, size_t bufsize)
{

    const char URL[] = "https://accounts.google.com/o/oauth2/auth";

    const char PARAM[] = "scope=https://mail.google.com/&response_type=code&approval_prompt=force&access_type=offline";

    snprintf(buf, bufsize, "%s?%s&client_id=%s&redirect_uri=%s", URL, PARAM, client_id, REDIRECT_URI);

}


/**
 * getEnterAuthorizationCode
 */
int getEnterAuthorizationCode(char * url, char * auth_code)
{

    printf("Enter the following URL into a browser: \n");
    printf("%s \n", url);
    printf("Enter the browsers response to confirm authorization: ");

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];
    int ret = getInputChars(buf, BUFSIZE);
    if(ret != 0){
        return 1;
    }

   strcpy(auth_code, buf);
    return 0;
}


/**
 * getInputChars
 */
int getInputChars(char* buf, size_t size)
{

    const char LF = '\n' ;
    const char END = '\0' ;

    if (fgets(buf, size, stdin) == NULL) {
        return 1;
    }

    if (strchr(buf, LF) != NULL) {
// if it contains a newline character
// replace with NUL terminal
        buf[strlen(buf) - 1] = END;
    } else {
// clear the input stream
// becuase the part exceeding the maximum number of characters are left in the input stream
        while(getchar() != LF);
        return 1;
    }

    return 0;
}


/**
 * buildRefreshTokenRequest
 */
void  buildRefreshTokenRequest(char * client_id, char * client_secret, char * auth_code, char * buf, size_t bufsize)
{

    const char  TYPE[] = "grant_type=authorization_code";

    snprintf(buf, bufsize, "%s&client_id=%s&client_secret=%s&code=%s&redirect_uri=%s", TYPE, client_id,  client_secret, auth_code, REDIRECT_URI);

}


/**
 * buildAccessTokenRequest
 */
void buildAccessTokenRequest( char * client_id, char * client_secret, char * refresh_token, char * buf, size_t bufsize )
{
    char TYPE[] = "grant_type=refresh_token";

    snprintf(buf, bufsize, "%s&client_id=%s&client_secret=%s&refresh_token=%s", TYPE,  client_id,  client_secret, refresh_token);

}

 
/**
 *  getRefreshToken
 */
int  getRefreshToken(char * data, char * file, int verbose)
{
    return http_post_to_file( (char *)URL_TOKEN, data, file, verbose);
}


/**
 *  getAccessToken
 */
int  getAccessToken(char * data, char * response, int verbose)
{
    struct CurlMemory mem;

    int ret = http_post_to_memory( (char *)URL_TOKEN, data, &mem, verbose);

    int res;
    if(ret == 0){
        strcpy(response , mem.memory);
        res = 0;
    } else {
        res = 1;
    }

    return res;
}


/**
 *existsFile
 * @ return 0 : exists, 1 : stat failed
 */
int existsFile(char *filename) 
{
  struct stat buffer;   
  return stat(filename, &buffer);
}


/**
 * readTextFile
 */
char* readTextFile(char *file, char *error)
{

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "r");
    if(!fp){
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return NULL;
    }

    // Seek the last byte of the file
    fseek(fp, 0, SEEK_END);
     
    // Offset from the first to the last byte, or in other words, filesize
    int string_size = ftell(fp);

    // go back to the start of the file
    rewind(fp);

    // Allocate a string that can hold it all
    char* buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

    // Read it all in one operation
    int read_size = fread(buffer, sizeof(char), string_size, fp);

    // fread doesn't set it so put a \0 in the last position
    // and buffer is now officially a string
    buffer[string_size] = '\0';

    if (string_size != read_size){
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;

        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
    }

    // Always remember to close the file.
    fclose(fp);

    return buffer;
}


/**
 * writeTextFile
 */
int writeTextFile(char* file, char* data, char *error)
{

    FILE *fp;
    int saved_errno;
    int res;

    fp = fopen(file, "w");
    if(!fp) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return 1;
    }

    int ret = fputs( data , fp );
    if( ret == EOF ) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        res = -1;
    } else {
        res = 0;
    }

    fclose(fp);
    return res;
}

