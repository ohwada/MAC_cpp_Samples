#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// readClientJsonFile


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <json.h>


// prototype
int readClientJsonFile( char * filepath, char * client_id, char * client_secret, char * error);
int  readRefreshTokenJsonFile( char * filepath, char * refresh_token, char * error);
int parseAccessTokenJson(char * json, char * access_token, char * error);



/**
 * readClientJsonFile
 */
int readClientJsonFile( char * filepath, char * client_id, char * client_secret, char * error) 
{

    char* installed = (char *)malloc(500);

    struct json_object *jobj_from_file = json_object_from_file(filepath);

    if (json_object_is_type(jobj_from_file, json_type_null)) {
        strcpy(error,  "json_object_from_file faild");
        return 1;
    }

    json_object_object_foreach(jobj_from_file, key, val) {
            if (strcmp(key, "installed") == 0) { 
                strcpy(installed, json_object_get_string(val) );
            }
    }

    if( strlen(installed) == 0 ){
        strcpy(error, "not found installed");
        return 1;
    }

    struct json_object *new_obj;
	new_obj = json_tokener_parse(installed);

    json_object *obj_client_id = json_object_object_get(new_obj,"client_id");
    strcpy( client_id, json_object_get_string(obj_client_id) );

    json_object *obj_client_secret = json_object_object_get(new_obj,"client_secret");
    strcpy( client_secret, json_object_get_string(obj_client_secret) );

    return 0;
}


/**
 * readRefreshTokenJsonFile
 */
int  readRefreshTokenJsonFile( char * filepath, char * refresh_token, char * error) 
{

    struct json_object *jobj_from_file = json_object_from_file(filepath);

    if (json_object_is_type(jobj_from_file, json_type_null)) {
        strcpy(error, "json_object_from_file faild:");
        return 1;
    }

    json_object_object_foreach(jobj_from_file, key, val) {
  
            //printf("key: %s \n", key);
            if (strcmp(key, "refresh_token") == 0) { 
                strcpy( refresh_token, json_object_get_string(val) );
            }
    }

    return 0;
  }


/**
 * parseAccessTokenJson
 */
int parseAccessTokenJson(char * json, char * access_token, char * error)
{

    struct json_object *new_obj;
	new_obj = json_tokener_parse(json);

    json_object *obj_access_token = json_object_object_get(new_obj,"access_token");
    strcpy( access_token, json_object_get_string(obj_access_token) );

    return 0;
}


