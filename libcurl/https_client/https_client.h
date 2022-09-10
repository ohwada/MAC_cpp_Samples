/**
 * https_client.h
 * 2020-07-01 K.OHWADA
 */

// original : https://curl.haxx.se/libcurl/c/https.html

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>
#include "write_func.h"

// prototype
bool https_client(char *url,  bool is_verify);
bool https_client_to_file(char *url,  bool is_verify, char *file);
bool https_client_to_memory(char *url,  bool is_verify,  struct CurlMemory *mem);


/**
 *  https_client
 */
bool https_client(char *url,  bool is_verify)
{
    CURL *curl;
    CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

    bool ret = false;

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL,  url);

        if (is_verify) {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
        } else {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res == CURLE_OK) {
        ret = true;
    } else {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    }

    /* always cleanup */
    curl_easy_cleanup(curl);

  } //   if(curl) 

  curl_global_cleanup();

    return ret;
}


/**
 *  https_client_to_file, 
 */
bool https_client_to_file(char *url,  bool is_verify, char *file)
{

    FILE* fp;

  /* open the file */
    fp = fopen(file, "wb");
    if(!fp) {
        printf("fopen faild: %s \n", file);
        return false;
    }


    CURL *curl;
    CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

    bool ret = false;

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL,  url);

        if (is_verify) {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
        } else {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }

  /* send all data to this function  */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_file_write_data);

    /* write the page body to this file handle */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);


    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res == CURLE_OK) {
        ret = true;
    } else {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    }

    /* always cleanup */
    curl_easy_cleanup(curl);

  } //   if(curl) 

    fclose(fp);
  curl_global_cleanup();

    return ret;
}


/**
 *  https_client_to_memory 
 */
bool https_client_to_memory(char *url,  bool is_verify,  struct CurlMemory *mem)
{

    CURL *curl;
    CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

    bool ret = false;

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL,  url);

        if (is_verify) {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
        } else {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        }

  /* write data to memory  */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_mem_write_cb);
  initCurlMemory(mem);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);


    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res == CURLE_OK) {
        ret = true;
    } else {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  } //   if(curl) 

  curl_global_cleanup();

    return ret;
}





