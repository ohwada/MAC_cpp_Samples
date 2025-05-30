#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */


 // download a given URL into memory 

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


#include "curl_write_file_memory.h"



// prototype
int url_to_memory(char *url, struct Memory* mem);


]/**
 * url_to_memory
 */
int url_to_memory(char *url, struct Memory* mem)
{
    CURL* curl_handle;
    CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* set URL to get here */
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);

  /* Switch on full protocol/debug output while testing */
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

  /* disable progress meter, set to 0L to enable it */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);


  /* write data to a struct  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curl_mem_write_cb);
  initMemory(mem);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, mem);

    /* get it! */
    res = curl_easy_perform(curl_handle);
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", 
              curl_easy_strerror(res));
        return 1;
    }

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  curl_global_cleanup();

  return 0;
}

