#pragma once
/**
 * str_join.h
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>

// prototype
void str_join(char* str1, char* str2, char *glue, char *buf, size_t bufsize);
void str_join_array(char **data, size_t num, char *glue, char *result, size_t result_size);
size_t calc_joinsize(char* str1, char* str2, char *glue);
size_t calc_joinsize_array(char **data, size_t num, char *glue);


/**
 * str_join
 */
void str_join(char* str1, char* str2, char *glue, char *buf, size_t bufsize)
{
    snprintf(buf, bufsize, "%s%s%s", str1, glue, str2);
}


/**
 * str_join_array
 */
void str_join_array(char **data, size_t num, char *glue, char *result, size_t result_size)
{
    const char NUL = '\0';

    char *glue_empty = "";

    memset(result, NUL, result_size);

    for(int i=0; i<num; i++)
    {
        if(i == 0){
            str_join(result, data[i], glue_empty, result, result_size);
        } else {
            str_join(result, data[i], glue, result, result_size);
        }
    } // for 
}


/**
 * calc_joinsize
 */
size_t calc_joinsize(char* str1, char* str2, char *glue)
{
    size_t size = strlen(str1) + strlen(str2) + strlen(glue);

// add number of terminating character
    return (size + 1);
}


/**
 * calc_joinsize_array
 */
size_t calc_joinsize_array(char **data, size_t num, char *glue)
{
    size_t size = 0;

    size_t glue_size = strlen(glue);

    for(int i=0; i<num; i++)
    {
        if(i == 0){
            size += strlen(data[i]);
        } else {
            size += strlen(data[i]) +  glue_size;
        }
    } // for

// add number of terminating character
    return (size + 1);
}

