 /**
 * expat_test2.c
 * 2022-06-01 K.OHWADA
 */

// display the data in the element
// reference : https://qiita.com/zinbe/items/0516e58cea479e95f6bf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <expat.h>
#include "utstring.h"

#define BUFSIZE 102400


 /**
 * elementStart
 */
static void XMLCALL
elementStart(void *user_data, const XML_Char *el, const XML_Char *attr[]) 
{
  printf("[ELEMENT] %s Start!\n", el);
}


 /**
 * elementEnd
 */
static void XMLCALL
elementEnd(void *user_data, const XML_Char *el) 
{
  printf("[ELEMENT] %s End!\n", el);
}


 /**
 * elementData
 */
static void XMLCALL
elementData(void *user_data, const XML_Char *data, int data_size) 
{
  if (data_size > 0) {
    UT_string *str = NULL;
    utstring_new(str);
    utstring_bincpy(str, data, data_size);
    printf("[DATA] %s\n", utstring_body(str));
    utstring_free(str);
  }
}


 /**
 * main
 */
int main(int argc, char *argv[]) 
{
  char buf[BUFSIZE];
  int done;
  XML_Parser parser;

  if ((parser = XML_ParserCreate(NULL)) == NULL) {
    fprintf(stderr, "Parser Creation Error.\n");
    exit(1);
  }

  XML_SetElementHandler(parser, elementStart, elementEnd);
  XML_SetCharacterDataHandler(parser, elementData);

  do {
    size_t len = fread(buf, sizeof(char), BUFSIZE, stdin);
    if (ferror(stdin)) {
      fprintf(stderr, "File Error.\n");
      exit(1);
    }

    done = len < sizeof(buf);
    if (XML_Parse(parser, buf, (int)len, done) == XML_STATUS_ERROR) {
      fprintf(stderr, "Parse Error.\n");
      exit(1);      
    }
  } while(!done);

  XML_ParserFree(parser);
  return(0);
}

// [DATA]     
// [ELEMENT] title Start!
// [DATA] Easy Java
// [ELEMENT] title End!
// [DATA] 


