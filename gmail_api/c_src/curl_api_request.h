#pragma once
/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// get message list and first one message with Google API

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "curl_write_func.h"


// prototype
bool http_token_to_file( char* url, char* access_token, char* filepath, char *error, bool is_verbose);
bool http_json_post_token_to_memory(char* url, char* postfileds, char* access_token, struct CurlMemory* mem, char *error, bool is_verbose);


/**
 * http_token_to_file
 */
bool http_token_to_file( char* url, char* access_token, char* filepath, char *error, bool is_verbose)
{

    bool is_save = true;

    FILE* fp;
  /* open the file */
    fp = fopen(filepath, "wb");
    if(!fp) {
        strcpy(error, "can not open: " );
        strcat(error, filepath);
        return false;
    }

   CURL *curl;
   CURLcode res;
    bool ret;


  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;

    /* Remove a header curl would otherwise add by itself */
    chunk = curl_slist_append(chunk, "Accept:");

    /* Add a custom header */
    const size_t BUFSIZE = 300;
    char buf[BUFSIZE];
    snprintf(buf, BUFSIZE, "Authorization: Bearer %s", access_token );
    printf("header: %s \n", buf);
    chunk = curl_slist_append(chunk, buf);

    /* set our custom set of headers */
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER, chunk);

    curl_easy_setopt(curl,CURLOPT_URL, url);

    /* write the page body to this file handle */
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, fp);

  /* send all data to this function  */
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,  curl_file_write_data);

    if( is_verbose ){
        curl_easy_setopt(curl,CURLOPT_VERBOSE, 1L);
    }

    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res == CURLE_OK){
        ret = true;
        // printf("saved to: %s \n", filepath);
    } else {
        ret = false;
        strcpy(error, curl_easy_strerror(res) );
    }

    /* always cleanup */
    curl_easy_cleanup(curl);

    /* free the custom headers */
    curl_slist_free_all(chunk);
  }

    fflush(fp);
    fclose(fp);

  return ret;
}


/**
 * http_json_post_token_to_memory
 */
bool http_json_post_token_to_memory(char* url, char* postfileds, char* access_token, struct CurlMemory* mem, char *error, bool is_verbose)
{

    CURL *curl;
    CURLcode res;
    bool ret;

  /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
    curl = curl_easy_init();

    if(curl) {
    struct curl_slist *headers = NULL;

    /* Remove a header curl would otherwise add by itself */
    headers = curl_slist_append(headers, "Accept:");

    /* Add a custom header */
    const size_t BUFSIZE = 300;
    char buf[BUFSIZE];
    snprintf(buf, BUFSIZE, "Authorization: Bearer %s", access_token );
    printf("header: %s \n", buf);
    headers = curl_slist_append(headers, buf);

    headers = curl_slist_append(headers, "Content-Type: application/json");

    /* set our custom set of headers */
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER, headers);

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
            strcpy(error, curl_easy_strerror(res) );
            ret = false;
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    } // if(curl)

    curl_global_cleanup();

    return ret;
}

