/**
 * test_parse_response_post_form.c
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "json_response_parser.h"
#include "file_util.h"


/**
 * main
 */
int main(int argc, char **argv) 
{
    const size_t TEXT_SIZE = 1024;
    char text[TEXT_SIZE];

    const size_t BUFSIZE = 128;
    char form[BUFSIZE];
    char name[BUFSIZE];
    char age[BUFSIZE];
    char error[BUFSIZE];


   // char* file = (char *)
//"sample/sample_response_post_form.json";

   char* file = (char *)
"sample/body_20221020122149.txt";

    bool ret1 = file_text_read2( file, (char *)text, (char *)error );
    if(!ret1){
        fprintf(stderr, "cannot read %s : %s \n", file, error );
        return EXIT_FAILURE;
    }

    printf("%s \n", text);

    bool ret2 = parse_response_post_form( (char *)text, (char *)form, (char *)name, (char *)age);
    if(!ret2){
        fprintf(stderr, "cannot parse \n");
        return EXIT_FAILURE;
    }

    printf("\n form: %s \n", form);
    printf("name: %s \n", name);
    printf("age: %s \n", age);

    assert(strcmp(name, "michael") == 0);
    assert( strcmp(age, "30") == 0 );

    printf("successful \n");

    return 0;
}

