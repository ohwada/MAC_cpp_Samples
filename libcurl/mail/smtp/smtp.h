#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// common function for SMTP client

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "mail_json.h"

/**
 * struct
 */
struct upload_status { int lines_read; char to[256], from[256], subject[256], body[1024]; };


// constant
const char *payload_style[] = {"[DATE]", "[TO]", "[FROM]", "[MAILER]", "[SUBJECT]", "[MESSAGEID]", "\r\n", 
"[BODY1]", "[BODY2]", "[BODY3]", NULL};

const char BODY1[] = "This is a test e-mail.";
 const char BODY2[] = "This mail was sent using libcurl";

// prototype
char* getGMTTime(void);
char* getMessageID(void);
size_t payload_source_base(void *ptr, size_t size, size_t nmemb, void *userp, int verbose);
 struct upload_status buildUploadStatus(char* subject , char* from,  char* to);
CURLcode sendMail( CURL *curl, char* url, char* user, 
char* passwd, char *from, char* to,     long ssl_verify, 
int verbose );
char* getMailer(void);


/**
 * getMailer
 */
char* getMailer(void)
{
    const size_t bufsize = 100;
    static char buff[bufsize];
    snprintf( buff, bufsize, "libcurl %s",  LIBCURL_VERSION );
    return buff;
}


/**
 * payload_source_base
 */
size_t payload_source_base(void *ptr, size_t size, size_t nmemb, void *userp, int verbose)
{
    struct upload_status* upload_ctx = (struct upload_status*)userp;
    if ( (size == 0) || (nmemb == 0) || ((size*nmemb) < 1) ) return 0;
    
    const char* data = payload_style[upload_ctx->lines_read];
    if ( data == NULL ) return 0;

    size_t len = 0;

    size_t bufsize = 1024;
    char buffer[bufsize];

    if ( strstr(data,"[DATE]") != NULL ) {
        snprintf(buffer, bufsize, "Date: %s\r\n",getGMTTime());
    } else if ( strstr(data,"[TO]") != NULL ) {
        snprintf(buffer, bufsize, "To: %s\r\n",  upload_ctx->to);
    } else if ( strstr(data,"[FROM]") != NULL ) {
        snprintf(buffer, bufsize, "From: %s\r\n", upload_ctx->to);
    } else if ( strstr(data,"[MAILER]") != NULL ) {
        snprintf(buffer, bufsize, "X-Mailer: %s\r\n",  getMailer() );
    } else if ( strstr(data,"[SUBJECT]") != NULL ) {
        snprintf(buffer, bufsize, "Subject: %s\r\n", upload_ctx->subject);
    } else if ( strstr(data,"[BODY1]") != NULL ) {
        snprintf(buffer, bufsize, "%s\r\n", BODY1);
    } else if ( strstr(data,"[BODY2]") != NULL ) {
        snprintf(buffer, bufsize, "%s\r\n", BODY2);
} else if ( strstr(data,"[BODY3]") != NULL ) {
        snprintf(buffer, bufsize, "%s\r\n",  curl_version() );
    } else if ( strstr(data,"[MESSAGEID]") != NULL ) {
        snprintf(buffer, bufsize, "Message-ID: <%s>\r\n",getMessageID());
    } else {
        strcpy(buffer, data);
    }

    if(verbose) {
        printf("%s \n", buffer);
    }

    len = strlen(buffer);
    memcpy(ptr,buffer,len);
    upload_ctx->lines_read ++;
    return len;
}


/**
 * getGMTTime
 */
char* getGMTTime(void)
{
    static const char* MONTH[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    static const char* WEEK[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    const size_t bufsize = 256;
    static char gmtBuffer[bufsize];

    struct timeval tv; gettimeofday(&tv,NULL);
    time_t sec = (time_t)(tv.tv_sec + tv.tv_usec * 1e-6);
    struct tm tm; localtime_r(&sec,&tm);
    snprintf(gmtBuffer, bufsize, "%s, %d %s %d %02d:%02d:%02d +0900",
            WEEK[tm.tm_wday],tm.tm_mday,MONTH[tm.tm_mon],tm.tm_year+1900,
            tm.tm_hour,tm.tm_min,tm.tm_sec);

    return gmtBuffer;
}


/**
 * getMessageID
 */
char* getMessageID(void)
{
    const size_t bufsize = 256;
    static char msgID[bufsize];
    struct timeval tv; gettimeofday(&tv,NULL);
    time_t sec = (time_t)(tv.tv_sec + tv.tv_usec * 1e-6);
    struct tm tm; localtime_r(&sec,&tm);

// function 'gethostname' is invalid in C99
    const size_t hostnamesize = 256;
    char hostname[hostnamesize]; 
    gethostname(hostname,  hostnamesize);

    snprintf(msgID, bufsize, "%d%02d%02d%02d%02d%02d.%s",
            tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,
            hostname);

    return msgID;
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
 * sendMail
 */
 CURLcode sendMail( CURL *curl, char* url, char* user, char* passwd, char* from, char* to,     long ssl_verify, int verbose )
{

  //CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  //struct upload_status upload_ctx;

  //upload_ctx.lines_read = 0;

  //curl = curl_easy_init();
  //if(curl) {
    /* Set username and password */
    if(user && *user){
        curl_easy_setopt(curl, CURLOPT_USERNAME, user);
    }
    if(passwd && *passwd){
        curl_easy_setopt(curl, CURLOPT_PASSWORD, passwd);
    }

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
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, ssl_verify);

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
    if (verbose){
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Free the list of recipients */
    curl_slist_free_all(recipients);

    /* Always cleanup */
    curl_easy_cleanup(curl);
  
  return res;
}

