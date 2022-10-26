/**
 * smtp_gmail_xoauth.h
 * 2022-06-01 K.OHWADA
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
 * send_mail
 */
bool send_mail(char* url, char* subject,  char* from,  char* to, char* user, char* access_token, bool is_ssl_verify, bool is_verbose)
{
    CURL *curl;

    struct upload_status upload_ctx = buildUploadStatus( subject,  from,  to );

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);

        curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, access_token);
        curl_easy_setopt(curl, CURLOPT_USERNAME, user);

        return sendMail( curl, url, from, to,  is_ssl_verify, is_verbose );
    }

    return false;
}


/**
 *  main
 */
int main(void)
{
    const size_t BUFSIZE = 1024;
    char access_token[BUFSIZE];
    char error[BUFSIZE];

    const char SUBJECT[] = "libcurl xouath";
  
    struct MailParam  p = getGmailParam();
    printMailParam( p );

    char * URL = p.smtp_url;
    char * USER = p.user;
    char * FROM = p.from;
    char * TO =  p.to;

      bool is_ssl_verify = true;
    bool is_verbose = true;

    bool ret1 = getAccessToken(
    (char *)access_token, (char *)error, is_verbose);

    if(!ret1){
        fprintf(stderr, "error: %s \n", error);
        return EXIT_FAILURE;
    }

    printf("\n access_token \n");
    printf("%s \n", access_token);

     printf("\n send mail \n");

    bool ret2 = send_mail( 
    URL, (char *)SUBJECT,  FROM,  TO, USER, (char *)access_token, is_ssl_verify, is_verbose);

    if(!ret2){
        return EXIT_FAILURE;
    }

    printf("successfiul \n");

    return EXIT_SUCCESS;
}


// Connected to smtp.gmail.com (2404:6800:4008:c00::6c) port 587 (#0)
// > AUTH OAUTHBEARER
// < 334 
// > bixhPWlvdC5.....0PXNtdH
// < 235 2.7.0 Accepted

