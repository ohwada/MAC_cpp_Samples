 /**
 * expat_test1.c
 * 2022-06-01 K.OHWADA
 */


// display list of elements
// read from stdin
// reference : https://qiita.com/zinbe/items/0516e58cea479e95f6bf

// gcc expat_test1.c -Wall -lexpat -o test1
// ./test1 < sample.xml

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <expat.h>

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


// [ELEMENT] booklist Start!
// [ELEMENT] book Start!
// [ELEMENT] title Start!
// [ELEMENT] title End!
