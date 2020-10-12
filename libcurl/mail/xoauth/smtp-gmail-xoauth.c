/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

//  send mail to Gmail SMTP server with xoauth2

// reference : https://curl.haxx.se/libcurl/c/CURLOPT_XOAUTH2_BEARER.html


// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. login Gmail server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <stdio.h>
#include "auth_json.h"
#include "auth_token.h"
#include "mail_json.h"
#include "smtp.h"


/**
 *  getNewAccessToken
 */
int getNewAccessToken(char* access_token, int verbose)
{

    const char REFRESH_FILE[] = "refresh_token.json";
    const char ACCESS_FILE[] = "access_token.json";

    char client_file[100];
    strcpy( client_file, getMailDir() );
    strcat( client_file, "/client_credentials.json");

    char client_id[100];
    char client_secret[100];
    char refresh_token[100];
    char error[100];

 
// debug 
    int is_access_save = 1;


    int ret1 = readClientJsonFile(client_file, client_id, client_secret, error);
    if(ret1 != 0){
        printf( " readClientJsonFile error: %s \n", error);
        return 1;
    }

    printf("client_id: %s \n", client_id);
    printf("client_secret: %s \n", client_secret);

    int ret2 = existsFile(  (char *)REFRESH_FILE );
    if( ret2 != 0 ){
    // get new, if not exists
        int ret3 = getRefreshTokenToFile(client_id, client_secret,  (char *)REFRESH_FILE, verbose);
        if(ret3){
                printf( "save to: %s \n",  REFRESH_FILE );
        } else {
                printf("getRefreshTokenToFile faild \n");
                return 1;
        }
    }


    int  ret4 = readRefreshTokenJsonFile( (char *)REFRESH_FILE, refresh_token, error);
    if(ret4 != 0){
        printf("readRefreshTokenJson error: %s \n", error);
        return 1;
    }

    printf( "refresh_token: %s \n",  refresh_token );

    const size_t BUFSIZE = 300;
    char access_request[BUFSIZE];
    buildAccessTokenRequest( client_id, client_secret,  refresh_token, access_request, BUFSIZE );

    // printf( "access_request: %s \n",  access_request );

    char access_response[500];
    int  ret5 = getAccessToken(access_request, access_response, verbose);
    if(ret5 != 0){
        printf("getAccessToken error: %s \n", error);
        return 1;
    }

    if(is_access_save){
        int ret6 =  writeTextFile( (char *)ACCESS_FILE, access_response, error );
        if(ret6 == 0){
            printf("saved: %s \n", ACCESS_FILE);
        } else {
            printf( "writeTextFile failed: %s \n", error);
        }
    }

    int ret7 = parseAccessTokenJson( access_response, access_token, error);
    if(ret7 != 0){
        printf("parseAccessTokenJson error: %s \n", error);
        return 1;
    }

    return 0;
}


// global
const int g_verbose = 1;



/**
 * payload_source
 */
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    return payload_source_base(ptr, size, nmemb, userp, g_verbose );
}


/**
 *  main
 */
int main(void)
{

    const char SUBJECT[] = "libcurl xouath";
  
    struct MailParam  p = getGmailParam();
    printMailParam( p );

    char * URL = p.smtp_url;
    char * USER = p.user;
    char * PASSWD = p.passwd;
    char * MAIL_FROM = p.from;
    char * MAIL_TO =  p.to;

    char access_token[200];
   int verbose2 = 0;
    int ret1 = getNewAccessToken( access_token, verbose2);
    if(ret1 != 0){
        return 1;
    }

    printf( "access_token: %s \n", access_token);



    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;

    struct upload_status upload_ctx = buildUploadStatus((char *)SUBJECT,  MAIL_FROM,  MAIL_TO);


    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token);
        curl_easy_setopt(curl, CURLOPT_USERNAME, USER);
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, MAIL_FROM);
        recipients = curl_slist_append(recipients, MAIL_TO);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        if (g_verbose){
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

	return 0;
}


// Connected to smtp.gmail.com (2404:6800:4008:c00::6c) port 587 (#0)
// > AUTH OAUTHBEARER
// < 334 
// > bixhPWlvdC5.....0PXNtdH
// < 235 2.7.0 Accepted

