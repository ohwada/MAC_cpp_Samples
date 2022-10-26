#pragma once
/**
  * auth_json.h
 * 2022-06-01 K.OHWADA
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <json.h>


// prototype
bool readClientJsonFile( char * filepath, char * client_id, char * client_secret, char * error);
bool  readRefreshTokenJsonFile( char * filepath, char * refresh_token, char * error);
bool parseAccessTokenJson(char * json, char * access_token, char * error);


/**
 * readClientJsonFile
 */
bool readClientJsonFile( char * filepath, char * client_id, char * client_secret, char * error)
{

    struct json_object *jobj_from_file = json_object_from_file(filepath);

    if (json_object_is_type(jobj_from_file, json_type_null)) {
        strcpy(error,  "json_object_from_file faild");
        return false;
    }


    struct json_object *jobj_installed = json_object_object_get(jobj_from_file,"installed");

    if (json_object_is_type(jobj_installed, json_type_null)) {
        strcpy(error,  "not found installed");
        return false;
    }


    json_object *obj_client_id = json_object_object_get(jobj_installed,"client_id");
    strcpy( client_id, json_object_get_string(obj_client_id) );

    json_object *obj_client_secret = json_object_object_get(jobj_installed,"client_secret");
    strcpy( client_secret, json_object_get_string(obj_client_secret) );

    return true;
}


/**
 * readRefreshTokenJsonFile
 */
bool  readRefreshTokenJsonFile( char * filepath, char * refresh_token, char * error) 
{

    struct json_object *jobj_from_file = json_object_from_file(filepath);

    if (json_object_is_type(jobj_from_file, json_type_null)) {
        strcpy(error, "json_object_from_file faild:");
        return false;
    }


    json_object *obj_refresh_token = json_object_object_get(jobj_from_file,"refresh_token");
    strcpy( refresh_token, json_object_get_string(obj_refresh_token) );

    return true;
  }


/**
 * parseAccessTokenJson
 */
bool parseAccessTokenJson(char * json, char * access_token, char * error)
{

    struct json_object *new_obj;
	new_obj = json_tokener_parse(json);

    json_object *obj_access_token = json_object_object_get(new_obj,"access_token");
    strcpy( access_token, json_object_get_string(obj_access_token) );

    return true;
}


