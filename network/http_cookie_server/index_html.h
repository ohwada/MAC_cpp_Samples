#pragma once
/**
 * index_html.h
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_util.h"


// prototype
bool get_index_html(char *html);


/**
 * get_index_html
 */
bool get_index_html(char *html)
{
    const size_t BUFSIZE = 128;
    char error[BUFSIZE];

    char *file = "data/index.html";

    bool ret = file_text_read1(file, html, (char *)error);
    if(!ret){
        fprintf(stderr, "cannot read: %s : %s \n", file, error);
        return false;
    }

    return true;
}

