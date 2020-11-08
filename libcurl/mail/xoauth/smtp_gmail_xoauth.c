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
#include <stdlib.h>
#include "auth_json.h"
#include "auth_token.h"
#include "access_token.h"
#include "mail_json.h"
#include "smtp.h"


// global
const bool g_verbose = false;


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
  
    const char REFRESH_FILE[] = "refresh_token_mail.json";

    const bool is_ssl_verify = true;

    const bool is_verbose = true;

    struct MailParam  p = getGmailParam();
    printMailParam( p );

    char * URL = p.smtp_url;
    char * USER = p.user;
    char * PASSWD = p.passwd;
    char * FROM = p.from;
    char * TO =  p.to;

    char access_token[200];
    char error[100];
    bool is_access_save = true;
   bool verbose1 = false;

    bool ret1 = getNewAccessToken( ( char *)SCOPE_MAIL, 
    (char *)REFRESH_FILE,
    access_token,  error,
    is_access_save, verbose1);

    if(ret1){
            printf( "access_token: %s \n", access_token);
    } else {
    printf( "getNewAccessToken: %s \n", error);
            return EXIT_FAILURE;
    }


    CURL *curl;
    bool res;

    struct upload_status upload_ctx = buildUploadStatus((char *)SUBJECT,  FROM,  TO);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);

        curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token);
        curl_easy_setopt(curl, CURLOPT_USERNAME, USER);

        res = sendMail( curl, URL, FROM, TO,  is_ssl_verify, is_verbose );
    }

    int ret = res ? EXIT_SUCCESS : EXIT_FAILURE;
    return ret;
}


// Connected to smtp.gmail.com (2404:6800:4008:c00::6c) port 587 (#0)
// > AUTH OAUTHBEARER
// < 334 
// > bixhPWlvdC5.....0PXNtdH
// < 235 2.7.0 Accepted

