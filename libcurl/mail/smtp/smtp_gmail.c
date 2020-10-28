/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// send mail to Gmail SMTP server 
// gcc src/smtp-gmail.c `pkg-config --cflags --libs json-c` -lcurl -o gmail


#include <stdio.h>
#include <stdlib.h>
#include "smtp.h"

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

    const char SUBJECT[] = "libcurl test";
  
    const long ssl_verify = 1L;

    struct MailParam  p = getGmailParam();
    printMailParam( p );

    char * URL = p.smtp_url;
    char * USER = p.user;
    char * PASSWD = p.passwd;
    char * FROM = p.from;
    char * TO =  p.to;

    CURL *curl;
    bool res;

 struct upload_status upload_ctx = buildUploadStatus((char *)SUBJECT,  FROM,  TO);

  curl = curl_easy_init();

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);

    res = sendMailUserPassword(curl,  URL,USER, PASSWD, FROM, TO, ssl_verify,  g_verbose );

  }

    int ret = res ? EXIT_SUCCESS : EXIT_FAILURE;
    return ret;

}


// < 220 smtp.gmail.com ESMTP q23sm7579351pfl.162 - gsmtp
// > AUTH PLAIN
// < 235 2.7.0 Accepted
