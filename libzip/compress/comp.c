/**
 *  comp.c
 * 2022-06-01 K.OHWADA
 */

// Compressing and decompressing files to/from a ZIP archive 
// reference : https://suzulang.com/try-libzip-2-compress/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <zip.h>
#include "file_list.h"



/**
 *   comp_file
 */
bool comp_file( zip_t* zipper,  char* file)
{
    zip_source_t* source;
    source = zip_source_file(zipper, file, 0, 0);
    int ret = zip_file_add(zipper, file, source, ZIP_FL_ENC_UTF_8);

    if(ret >= 0){
        printf("file add: %s \n", file);
    } else {
        printf("file add faild: %s \n", file);
        zip_source_free(source);
        return false;
    }



    return true;
}


/**
 *   r_comp_dir
 * recursive call
 */
bool r_comp_dir( zip_t* zipper,  char* dir)
{
    const int BUFSIZE = 256;
    char path[BUFSIZE];
    char error[BUFSIZE];

    if( !is_dir(dir) ){
            printf("not dir: %s \n", dir);
            return false;
    }

    int ret = zip_dir_add(zipper, dir, ZIP_FL_ENC_UTF_8);
    if(ret >= 0){
            printf("dir add: %s \n", dir);
    }else {
            printf("dir add faild: %s \n", dir);
            return false;
    }

    int num;
    int size;

    char** list= get_file_list(dir, &num, &size, error );
    if(num == 0){
        printf("%s \n", error);
        return false;
    }
    if(size == 0){
        return false;
    }

    for(int i=0; i<size; i++)
    {
        make_path(path, dir, list[i]);
        if(is_dir(path)) {
            r_comp_dir(zipper, path);
        } else if(is_file(path)){
            comp_file(zipper,  path);
        }
    } // for

    free_chars(list, num);

        return true;
}


/**
 *   comp
 */
bool comp(char* input, char* file_zip)
{
    int errorp;
    zip_t* zipper = zip_open(file_zip, ZIP_CREATE | ZIP_EXCL, &errorp);
    if(!zipper){
        printf("cannot open: %s : %d \n", file_zip, errorp);
        return false;
    }

    bool is_error = false;
    if( is_dir(input) ) {
        if( !r_comp_dir(zipper,  input) ){
                is_error = true;
        }
    } else if( is_file(input) ) {
        if( !comp_file(zipper,  input) ) {
                is_error = true;
        }
    } else {
        printf("invalid: %s \n", input);
        is_error = true;
    }

    zip_close(zipper);

    return !is_error;
}


/**
 *  main
 */
int main(int argc, char* argv[])
{
    const int BUFSIZE = 256;
    char file_zip[BUFSIZE];

 	char* input = (char *)"test1";

    if(argc == 3){
        input = argv[1];
        strcpy( file_zip, argv[2]);
    } else if(argc == 2){
        input = argv[1];
    } else {
        printf("Usage: %s <dir> \n", argv[0]);
    }

if(strlen(file_zip) == 0){
    strcpy(file_zip, input);
    strcat(file_zip, ".zip");
}

      printf("%s \n", input);
      printf("%s \n", file_zip);

    if( !comp(input, file_zip) ) {
       return EXIT_FAILURE;
	}

   printf("created: %s \n", file_zip);

    return EXIT_SUCCESS;

  return 0;
}

// dir add: test1 
// file add: test1/sample1.txt 
// file add: test1/sample2.txt 
// file add: test1/sample3.txt 
// created: test1.zip 

