/**
 * parse_file.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://mattn.kaoriya.net/software/lang/c/20220320234556.htm


#include <stdio.h>
#include "yyjson.h"


/**
 * main
 */
int main() 
{
const char* FILEPATH = (char *)"foo.json";
  yyjson_read_err err;
  yyjson_doc *doc = yyjson_read_file(FILEPATH,
      YYJSON_READ_NOFLAG,
      NULL,
      &err);

  if (!doc) {
    fprintf(stderr, "%s\n", err.msg);
    return 1;
  }

  yyjson_val *root = yyjson_doc_get_root(doc);

  yyjson_val *title = yyjson_obj_get(root, "title");
  printf("title: %s\n", yyjson_get_str(title));

  yyjson_val *entries = yyjson_obj_get(root, "entries");

  size_t idx, max;
  yyjson_val *entry;
  yyjson_arr_foreach(entries, idx, max, entry) {
    title = yyjson_obj_get(entry, "title");
    printf("%s\n", yyjson_get_str(title));
  }

  yyjson_doc_free(doc); 

  return 0;
}


 
