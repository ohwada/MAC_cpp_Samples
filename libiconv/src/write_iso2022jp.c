/**
 * iconv Sample
 * 2021-02-01 K.OHWADA
 */

// read UTF-8 file
// convert codeset UTF-8 to ISO-2022-JP
// write ISO-2022-JP file

// gcc write_iso2022jp.c `pkg-config --cflags --libs iconv` 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iso2022jp.h"


/*
 * main
 */
int main(int argc, char** argv)
{

    char *input = "../samples/sample_utf8.txt";

    if (argc == 2) {
        input = argv[1];
    } else {
        printf( "Usage: %s <textFile> \n", argv[0] );
    }

        printf( "input: %s \n", input );


    char output[] = "utf8_iso2022jp.txt";

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
            puts(line);

            bool ret1 = utf8_to_iso2022jp( line,  strlen(line), (char *)text, CONV_BUFSIZE, (char *)error );


            if ( ret1 ) {
// line feed code is also converted
                    dump_string( text );
                    fputs( text, out );

            } else {

                    printf( "%s \n", error);
             }

            bool ret2 = iso2022jp_to_utf8( text,  strlen(text), (char *)text2,  CONV_BUFSIZE, error );

            if ( ret2 ) {
                    puts(text2);
           } else {
                    printf( "%s \n", error);
            }

            if( strcmp( line, text2 ) != 0 ){
                    printf( "unmatch \n");
            }

        } // while

        fclose(in);

        fflush(out);
        fclose(out);

        printf( "saved: %s \n", output);

    return EXIT_SUCCESS;
}

