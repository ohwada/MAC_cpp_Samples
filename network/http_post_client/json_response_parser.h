/**
 * json_response_parser.c
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>
#include <json.h>
#include "file_util.h"

// prototype
bool parse_response_post_form(char *text, char* form, char *name, char* age);
bool parse_response_post_json(char *text, char* data);


/**
 *  parse_response
 */
bool parse_response_post_form(char *text, char* form, char *name, char* age)
{

    json_object *jobj_root = json_tokener_parse(text);

    json_object *jobj_form = json_object_object_get(jobj_root, "form");

    if (json_object_is_type(jobj_form, json_type_null)) {
        fprintf(stderr, "not find: form \n");
        return false;
    }

    strcpy(form, json_object_get_string(jobj_form) );

    json_object *jobj_json = json_object_object_get(jobj_root, "json");

    if (! json_object_is_type(jobj_json, json_type_object)) {
        fprintf(stderr, "not find: json \n");
        return false;
    }

    json_object *jobj_name = json_object_object_get(jobj_json, "name");

    if (json_object_is_type(jobj_name, json_type_string)) {
        strcpy(name, json_object_get_string(jobj_name) );
    } else {
        fprintf(stderr, "not find: name \n");
        return false;
   }

    json_object *jobj_age = json_object_object_get(jobj_json, "age");

    if (json_object_is_type(jobj_age, json_type_string)) {
        strcpy(age, json_object_get_string(jobj_age) );
    } else {
        fprintf(stderr, "not find: age \n");
        return false;
   }

    return true;
}


/**
 *  parse_response
 */
bool parse_response_post_json(char *text, char* data)
{

    json_object *jobj_root = json_tokener_parse(text);

    json_object *jobj_data = json_object_object_get(jobj_root, "data");

    if (json_object_is_type(jobj_data, json_type_null)) {
        fprintf(stderr, "not find: data \n");
        return false;
    }

    strcpy(data, json_object_get_string(jobj_data) );

    return true;
}
