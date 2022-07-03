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
bool get_file_list(char *path, char** list, int n, int *size, char *error );
bool get_file_list_ext(char *path, char** list, int n, char *ext, int *size, char *error );
bool file_exists (char* path);
bool is_dir(char* path);
bool match_ext( char *name, char *ext );
char* get_file_ext(char *fullpath);
char** alloc_chars(int n, int m) ;
void clear_chars(char** chars, int n);
void print_chars(char** chars, int n);
void free_chars(char** chars, int n);


/**
 * get_file_list
 */
bool get_file_list(char *path, char** list, int n, int *size, char *error )
{
    const char DOT[] = ".";
    const char TWO_DOT[] = "..";


    if ( !file_exists(path) ) {
        strcpy(error, "not found: ");
        strcat(error, path);
        return false;
    }


    if ( !is_dir(path) ) {
        strcpy(error, "not directory: ");
        strcat(error, path);
        return false;
    }


    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );               
        return false;
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
  
        if(cnt < n){
            strcpy( list[cnt], ent->d_name );
        } else {
            break;
        }

        cnt++;
    } // while

    closedir (dir);

    *size = cnt;

    return true;
}


/**
 * get_file_list
 */
bool get_file_list_ext(char *path, char** list, int n, char *ext, int *size, char *error )
{
    const char DOT[] = ".";
    const char TWO_DOT[] = "..";

    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        int save_err = errno;
        strcpy(error, strerror(save_err) );               
        return false;
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

        if(cnt < n){
            strcpy( list[cnt], ent->d_name );
        } else {
            break;
        }

        cnt++;
    } // while

    closedir (dir);

    *size = cnt;

    return true;
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
 * match_ext
 */
bool match_ext( char *name, char *ext )
{

    char *name_ext = get_file_ext( name );

    if( strcmp( name_ext, ext ) == 0 ) {
        return true;
    }

    return false;
}


/**
 * get_file_ext
 */
char* get_file_ext(char *fullpath) 
{

    const char DOT = '.';

    int len = strlen(fullpath);
    char buf[len+1];
    strcpy(buf, fullpath);

    char *ext = strrchr(buf, DOT);
    if(!ext) {
        printf("not find dot \n");
        return "";
    }


    // omit the first DOT
    char *ext1 = &ext[1];

    return ext1;

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


