#pragma once
/**
 *  request_parser.h
 * 2022-06-01 K.OHWADA
 */


#include "mongoose.h"


// prototype
void print_mg_str(char* name, struct mg_str str);


/**
 *  print_mg_str
 */
void print_mg_str(char* name, struct mg_str str)
{
   printf("%s: %.*s \n", name, (int)str.len, (char *)str.ptr );
}