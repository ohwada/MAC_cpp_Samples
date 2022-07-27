/**
 *  show_zip.c
 * 2020-03-01 K.OHWADA
 */

// refece : https://blog.ikappio.com/use-libzip-in-xcode/#example

// gcc show_zip.cpp -o show `pkg-config --cflags --libs libzip`

#include <stdio.h>
#include <zip.h>


/**
 *  main
 */
int main(int argc, char **argv) 
{
	char* file = (char *)"sample.zip";

    if(argc == 2){
        file = argv[1];
    } else {
        printf("Usage: %s <zipFile> \n", argv[0]);
    }

      printf("file: %s \n", file);

	int err;
	zip_t *zz = zip_open(file, 0, &err);
	if(!zz){
		printf("err: %d \n", err);
		return 1;
	}

	int num = zip_get_num_files(zz);
	printf("num: %d \n", num);

	for (int i = 0; i < num; i++) {
    	struct zip_stat zs;
    	zip_stat_index(zz, i, 0, &zs);
		printf("i: %d , name: %s \n", i, zs.name);
	}

	return 0;
}


// num: 4 
// i: 0 , name: sample/sample1.txt 
// i: 1 , name: sample/sample2.txt 
// i: 2 , name: sample/sample3.txt 
// i: 3 , name: sample/ 


