#pragma once
/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// content type

#include <string.h>


// prototype
void getMediaType(char *ext, char *type);


/**
 * getMediaType
 */
void getMediaType(char *ext, char *type)
{

    if ( strcmp( ext, "txt") == 0 ){
        strcpy( type, "text/plain" );
    } else if ( strcmp(ext, "jpg") == 0 ){
        strcpy( type, "image/jpg" );
    } else if ( strcmp(ext, "png") == 0 ){
        strcpy( type, "image/png" );
    } else {
        strcpy( type, "application/octet-stream" );
    }

}

