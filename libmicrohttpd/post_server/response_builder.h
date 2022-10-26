#pragma once
/**
 * response_builder.h
 * 2022-06-01 K.OHWADA
 */


#include <stdlib.h>
#include <string.h>


// prototype
void build_msg_form(char* msg, char* key, char* value );



/**
 *  build_msg_form
 */
void build_msg_form(char* msg, char* key, char* value )
{
    const char FORMAT[] =
"<html><head><head><body><h1>POST Server</h1><font size='+2'>key= |%s|, value= |%s|<br/></font></body></html>";

    const size_t BUFSIZE = 512;
    char buf[BUFSIZE];

    snprintf( (char *)buf, BUFSIZE, (char *)FORMAT, key, value);

    strcpy(msg, buf);
}