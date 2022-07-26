/**
 * parse_string.c
 * 2026-03-01 K.OHWADA
 */

// refence : https://memonano.hatenablog.com/entry/2012/10/16/022315

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsmn.h"

#define countof(x) (sizeof(x)/sizeof(x[0]))


/**
 * parse
 */
int parse(const char* json) 
{
    jsmn_parser parser;
    jsmntok_t tokens[5] = {0};

    const int BUFSIZE = 256;
    char buf[BUFSIZE];

    jsmn_init(&parser);

    int len = strlen(json);
    jsmn_parse(&parser, json, len, tokens, countof(tokens));

    printf("*********************************\n");
    printf("array : %s\n", json);

    for(int i=1; i<countof(tokens); i++){
        memset(buf, 0, sizeof(buf));
        strncpy(buf, json + tokens[i].start, tokens[i].end - tokens[i].start);
        printf("%d : %s\n", i, buf);
    }

    printf("*********************************\n\n");
    return 0;
}


/**
 * main
 */
int main()
{
    parse("{\"first\" : \"second\" : \"third\" : \"fourth\"}");
    parse("[\"first\" , \"second\" , \"third\" , \"fourth\"]");
    parse("[first second third fourth]");

    return 0;
}


// array : {"first" : "second" : "third" : "fourth"}
// 1 : first
// 2 : second
// 3 : third
// 4 : fourth

