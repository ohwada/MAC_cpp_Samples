#pragma once
/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// file utility

#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include  <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


// prototype
int file_exists (char* path);
int is_file(char* path);;
int is_dir(char* path);
int file_rename(char* oldpath, char* newpath, char* error);
int file_copy(char *from, char *to, char* error);
int file_text_write(char* file, char* data, char *error);
char* file_text_read(char *file, char *error);


/**
 * file_exists
 * @return 1 : exists 0 : not found
* https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
 */
int file_exists (char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    int res = ( ret == 0 )?1:0;
    return res;
}


/**
 * is_file
 * @return 1 : is_file -1 : not found
 */
int is_file(char* path)
{
    struct stat sb;
    int ret = stat(path, &sb);
    if(ret != 0){
        return -1;
    }

    mode_t m = sb.st_mode;
    int res = ( S_ISREG(m) )?1:0;
    return res;        
}


/**
 * is_dir
 * @return 1 : is_dir -1 : not found
 */
int is_dir(char* path)
{
    struct stat sb;
    int ret = stat(path, &sb);
    if(ret != 0){
        return -1;
    }

    mode_t m = sb.st_mode;
    int res = ( S_ISDIR(m) )?1:0;
    return res;        
}


/**
 * file_rename
 * @ return 0 : successful, 1 : failed
 * https://linuxjm.osdn.jp/html/LDP_man-pages/man2/rename.2.html
 */
int file_rename(char* oldpath, char* newpath, char* error)
{
    int ret = rename( oldpath, newpath );

    if(ret != 0){
        int errnum = errno;
        strcpy(error, strerror(errnum) );
        return 1;
    }

    return 0;
}


/**
 * file_copy
 * @ return 0 : successful, 1 : failed
 * https://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
 */
int file_copy(char *from, char *to, char* error)
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
        return 1;
    }

    fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_to < 0){
        saved_errno = errno;
        snprintf(errbuf, ERRSIZE, "%s : %s", strerror(saved_errno), to);
        strcpy(error, errbuf);
        close(fd_from);
        return 1;
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
            return 0;
        }
    } // while

  out_error:
    saved_errno = errno;
    strcpy(error, strerror(saved_errno) );
    close(fd_from);
    if (fd_to >= 0){
        close(fd_to);
    }
    return 1;
}


/**
 * file_text_write
 * refrence ; https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rtref/fputs.htm
 */
int file_text_write(char* file, char* data, char *error)
{

    FILE *fp;
    int saved_errno;
    int res;

    fp = fopen(file, "w");
    if(!fp) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return 1;
    }

    int ret = fputs( data , fp );
    if( ret == EOF ) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        res = -1;
    } else {
        res = 0;
    }

    fclose(fp);
    return res;
}


/**
 * file_text_read
 * refrence ; https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
 */
char* file_text_read(char *file, char *error)
{

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "r");
    if(!fp){
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return NULL;
    }

    // Seek the last byte of the file
    fseek(fp, 0, SEEK_END);
     
    // Offset from the first to the last byte, or in other words, filesize
    int string_size = ftell(fp);

    // go back to the start of the file
    rewind(fp);

    // Allocate a string that can hold it all
    char* buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

    // Read it all in one operation
    int read_size = fread(buffer, sizeof(char), string_size, fp);

    // fread doesn't set it so put a \0 in the last position
    // and buffer is now officially a string
    buffer[string_size] = '\0';

    if (string_size != read_size){
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;

        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
    }

    // Always remember to close the file.
    fclose(fp);

    return buffer;
}
