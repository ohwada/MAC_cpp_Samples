/**
 * response.h
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include "response_parser.h"
#include "save.h"

// prototype
bool proc_response1(char* response);
bool proc_response2(char* response, char* body);



/**
 * bool proc_response1
 */
bool proc_response1(char* response)
{

    printf("\n response \n");
    printf("%s \n", response);
   printf("response size: %zu \n", strlen(response) );

    bool is_save_verbose = true;

    save_response( (char *)response, is_save_verbose);


   size_t header_len = get_header_length( (char*)response);
    if(header_len == 0){
        return false;
    }

    printf("\n header \n");
// teminator NUL is written by get_header_length
    printf("%s \n", response);
    printf("header size: %zu \n",  strlen(response) );

    printf("\n body \n");
    int body_start = header_len+4;
    char* body = &response[body_start];
    printf("%s \n", body );
    printf("body size: %zu \n",  strlen(body) );

    save_body( body, is_save_verbose);

    return false;
}


/**
 * bool proc_response2
 */
bool proc_response2(char* response, char* body)
{

    printf("\n response \n");
    printf("%s \n", response);
   printf("response size: %zu \n", strlen(response) );

    bool is_save_verbose = true;

    save_response( (char *)response, is_save_verbose);


   size_t header_len = get_header_length( (char*)response);
    if(header_len == 0){
        return false;
    }

    printf("\n header \n");
// teminator NUL is written by get_header_length
    printf("%s \n", response);
    printf("header size: %zu \n",  strlen(response) );

    printf("\n body \n");
    int body_start = header_len+4;
    strcpy(body, &response[body_start]);
    printf("%s \n", body );
    printf("body size: %zu \n",  strlen(body) );

    save_body( body, is_save_verbose);

    return false;
}

