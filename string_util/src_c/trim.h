/*
 * trim.h
 * 2022-06-01 K.OHWADA 
*/

// reference : https://blog.systemjp.net/entry/2013/05/28/153823

#include <string.h>
#include <ctype.h>


// prototype
void trim (const char* string, char* result); 
void ltrim (const char* string, char* result) ;
void rtrim (const char* string, char* result) ;

const char NUL = '\0';


/*
 * trim
*/
void trim(const char* str, char* result) 
{
    size_t s_len = strlen(str);
    char buf[s_len];
    rtrim(str, buf);
    ltrim(buf, result);
}


/*
 * ltrim
*/
void ltrim(const char* str, char* result) 
{
    size_t s_len = strlen(str);
    char tmp[s_len];
    strcpy(tmp, str); 
    int ptr = 0;
char ch = tmp[ptr];

// find not space
    while( isspace( ch ) && ch != NUL){
        ptr++;
        ch = tmp[ptr];
    }
    strcpy(result, &tmp[ptr]);
}


/*
 * rtrim
*/
void rtrim(const char* str, char* result) 
{
    size_t s_len = strlen(str);
    char tmp[s_len];
    strcpy(tmp, str); 
 
// string size - null byte position
    int s = (strlen(tmp) - 1);
// find not space
    while(s > 0 && isspace(tmp[s]) ){
        s--;
    }
    tmp[s + 1] = NUL;
    strcpy(result, tmp);
}


