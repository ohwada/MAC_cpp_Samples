#pragma once
/**
 * slink.h
 * 2022-06-01 K.OHWADA
 */

// reference : https://www.jpcert.or.jp/sc-rules/c-pos30-c.html

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include  <errno.h> 
#include <string.h>
#include <sys/stat.h>

size_t get_file_size(char* filepath);
bool get_linkpath(char *buf, size_t bufsize, char *sym_path, char *error);
bool is_slink(char* path, size_t *size);
bool show_link(char *path);


/**
 * get_file_size
 */
size_t get_file_size(char* filepath)
{
    struct stat sb;

    int ret = stat(filepath, &sb);
    if (ret != 0) {
        return false;
    }

    return sb.st_size;
}


/**
 * get_linkpath
 */
bool get_linkpath(char *buf, size_t bufsize, char *sym_path, char *error)
{
    const char NUL = '\0';

    ssize_t len = readlink(sym_path, buf, bufsize-1);

    if (len == -1) {
	    strcpy(error, strerror(errno));
	    return false;
    }

	buf[len] = NUL;
    return true;
}


/**
 * is_slink
 */
bool is_slink(char* path, size_t *size)
{
struct stat sb;

    int ret = lstat(path, &sb);
    if(ret != 0){
        return false;
    }

    *size = sb.st_size;
    mode_t m = sb.st_mode;
    bool res = ( S_ISLNK(m) )? true: false;
    return res;        
}


/**
 * show_link
 */
bool show_link(char *path)
{
const size_t BUFSIZE = 1024;
char buf[BUFSIZE];

const size_t ERRSIZE = 100;
char error[ERRSIZE];

size_t sym_size;

bool ret1 = is_slink(path, &sym_size);

if( !ret1 ) {
	printf("not symlink: %s \n", path);
	return false;
}

bool ret2 = get_linkpath(buf, BUFSIZE, path, error);
if( !ret2 ) {
	printf("%s \n", error);
	return false;
}

    size_t link_size = get_file_size(path);

	printf("%s (%zu) \n", path, sym_size);
	printf("-> %s (%zu) \n", buf, link_size);

    return true;
}

