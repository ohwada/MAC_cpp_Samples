/**
 * test_parse_response_post_json.c
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
    char data[BUFSIZE];
    char error[BUFSIZE];

    char* file = (char *)
"sample/sample_response_post_json.json";

    char* expect =
  "{ \"name\": \"michael\" \"age\": 30 }";

    bool ret1 = file_text_read2( file, (char *)text, (char *)error );
    if(!ret1){
        fprintf(stderr, "cannot read %s : %s \n", file, error );
        return EXIT_FAILURE;
    }

    printf("%s \n", text);

    bool ret2 = parse_response_post_json( (char *)text, (char *)data);
    if(!ret2){
        fprintf(stderr, "cannot parse \n");
        return EXIT_FAILURE;
    }

    printf("\n data: %s \n", data);

    assert(strcmp(data, expect) == 0);

    printf("successful \n");

    return 0;
}

