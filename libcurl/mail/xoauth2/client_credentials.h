#pragma once
/**
  * client_credentials.h
 * 2022-06-01 K.OHWADA
 */


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "auth_json.h"
#include "mail_directory.h"
#include "file_util.h"

// prototype
bool read_client_credentials(
char* client_id, char* client_secret, char* error);


/**
 *  read_client_credentials
 */
bool read_client_credentials(
char* client_id, char* client_secret, char* error)
{
    const size_t BUFSIZE= 128;
    char path[BUFSIZE];

    char* file= "client_credentials.json";

    make_path(getMailDir(), file, (char *)path );
 
    if( !file_exists( (char *)path ) ){
        strcpy(error, "not found: ");
        strcat(error, (char *)path );
        return false;
    }

  bool ret1 = readClientJsonFile( (char *)path, client_id, client_secret, error);
    if( !ret1 ){
        return false;
    }

    return true;
}
