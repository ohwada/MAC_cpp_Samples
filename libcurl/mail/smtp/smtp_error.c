/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// send mail to SMTP server with TLS and AUTH
 
// cd  /Users/ohwada/github/MAC_cpp_Samples/libcurl/mail/smtp
// gcc smtp_error.c `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs json-c` 



 
// gcc smtp/smtp_tls_auth.c `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs json-c` 



/* This is a simple example showing how to send mail using libcurl's SMTP
 * capabilities. It builds on the smtp-mail.c example to add authentication
 * and, more importantly, transport security to protect the authentication
 * details from being snooped.
 *
 * Note that this example requires libcurl 7.20.0 or above.
 */

#include <stdio.h>
#include <stdlib.h>
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

    const char SUBJECT[] = "libcurl test";

// skip SSL verification 
// because ubuntu server is self-certified
    const bool is_ssl_verify = false;

const bool is_verbose = true;

    struct MailParam p = getUbuntuMailParam();
    printMailParam( p );

    char * URL = p.smtp_url;
    char * USER = p.user;
    char * PASSWD = p.passwd;
    char * FROM = p.from;
    char * TO =  p.to;
 
    //URL = "smtp://ubuntu1:25";
// url_easy_perform() failed: Couldn't resolve host name

  // URL = "smtp://ubuntu:250";
// Failed to connect to ubuntu port 250: Connection refused

//USER = "jiro";
//Error: authentication failed: 
// curl_easy_perform() failed: Login denied

    // PASSWD = "0000";
// Error: authentication failed: 
// curl_easy_perform() failed: Login denied

// TO = "jiro";
// <jiro>: Recipient address rejected: User unknown in local recipient table
// curl_easy_perform() failed: Failed sending data to the peer


    CURL *curl;
    bool res;

 struct upload_status upload_ctx = buildUploadStatus((char *)SUBJECT,  FROM,  TO);

  curl = curl_easy_init();

  if(curl) {

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);

    res = sendMailUserPassword(curl, URL, USER, PASSWD, FROM,  TO,  is_ssl_verify,  is_verbose );

  }

    int ret = res ? EXIT_SUCCESS : EXIT_FAILURE;
    return ret;
}


// > 220 VirtualBox ESMTP Postfix (Ubuntu) 
// > AUTH PLAIN
// < 235 2.7.0 Authentication successful


