 /**
 * expat_test3.c
 * 2022-06-01 K.OHWADA
 */

// display element name and the data in the element as a set
// read from stdin
// reference : https://qiita.com/zinbe/items/0516e58cea479e95f6bf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <expat.h>
#include "utstring.h"

#define BUFSIZE 102400


 /**
 * typedef enum
 */
typedef enum {
  DOCUMENT,
  BOOKLIST, 
  BOOK, 
  TITLE, 
  AUTHORS, 
  AUTHOR, 
  PUBLISHER, 
  CATEGORIES, 
  CATEGORY
} element;

element current = DOCUMENT;


 /**
 * elementStart
 */
static void XMLCALL
elementStart(void *user_data, const XML_Char *el, const XML_Char *attr[]) 
{
  switch (current) {
    case DOCUMENT:
      if (strcmp(el,"booklist") == 0)
        current = BOOKLIST;
      break;
    case BOOKLIST:
      if (strcmp(el,"book") == 0)
        current = BOOK;
      break;
    case BOOK:
      if (strcmp(el,"title") == 0)
        current = TITLE;
      else if (strcmp(el,"authors") == 0)
        current = AUTHORS;
      else if (strcmp(el,"publisher") == 0)
        current = PUBLISHER;
      else if (strcmp(el,"categories") == 0)
        current = CATEGORIES;
      break;
    case AUTHORS:
      if (strcmp(el,"author") == 0)
        current = AUTHOR;
      break;
    case CATEGORIES:
      if (strcmp(el,"category") == 0)
        current = CATEGORY;
      break;
    case TITLE:
    case PUBLISHER:
    case AUTHOR:
    case CATEGORY:
      break;
    default:
      current = DOCUMENT;
      break;
  }
}


 /**
 * elementEnd
 */
static void XMLCALL
elementEnd(void *user_data, const XML_Char *el) 
{
  switch (current) {
    case DOCUMENT:
      break;
    case BOOKLIST:
      current = DOCUMENT;
      break;
    case BOOK:
      current = BOOKLIST;
      printf("\n");
      break;
    case AUTHORS:
      current = BOOK;
      break;
    case CATEGORIES:
      current = BOOK;
      break;
    case TITLE:
      current = BOOK;
      break;
    case PUBLISHER:
      current = BOOK;
      break;
    case AUTHOR:
      current = AUTHORS;
      break;
    case CATEGORY:
      current = CATEGORIES;
      break;
    default:
      break;
  }
}


 /**
 * elementData
 */
static void XMLCALL
elementData(void *user_data, const XML_Char *data, int data_size) 
{
  switch (current) {
    case TITLE:
      printf("[TITLE] ");
      break;
    case AUTHOR:
      printf("[AUTHOR] ");
      break;
    case PUBLISHER:
      printf("[PIBLISHER] ");
      break;
    case CATEGORY:
      printf("[CATEGORY] ");
      break;
    default:
      return;
  } 

  UT_string *str = NULL;
  utstring_new(str);
  utstring_bincpy(str, data, data_size);
  printf("%s\n", utstring_body(str));
  utstring_free(str);
}


 /**
 * main
 */
int main(int argc, char *argv[]) {
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


// [TITLE] Easy Java
// [AUTHOR] Taro Yamada
// [PIBLISHER]
