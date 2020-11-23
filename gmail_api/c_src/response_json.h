#pragma once
/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// readMessageResponseJsonFile


#include <stdio.h>
#include <stdlib.h>
 #include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <json.h>


// prototype
bool readListResponseJsonFile( char * filepath, char** ids,  int n, int *num, char * error, bool is_verbose) ;
bool readMessageResponseJsonFile( char * filepath, 
char * id, char* subject, char* from, char* date, char* snippet,
char * error, bool is_verbose);


/**
 * readListResponseJsonFile
 * get first one id
 */
bool readListResponseJsonFile( char * filepath, char** ids,  int n, int *num, char * error, bool is_verbose) 
{

    struct json_object *jobj_from_file = json_object_from_file(filepath);

    if (json_object_is_type(jobj_from_file, json_type_null)) {
        strcpy(error,  "json_object_from_file faild");
        return false;
    }


// messages
    json_object *jobj_messages = json_object_object_get(jobj_from_file,"messages");

   if ( !json_object_is_type(jobj_messages, json_type_array) ) {
        strcpy(error, "not found messages");
        return false;
    }

    int len = json_object_array_length(jobj_messages);
    *num = len;

    if (is_verbose) {
            printf("len: %d \n", len);
    }


    for (int i = 0; i<len; ++i) {

        struct json_object *jobj_message = json_object_array_get_idx(jobj_messages, i);

// id
        json_object *jobj_id = json_object_object_get(jobj_message,"id");

        char *id = (char *)json_object_get_string(jobj_id);

        if (is_verbose) {
            printf(" %d ) id: %s \n",  i, id );
        }

        if (i < n) { 
                strcpy(ids[i],  id ); 
        }

    } // for

    return true;
}


/**
 * readMessageResponseJsonFile
 */
bool readMessageResponseJsonFile( char * filepath, 
char * str_id, char* subject, char* from, char* date, char* snippet,
char * error, bool is_verbose) 
{

    struct json_object *jobj_from_file = json_object_from_file(filepath);

    if (json_object_is_type(jobj_from_file, json_type_null)) {
        strcpy(error,  "json_object_from_file faild");
        return false;
    }

// id
    json_object *jobj_id = json_object_object_get(jobj_from_file,"id");
    strcpy(str_id,  json_object_get_string(jobj_id) ); 

// _snippet 
    json_object *jobj_snippet = json_object_object_get(jobj_from_file,"snippet");
    strcpy(snippet,  json_object_get_string(jobj_snippet) ); 

// payload
    json_object *jobj_payload = json_object_object_get(jobj_from_file,"payload");

   if (json_object_is_type(jobj_payload, json_type_null)) {
        strcpy(error, "not found payload");
        return false;
    }

// header
    json_object *jobj_headers = json_object_object_get(jobj_payload,"headers");

    if ( !json_object_is_type(jobj_headers, json_type_array) ) {
        strcpy(error,  "not found headers");
        return false;
    }


    int len = json_object_array_length(jobj_headers);
    if (is_verbose) {
                printf("header len: %d \n", len);
    }

    char * name_val;
    char * value_val;
    for (int i = 0; i<len; ++i) {

            struct json_object *jobj_header = json_object_array_get_idx(jobj_headers, i);

            json_object *jobj_name = json_object_object_get(jobj_header,"name");
            char *str_name = 
            (char *)json_object_get_string(jobj_name); 

            json_object *jobj_value = json_object_object_get(jobj_header,"value");
            char *str_value = 
            (char *)json_object_get_string(jobj_value); 

            if (is_verbose) {
                printf(" %d ) %s: %s \n",  i,  str_name, str_value );
            }

            if (strcmp(str_name, "Subject") == 0) { 
                    strcpy(subject,  str_value); 
            } else if (strcmp(str_name, "From") == 0) { 
                    strcpy(from,  str_value); 
            } else if (strcmp(str_name, "Date") == 0) { 
                    strcpy(date,  str_value); 
            }
          
    } // for

    return true;
}

