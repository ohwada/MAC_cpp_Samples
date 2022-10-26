/**
 * index_html.h
 * 2022-06-01 K.OHWADA
 */

#include "file_util.h"

// prototype
bool get_index_html( char* text, char* error);


/**
 * get_index_html
 */
bool get_index_html(char* text,  char* error)
{
    char *file = "data/index.html"; 

    return file_text_read2(file, text, error);
}

