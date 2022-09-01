/**
 *  decomp.c
 * 2022-06-01 K.OHWADA
 */

// Compressing and decompressing files to/from a ZIP archive 
// refece : https://blog.ikappio.com/use-libzip-in-xcode/#example

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>
#include "file_util.h"
#include "zip_util.h"


/**
 *  decomp
 */
bool decomp(char* file_zip)
{
const int NUM = 10;
const int BUFSIZE = 256;
char list[NUM][BUFSIZE];
char name[BUFSIZE ];
char dir[BUFSIZE ];

	int err;
	zip_t *zz = zip_open(file_zip, 0, &err);
	if(!zz){
		printf("err: %d \n", err);
		return false;
	}

FILE *fp;

	int num = zip_get_num_files(zz);
	printf("num: %d \n", num);

for (int i = 0; i < num; i++) 
{
    	struct zip_stat zs;
    	zip_stat_index(zz, i, 0, &zs);
		strcpy(name, zs.name);
		// printf("i: %d , name: %s \n", i, name);
 
// allocate memory equal to file size
	int size = zs.size;
  	char* contents = (char *)calloc(size, sizeof(char) );

// read the contents of a file into memory
  struct zip_file* zf = zip_fopen(zz, name, 0);
  zip_fread(zf, contents, size);
  zip_fclose(zf);

if( is_zip_dir(name) ){
// directory
		if ( make_dir(name, 0777) ) {
			printf("mkdir: %s \n", name);
		}
		continue;
} 

// file
    int listsize;
    get_parent_list(name, &listsize, NUM, BUFSIZE, list);

    for(int i=0; i<listsize; i++){
		strcpy(dir, list[i]);
		if ( make_dir(dir, 0777) ) {
			printf("mkdir: %s \n", dir);
		}
	} // for

	if( is_dir(name) ) {
		continue;
	}

// write
		fp = fopen(name, "w");
		if(fp){
			size_t num = fwrite(contents, sizeof(char), size, fp);
			if(num == size){
				printf("%d : decompress: %s \n", i, name);
			}
		} else {
			printf("cannot open: %s \n", name);
		} // fp
} // for

  zip_close(zz);

	return true;
}


/**
 *  main
 */
int main(int argc, char **argv) 
{
	char* file = (char *)"sample1.zip";

    if(argc == 2){
        file = argv[1];
    } else {
        printf("Usage: %s <zipFile> \n", argv[0]);
    }

      printf("file: %s \n", file);

	if( !decomp(file) ) {
       return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

// mkdir: sample1 
// 0 : decompress: sample1/sample1.txt 
// 1 : decompress: sample1/sample2.txt 
// 2 : decompress: sample1/sample3.txt


