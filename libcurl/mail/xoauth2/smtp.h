#pragma once
/**
 * smtp.h
 * 2020-07-01 K.OHWADA
 */

// common function for SMTP client

// original : https://curl.haxx.se/libcurl/c/smtp-tls.html

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "mail_json.h"
#include "msg_func.h"


/**
 * struct
 */
struct upload_status { int lines_read; char to[256], from[256], subject[256], body[1024]; };


// constant
const char *payload_style[] = {"[DATE]", "[TO]", "[FROM]", "[MAILER]", "[SUBJECT]", "[MESSAGEID]", "\r\n", 
"[BODY1]", "[BODY2]", NULL};

const char BODY1[] = "This is a test e-mail.";
 const char BODY2[] = "This mail was sent using";


// prototype
size_t payload_source_base(void *ptr, size_t size, size_t nmemb, void *userp, bool is_verbose);
 struct upload_status buildUploadStatus(char* subject , char* from,  char* to);
 bool sendMailUserPassword( CURL *curl, char* url, char* user, char* passwd, char* from, char* to,     bool is_ssl_verify, bool is_verbose );
 bool sendMail( CURL *curl, char* url, char* from, char* to, bool is_ssl_verify, bool is_verbose );


/**
 * payload_source_base
 */
size_t payload_source_base(void *ptr, size_t size, size_t nmemb, void *userp, bool is_verbose)
{
    struct upload_status* upload_ctx = (struct upload_status*)userp;
    if ( (size == 0) || (nmemb == 0) || ((size*nmemb) < 1) ) return 0;
    
    const char* data = payload_style[upload_ctx->lines_read];
    if ( data == NULL ) return 0;

    size_t len = 0;

    size_t bufsize = 1024;
    char buffer[bufsize];

    if ( strstr(data,"[DATE]") != NULL ) {
        snprintf(buffer, bufsize, "Date: %s\r\n",getDate());
    } else if ( strstr(data,"[TO]") != NULL ) {
        snprintf(buffer, bufsize, "To: %s\r\n",  upload_ctx->to);
    } else if ( strstr(data,"[FROM]") != NULL ) {
        snprintf(buffer, bufsize, "From: %s\r\n", upload_ctx->to);
    } else if ( strstr(data,"[MAILER]") != NULL ) {
        snprintf(buffer, bufsize, "X-Mailer: %s\r\n",  getMailer() );
    } else if ( strstr(data,"[SUBJECT]") != NULL ) {
        snprintf(buffer, bufsize, "Subject: %s\r\n", upload_ctx->subject);
    } else if ( strstr(data,"[BODY1]") != NULL ) {
        snprintf(buffer, bufsize, "%s \r\n", BODY1);
    } else if ( strstr(data,"[BODY2]") != NULL ) {
        snprintf(buffer, bufsize, "%s %s \r\n", BODY2, getMailer() );

    } else if ( strstr(data,"[MESSAGEID]") != NULL ) {
        snprintf(buffer, bufsize, "Message-ID: <%s>\r\n",getMessageID());
    } else {
        strcpy(buffer, data);
    }

    if(is_verbose) {
        printf("%s \n", buffer);
    }

    len = strlen(buffer);
    memcpy(ptr,buffer,len);
    upload_ctx->lines_read ++;
    return len;
}


/**
 * buildUploadStatus
 */
 struct upload_status buildUploadStatus(char* subject, char* from, char* to)
{
  
    struct upload_status upload_ctx;
    upload_ctx.lines_read = 0;
     strcpy(upload_ctx.subject,  subject);
    strcpy(upload_ctx.from,  from);
    strcpy(upload_ctx.to,  to);
    return upload_ctx;
}


/**
 * sendMailUserPassword(
 */
 bool sendMailUserPassword( CURL *curl, char* url, char* user, char* passwd, char* from, char* to,     bool is_ssl_verify, bool is_verbose )
{

    /* Set the username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, user);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, passwd);

    return sendMail( curl, url, from, to,  is_ssl_verify, is_verbose );
}


/**
 * sendMail
 */
 bool sendMail( CURL *curl, char* url, char* from, char* to, bool is_ssl_verify, bool is_verbose )
{

    bool ret;

  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;

    /* This is the URL for your mailserver. Note the use of port 587 here,
     * instead of the normal SMTP port (25). Port 587 is commonly used for
     * secure mail submission (see RFC4403), but you should use whatever
     * matches your server configuration. */
    curl_easy_setopt(curl, CURLOPT_URL,  url);

    /* In this example, we'll start with a plain text connection, and upgrade
     * to Transport Layer Security (TLS) using the STARTTLS command. Be careful
     * of using CURLUSESSL_TRY here, because if TLS upgrade fails, the transfer
     * will continue anyway - see the security discussion in the libcurl
     * tutorial for more details. */

    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

    /* If your server doesn't have a valid certificate, then you can disable
     * part of the Transport Layer Security protection by setting the
     * CURLOPT_SSL_VERIFYPEER and CURLOPT_SSL_VERIFYHOST options to 0 (false).
     *   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
     *   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
     * That is, in general, a bad idea. It is still better than sending your
     * authentication details in plain text though.  Instead, you should get
     * the issuer certificate (or the host certificate if the certificate is
     * self-signed) and add it to the set of certificates that are known to
     * libcurl using CURLOPT_CAINFO and/or CURLOPT_CAPATH. See docs/SSLCERTS
     * for more information. */
    //curl_easy_setopt(curl, CURLOPT_CAINFO, "/path/to/certificate.pem");

    /* Note that this option isn't strictly required, omitting it will result
     * in libcurl sending the MAIL FROM command with empty sender data. All
     * autoresponses should have an empty reverse-path, and should be directed
     * to the address in the reverse-path which triggered them. Otherwise,
     * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
     * details.
     */
    if (is_ssl_verify ){
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
    } else {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }


    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from);

    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */
    recipients = curl_slist_append(recipients, to);

    //recipients = curl_slist_append(recipients, CC);

    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    /* We're using a callback function to specify the payload (the headers and
     * body of the message). You could just use the CURLOPT_READDATA option to
     * specify a FILE pointer to read from. */
    //curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    //curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    /* Since the traffic will be encrypted, it is very useful to turn on debug
     * information within libcurl to see what is happening during the transfer.
     */
    if (is_verbose){
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res == CURLE_OK){
        ret = true;
    } else {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
        ret = false;
    }

    /* Free the list of recipients */
    curl_slist_free_all(recipients);

    /* Always cleanup */
    curl_easy_cleanup(curl);
  
  return ret;
}

