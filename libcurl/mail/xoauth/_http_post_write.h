#pragma once
/**
  * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// http_post_to_memory

// original : https://curl.haxx.se/libcurl/c/http-post.html
// reference  // https://curl.haxx.se/libcurl/c/http2-pushinCurlMemory.html


#include <stdbool.h>
#include "write_func.h"


// prototype
bool http_post_to_memory(char* url, char* postfileds, struct CurlMemory* mem, bool is_verbose);
bool http_post_to_file(char* url, char* postfileds,  char* file, bool is_verbose);
bool http_post_to_fp(char* url, char* postfileds,  FILE* fp, bool is_verbose);


/**
 * http_post_to_memory
 */
bool http_post_to_memory(char* url, char* postfileds, struct CurlMemory* mem, bool is_verbose)
{

    CURL *curl;
    CURLcode res;
    bool ret;

  /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
        curl_easy_setopt(curl, CURLOPT_URL, url);

    /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfileds);

  /* Switch on full protocol/debug output while testing */
        if (is_verbose){
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }


  /* write data to a struct  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  curl_mem_write_cb);
        initCurlMemory(mem);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);


    /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
    /* Check for errors */  
        if(res == CURLE_OK) {
            ret = true;
        } else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
            ret = false;
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    } // if(curl)

    curl_global_cleanup();

    return ret;
}


/**
 * http_post_to_file
 */
bool http_post_to_file(char* url, char* postfileds,  char* file, bool is_verbose)
{

    FILE* fp;

  /* open the file */
    fp = fopen(file, "wb");
    if(!fp) {
        printf("fopen faild: %s \n", file);
        return false;
    }

    return http_post_to_fp(url, postfileds,  fp, is_verbose);
}


/**
 * http_post_to_fp
 */
bool http_post_to_fp(char* url, char* postfileds,  FILE* fp, bool is_verbose)
{

    CURL *curl;
    CURLcode res;
    bool ret;

  /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
        curl_easy_setopt(curl, CURLOPT_URL, url);

    /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfileds);

  /* Switch on full protocol/debug output while testing */
        if (is_verbose){
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

    /* write the page body to this file handle */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

  /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  curl_file_write_data);

    /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
    /* Check for errors */  
        if(res == CURLE_OK) {
            ret = true;
        } else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
            ret = false;
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    } // if(curl)

    curl_global_cleanup();

    return ret;
}

