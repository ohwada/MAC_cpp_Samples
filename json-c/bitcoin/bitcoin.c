/**
 * butcoin.c
 * 2022-06-01 K.OHWADA
 */

// Bitcoin exchange rates  
// parse response
// from https://blockchain.info/ticker
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter12/problem_97/main.cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "json_bitcoin_parser.h"
#include "file_util.h"


/**
 * main
 */
int main(int argc, char *argv[])
{
    const size_t BUFSIZE = 512;
    char error[BUFSIZE];

    char *file = "data/sample_bitcoin.json";

   char* text = file_text_read(file, (char *)error);

    parse_response(text);

    printf("Bitcoin Exchage Rate \n");
    for(int i=0; i<info_num; i++){
        print_latest( exchange_infos[i] );
    } // for

    return 0;
}

