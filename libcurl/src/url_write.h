#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */


 // download a given URL into local file or memory 

// reference  https://curl.haxx.se/libcurl/c/url2file.html
// https://curl.haxx.se/libcurl/c/http2-pushinmemory.html

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2019, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING gfile.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * Download a given URL into a local file named page.out.
 * </DESC>
 */

#include <stdbool.h>
#include "write_func.h"



// prototype
bool url_to_memory(char *url, struct CurlMemory *mem, char *error, bool is_verbose);
bool url_to_file(char* url,  char* file, char *error, bool is_verbose);



/**
 * url_to_memory
 */
bool url_to_memory(char *url, struct CurlMemory *mem, char *error, bool is_verbose)
{

    CURL* curl;
    CURLcode res;
    bool ret;

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl = curl_easy_init();

  /* set URL to get here */
  curl_easy_setopt(curl, CURLOPT_URL, url);

  /* Switch on full protocol/debug output while testing */
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* disable progress meter, set to 0L to enable it */
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);


  /* write data to a struct  */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_mem_write_cb);
  initCurlMemory(mem);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);

  /* Switch on full protocol/debug output while testing */
   if (is_verbose){
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

    /* get it! */
    res = curl_easy_perform(curl);
    if(res == CURLE_OK) {
            ret = true;
    } else {
            strcpy(error, curl_easy_strerror(res) );
            ret = false;
    }

  /* cleanup curl stuff */
  curl_easy_cleanup(curl);

  curl_global_cleanup();

  return ret;
}


/**
 * url_to_file
 */
bool url_to_file(char* url,  char* file, char *error, bool is_verbose)
{

    FILE* fp;

  /* open the file */
    fp = fopen(file, "wb");
    if (!fp) {
        strcpy(error, "can not open: ");
        strcat(error, file);
        return false;
    }

    CURL* curl;
    CURLcode res;
    bool ret;

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl = curl_easy_init();

  /* set URL to get here */
  curl_easy_setopt(curl, CURLOPT_URL, url);

  /* Switch on full protocol/debug output while testing */
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* disable progress meter, set to 0L to enable it */
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

  /* send all data to this function  */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_file_write_data);

    /* write the page body to this file handle */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);


  /* Switch on full protocol/debug output while testing */
   if (is_verbose){
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

    /* get it! */
    res = curl_easy_perform(curl);

    if(res == CURLE_OK) {
            ret = true;
    } else {
            strcpy(error, curl_easy_strerror(res) );
            ret = false;
    }

    /* close the header file */
    fclose(fp);

  /* cleanup curl stuff */
  curl_easy_cleanup(curl);

  curl_global_cleanup();

  return ret;
}

