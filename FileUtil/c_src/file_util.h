#pragma once
/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// file utility

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h> 
#include  <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


// prototype
bool file_exists (char* path);
bool is_file(char* path);;
bool is_dir(char* path);
bool file_rename(char* oldpath, char* newpath, char* error);
bool file_text_copy(char *from, char *to, char* error);
bool file_text_write(char* file, char* data, char *error);
char* file_text_read(char *file, char *error);
 uint8_t* file_binary_read(char *file, size_t *size, char *error);
 bool file_binary_write(char *file,  uint8_t *data, size_t size, char *error);
void dump_binary(uint8_t *data, size_t size);



/**
 * file_exists
 */
bool file_exists (char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    bool res = ( ret == 0 )? true: false;
    return res;
}


/**
 * is_file
 */
bool is_file(char* path)
{
    struct stat sb;
    int ret = stat(path, &sb);
    if(ret != 0){
        return false;
    }

    mode_t m = sb.st_mode;
    bool res = ( S_ISREG(m) )? true: false;
    return res;        
}


/**
 * is_dir
 */
bool is_dir(char* path)
{
    struct stat sb;
    int ret = stat(path, &sb);
    if(ret != 0){
        return false;
    }

    mode_t m = sb.st_mode;
    bool res = ( S_ISDIR(m) )? true: false;
    return res;        
}


/**
 * file_rename
 */
bool file_rename(char* oldpath, char* newpath, char* error)
{
    int ret = rename( oldpath, newpath );

    if(ret != 0){
        int errnum = errno;
        strcpy(error, strerror(errnum) );
        return false;
    }

    return true;
}


/**
 * file_text_copy
 */
bool file_text_copy(char *from, char *to, char* error)
{
   const  ssize_t BUFSIZE = 4096;
    char buf[BUFSIZE];
   const  ssize_t ERRSIZE = 100;
    char errbuf[ERRSIZE];

    int fd_to, fd_from;
    ssize_t nread;
    int saved_errno;


    fd_from = open(from, O_RDONLY);
    if (fd_from < 0){
        saved_errno = errno;
        snprintf(errbuf, ERRSIZE, "%s : %s", strerror(saved_errno), from);
        strcpy(error, errbuf);
        return false;
    }

    fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_to < 0){
        saved_errno = errno;
        snprintf(errbuf, ERRSIZE, "%s : %s", strerror(saved_errno), to);
        strcpy(error, errbuf);
        close(fd_from);
        return false;
    }

    while (nread = read(fd_from, buf, BUFSIZE), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;

            do {
                nwritten = write(fd_to, out_ptr, nread);
                if (nwritten >= 0) {
                    nread -= nwritten;
                    out_ptr += nwritten;
                } else if (errno != EINTR) {
                    goto out_error;
                }
            } while (nread > 0);
    
    if (nread == 0)
    {
            if (close(fd_to) < 0) {
                fd_to = -1;
                goto out_error;
            }
            close(fd_from);

            /* Success! */
            return true;
        }
    } // while

  out_error:
    saved_errno = errno;
    strcpy(error, strerror(saved_errno) );
    close(fd_from);
    if (fd_to >= 0){
        close(fd_to);
    }
    return false;
}


/**
 * file_text_write
 */
bool file_text_write(char* file, char* data, char *error)
{

    FILE *fp;
    int saved_errno;
    bool res;

    fp = fopen(file, "w");
    if(!fp) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return false;
    }

    int ret = fputs( data , fp );
    if( ret == EOF ) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        res = false;
    } else {
        res = true;
    }

    fclose(fp);
    return res;
}


/**
 * file_text_read
 */
char* file_text_read(char *file, char *error)
{

    const char CHAR_NULL = '\0';

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "r");
    if(!fp){
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
     
    int file_size = ftell(fp);

    rewind(fp);

// one big size for the null end than file size
    char* buffer = (char*) malloc(sizeof(char) * (file_size + 1) );

    int read_size = fread(buffer, sizeof(char), file_size, fp);

    // fread doesn't set it so put a \0 in the last position
    // and buffer is now officially a string
    buffer[file_size] = CHAR_NULL;

    if (file_size != read_size){

           free(buffer);
           buffer = NULL;

        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
    }

    fclose(fp);

    return buffer;
}


/**
 * file_binary_read
 */
 uint8_t* file_binary_read(char *file, size_t *size, char *error)
{

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "rb");
    if(!fp){

        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );

        *size = 0;
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
     
    size_t file_size = ftell(fp);

    rewind(fp);

    uint8_t* buffer = ( uint8_t *) malloc(sizeof( uint8_t) * file_size );

    int read_size = fread(buffer, sizeof( uint8_t), file_size, fp);

    if (file_size == read_size){
            *size = read_size;
    } else {

            free(buffer);

            saved_errno = errno;
            strcpy( error, strerror(saved_errno) );

            *size = 0;
            buffer = NULL;
    }

    fclose(fp);

    return buffer;
}


/**
 * file_binary_write
 */
 bool file_binary_write(char *file,  uint8_t *data, size_t size, char *error)
{

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "wb");
    if(!fp){
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return false;
    }

    size_t write_size = fwrite(data, sizeof(uint8_t),  size, fp);

     if (size != write_size){
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return false;
    }

    return true;
}


/**
 * dump_binary
 */
void dump_binary(uint8_t *data, size_t size)
{
    for(int i=0; i<size; i++){
        printf("%x, ", data[i] );
    }
    printf( "\n" );
}


