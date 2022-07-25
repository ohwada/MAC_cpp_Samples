/**
 * sample.cpp
 * 2022-06-01 K.OHWADA
 */

// gcc sample.c -o sample -I/usr/local/include/cjson -lcjson

// refence : https://mattn.kaoriya.net/software/lang/c/20170510162815.htm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"


/**
 * main
 */
int main(int argc, char* argv[]) 
{
  cJSON *root = cJSON_CreateObject(), *arr, *item; 

  cJSON_AddNumberToObject(root, "count", 1);
  cJSON_AddItemToObject(root, "items", arr = cJSON_CreateArray());
  cJSON_AddItemToArray(arr, cJSON_CreateString("Hello World"));
  cJSON_AddItemToArray(arr, cJSON_CreateFalse());
  cJSON_AddItemToArray(arr, cJSON_CreateNull());
  puts(cJSON_PrintUnformatted(root));
  cJSON_free(root);
  
  root = cJSON_Parse("{\"count\":1, \"items\":[\"Hello World\",false,null]}");
  arr = cJSON_GetObjectItem(root, "items");
  cJSON_ReplaceItemInArray(arr, 0, cJSON_CreateString("Hello Japan"));
  cJSON_ArrayForEach(item, arr) {
    puts(cJSON_Print(item));
  }
  cJSON_free(root);

  return 0;
}

// {"count":1,"items":["Hello World",false,null]}
// "Hello Japan"
