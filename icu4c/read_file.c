/**
 * icu4c sample
 * 2020-07-01 K.OHWADA
 */

// read sjis file 
// convrt to UTF-8

// gcc read_file.c  `pkg-config --cflags --libs icu-uc`

// reference : https://www.nslabs.jp/icu-conversion.rhtml


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <unicode/ucnv.h> 


/**
 * readFile
 */
char* readFile(char *file, char *error)
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
 * main
 */
int main(int argc, char* argv[])
{

    const char CHAR_NULL  = '\0'; 
    const char *TARGET_CHARSET = "UTF-8";

    char *file = "data/sjis.txt";
    char *charset = "MS932";  // sjis

    if(argc == 3) {
            file = argv[1];
            charset = argv[2];
    } else {
            printf( "Usage:  %s [file] [charset] \n",  argv[0] );
    }

    char error[100];
    char*source = readFile(file, error);

    if(!source){
        printf("%s : %s \n", error, file );
        return EXIT_FAILURE;
    }

    size_t source_size = strlen(source);

    printf("%s : %zu bytes \n", file, source_size );

     size_t TARGET_SIZE = 10000; // 10 KB
    char target [TARGET_SIZE]; 

  UErrorCode err = U_ZERO_ERROR; 

  // convenience function. 
  int len_conv = ucnv_convert( 
            (char *)TARGET_CHARSET, 
            (char *)charset, 
            (char *)target, 
            TARGET_SIZE, 
            (char *)source, 
            source_size,  
            &err ); 

    if( U_FAILURE( err) ){
        printf("%d : %s \n", err, u_errorName(err) );
        return EXIT_FAILURE;
    }

    target[len_conv] = CHAR_NULL; 
    printf("%s \n", (char*)target);

    return EXIT_SUCCESS;
}


// data/sjis.txt : 221 bytes 

