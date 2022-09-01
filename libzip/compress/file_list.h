#pragma once
/**
 * file_list.h
 * 2021-02-01 K.OHWADA
 */

// get filenames in directory

// reference : https://linuxjm.osdn.jp/html/LDP_man-pages/man3/readdir.3.html

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>  
#include <sys/stat.h>

// prototype
char** get_file_list(char *path, int *num, int *size, char *error );
char** get_file_list_ext(char *path, char *ext, int *num, int *size, char *error );
int get_file_num(char *path, char *error );
bool file_exists (char* path);
bool is_dir(char* path);
bool is_file(char* path);
bool match_ext( char *name, char *ext );
bool get_file_ext(char *fullpath, char *ext);
char** alloc_chars(int n, int m) ;
void clear_chars(char** chars, int n);
void print_chars(char** chars, int n);
void free_chars(char** chars, int n);
void make_path(char *path, char *dir, char *file);


/**
 * get_file_list
 */
char** get_file_list(char *path, int *num, int *size, char *error )
{
    const char DOT[] = ".";
    const char TWO_DOT[] = "..";
    const int LEN = 256;

    if ( !file_exists(path) ) {
        strcpy(error, "not found: ");
        strcat(error, path);
        *num = 0;
        *size = 0;
        return NULL;
    }


    if ( !is_dir(path) ) {
        strcpy(error, "not directory: ");
        strcat(error, path);
        *num = 0;
        *size = 0;
        return NULL;
    }


    int file_num = get_file_num(path, error );
    if (file_num == 0) {
        *num = 0;
        *size = 0;
        return NULL;
    }

    char** list = alloc_chars(file_num, LEN) ;


// get files
    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );
        *num = 0;   
        *size = 0;            
        return NULL;
    }

    struct dirent * ent;
    char *name;
    int cnt = 0;

    while ((ent = readdir (dir)) != NULL) 
{
        name = ent->d_name;

        if( strcmp(name, DOT) == 0 ) {
            continue;
        }
        if( strcmp(name, TWO_DOT) == 0 ) {
            continue;
        }
  
        if(cnt< file_num){
            strcpy( list[cnt], ent->d_name );
            cnt++;
        } 

    } // while

    closedir (dir);

    *num = file_num;
    *size = cnt;

    return list;
}


/**
 * get_file_list_ext
 */
char** get_file_list_ext(char *path, char *ext, int *num, int *size, char *error )
{
    const char DOT[] = ".";
    const char TWO_DOT[] = "..";
 const int LEN = 256;

    if ( !file_exists(path) ) {
        strcpy(error, "not found: ");
        strcat(error, path);
        *num = 0;
        *size = 0;
        return NULL;
    }

    if ( !is_dir(path) ) {
        strcpy(error, "not directory: ");
        strcat(error, path);
        *num = 0;
        *size = 0;
        return NULL;
    }

    int file_num = get_file_num(path, error );
    if (file_num == 0) {
        *num = 0;
        *size = 0;
        return NULL;
    }

    char** list = alloc_chars(file_num, LEN) ;

// get files
    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );               
        *num = 0;
        *size = 0;
        return NULL;
    }

    struct dirent * ent;
    char *name;
    int cnt = 0;

    while ((ent = readdir (dir)) != NULL) 
{
        name = ent->d_name;

        if( strcmp(name, DOT) == 0 ) {
            continue;
        }
        if( strcmp(name, TWO_DOT) == 0 ) {
            continue;
        }
        if( !match_ext( name, ext ) ) {
            continue;
        }

        if(cnt < file_num){
            strcpy( list[cnt], ent->d_name );
            cnt ++;
        } 

    } // while

    closedir (dir);

    *num = file_num;
    *size = cnt;

    return list;
}


/**
 * get_file_num
 */
int get_file_num(char *path, char *error )
{
    if ( !is_dir(path) ) {
        strcpy(error, "not directory: ");
        strcat(error, path);
        return 0;
    }

// count files
    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );               
        return 0;
    }

    struct dirent * ent;
    int cnt = 0;

    while ((ent = readdir (dir)) != NULL) 
{
        cnt++;
} // while

    closedir (dir);

    return cnt;
}


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
 * match_ext
 */
bool match_ext( char *name, char *ext1 )
{
    const int BUFSIZE = 256;
    char ext2[BUFSIZE];

    get_file_ext( name, ext2 );

    if( strcmp(ext1, ext2 ) == 0 ) {
        return true;
    }

    return false;
}


/**
 * get_file_ext
 */
bool get_file_ext(char *fullpath, char *ext) 
{

    const char DOT = '.';
    const char NUL = '\0';

    int len = strlen(fullpath);
    char buf[len+1];
    strcpy(buf, fullpath);

    char *p = strrchr(buf, DOT);
    if(!p) {
        // not found dot
        ext[0] = NUL;
        return false;
    }


    // omit the first DOT
    strcpy(ext, &p[1]);

    return true;
}


/**
 * alloc_chars
 */
char** alloc_chars(int n, int m) 
{

	char **chars;

// allocate an area to hold addresses for n lines
	chars = malloc(sizeof(char *) * n);

 
	for(int i = 0; i < n; i++) {
// allocate an area to hold one line of data
		chars[i] = malloc(sizeof(char) * m); 
	    chars[i][0] = '\0';
	}
 
	return chars;
}


/**
 * clear_chars
 */
void clear_chars(char** chars, int n)
{

	for(int i = 0; i < n; i++) {
        chars[i][0] =  '\0';
	} // for i

}


/**
 * print_chars
 */
void print_chars(char** chars, int n)
{

	for(int i = 0; i < n; i++) {
	    printf("%d : %s \n", ( i + 1), chars[i]);
	} // for i

}


/**
 * free_chars
 */
void free_chars(char** chars, int n)
{

	for(int i = 0; i < n; i++) {
// release Memory 
		free( chars[i] );
	}
	free(chars);
}

void make_path(char *path, char *dir, char *file)
{
    const char SLASH = '/';
    const char NUL = '\0';


    strcpy(path, dir);

    int len = strlen(path);
    char last = path[len-1];
    if(last != SLASH) {
        path[len] = SLASH;
        path[len+1] = NUL;
    }

    strcat(path, file);
}
