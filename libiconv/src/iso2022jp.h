#pragma once
/**
 * iconv Sample
 * 2021-02-01 K.OHWADA
 */

// ISO2022_JP library
// C version


// reference : https://qiita.com/office-itou/items/6271bcc1a05682133f1a


#include <stdio.h>
#include <stdbool.h>  
#include <string.h> 
#include <errno.h> 
#include <iconv.h>


// constant
const size_t CONV_BUFSIZE = 1024;
const size_t CONV_ERROR_SIZE = 100;
const char ISO2022JP_LF[] = { 0x1B, 0x28, 0x42, 0x0A, 0x00 };


// prototype
bool utf8_to_iso2022jp(const char *src,  size_t src_size, char *dst, size_t dst_size, char *error);
bool iso2022jp_to_utf8(const char *src,  size_t src_size, char *dst, size_t dst_size, char *error);
bool conv_charset(const char *src,  size_t src_size, char *dst, size_t dst_size, const char *tocode, const char *fromcode, char *error);
bool cmp_chars(char *buf1, char *buf2, int buf_size);
void dump_string(char* buf);
void dump_chars(char* buf, int buf_size);

 
/**
 * iso2022jp_to_utf8
 */
bool iso2022jp_to_utf8(const char *src,  size_t src_size, char *dst, size_t dst_size, char *error)
{

    const char TOCODE[] = "UTF-8//IGNORE";
    const char FROMCODE[] = "ISO-2022-JP";

    return conv_charset( src,  src_size, dst, dst_size, 
    (char *)TOCODE, (char *)FROMCODE, error );

}


/**
 * utf8_to_iso2022jp
 */
bool utf8_to_iso2022jp(const char *src,  size_t src_size, char *dst, size_t dst_size, char *error)
{

    const char TOCODE[] = "ISO-2022-JP//IGNORE";
    const char FROMCODE[] = "UTF-8";

    return conv_charset( src,  src_size, dst, dst_size, 
    (char *)TOCODE, (char *)FROMCODE, error );

}


/**
 *  conv_charset
 */
bool conv_charset(const char *src,  size_t src_size, char *dst, size_t dst_size, const char *tocode, const char *fromcode, char *error)
{

    const char CHAR_NULL = '\0';

    char buf[CONV_BUFSIZE];

    if(src_size > CONV_BUFSIZE){
        strcpy( error, "src text size is too large");
        return false;
    }

    char *src_buf = buf;
    char *dst_buf = dst;
    size_t src_len = src_size;
    size_t dst_len = dst_size - 1;
    int save_err;

    strncpy(buf, src, src_size);

    iconv_t conv = iconv_open( (char *)tocode, 
    (char *)fromcode );

    if ( conv  == (iconv_t) - 1) {
        save_err = errno;
        strcpy(error, "iconv_open: " );
        strcat(error, strerror(save_err) );
        return false;
    }

    size_t ret = iconv(conv, &src_buf, &src_len, &dst_buf, &dst_len);
    if ( ret == (size_t) - 1) {
        save_err = errno;
        strcpy(error, "iconv: " );
        strcat(error, strerror(save_err) );
        return false;
    }

    *dst_buf = CHAR_NULL;

    iconv_close(conv);

    return true;
}

/*
 * cmp_chars
 */
bool cmp_chars(char *buf1, char *buf2, int buf_size)
{
    bool is_unmach = false;
    for(int i=0; i < buf_size; i++ ){
        if( buf1[i] != buf2[i] ) {
            is_unmach = true;
        }
    }

    return !is_unmach;
}


/*
 * dump_string
 */
void dump_string(char* buf)
{
    dump_chars( buf, strlen(buf) );
}


/*
 * dump_chars
 */
void dump_chars(char* buf, int buf_size)
{

    for(int i=0; i < buf_size; i++ ){
        printf( "%02X, ", (char)buf[i] );
    }
    printf("\n");

}
