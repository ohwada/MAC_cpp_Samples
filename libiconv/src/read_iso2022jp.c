/**
 * iconv Sample
 * 2021-02-01 K.OHWADA
 */

// read ISO-2022-JP  file
// convert codeset ISO-2022-JP to UTF-8 
// write UTF-8  file

// gcc read_iso2022jp.c `pkg-config --cflags --libs iconv` 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iso2022jp.h"


/*
 * main
 */
int main(int argc, char** argv)
{

    char *input = "../samples/sample_iso2022jp.txt";

    if (argc == 2) {
        input = argv[1];
    } else {
        printf( "Usage: %s <textFile> \n", argv[0] );
    }

        printf( "input: %s \n", input );


    char output[] = "iso2022jp_utf8.txt";

    FILE *in;
    FILE *out;

        // open input file
        in = fopen( input, "r"); 
        if (!in){ 
            printf( "Could not open %s \n", input);
            return EXIT_FAILURE;
        }  

	    out = fopen( output,  "w" );

        if (!out){ 
            printf( "Could not open %s \n", output);
            return EXIT_FAILURE;
        }  

    const size_t LINE_SIZE = 256;

    char line[LINE_SIZE] = {'\0'};

    char text[CONV_BUFSIZE];
    char text2[CONV_BUFSIZE];
    char error[CONV_ERROR_SIZE];

    while ( fgets(line, LINE_SIZE, in) != NULL ) {

// read up to the line feed code (0x0A)
            dump_string( line );


            bool ret1 = iso2022jp_to_utf8( line,  strlen(line), (char *)text, CONV_BUFSIZE, (char *)error );

            if ( ret1 ) {

                    puts( text );
                    fputs( text, out );

            } else {

                    printf( "%s \n", error);
             }

        } // while

        fclose(in);

        fflush(out);
        fclose(out);

        printf( "saved: %s \n", output);

    return EXIT_SUCCESS;
}

