#pragma once
/**
 * menu sample
 * 2020-07-01 K.OHWADA
 */

// menu function



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// prototype
int printMenu( char **list,  size_t size, int empty);
bool getEnterYn(char *msg);
bool hitEnterKey(void);
bool checkNumber(int num, int min, int max);
bool getInputChars(char* buf, size_t size);
char** alloc_chars(size_t n, size_t m);

/**
 *   printMenu
 */
int printMenu( char **list, size_t size, int empty )
{

    printf("%d %s \n", 0, "quit" );
    for(int i=0; i<size; i++) {
        printf("%d %s \n", (i+1), list[i] );
    } // for

    printf("[ 0 - %zu ] ",  size );

    size_t BUFSIZE = 100;
    char buf[BUFSIZE];


    bool ret = getInputChars(buf, BUFSIZE);

     int choice = 0;

    if(ret) {
        if(strlen(buf) == 0 ) {
            choice = empty;
        } else{
            choice = atoi(buf);
        }
    }

    return choice;
}


/**
 *  getEnterYn
 */
bool getEnterYn(char *msg)
{

	printf( "%s [Y/n] ", msg);


   size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    bool ret = getInputChars(buf, BUFSIZE);

     bool res = false;

    if(ret ){
        if( strlen(buf) == 0 ) {
                // empty
			    res = true;
        } else {
            char answer = buf[0];
	        if ( (answer == 'Y' ) || ( answer == 'y') ) {
			    res = true;
	        }
        }
    }

	return res;
}


/**
 *  hitEnterKey
 */
bool hitEnterKey(void)
{

	printf("\n");
	printf("Please hit Enter key \n");

   size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    bool ret = getInputChars(buf, BUFSIZE);

     bool res = false;

    if(ret) {
            if(strlen(buf)==0) {
                // empty
			    res = true;
	        }
    }

	return res;
}


/**
 *  checkNumber
 */
bool checkNumber(int num, int min, int max)
{
	if ((num >= min) && (num <=  max)) {
		return true;
	}

	return false;
}


/**
 * getInputChars
 */
bool getInputChars(char* buf, size_t size)
{

    const char LF = '\n' ;
    const char END = '\0' ;

    if (fgets(buf, size, stdin) == NULL) {
        return false;
    }

    if (strchr(buf, LF) != NULL) {
        buf[strlen(buf) - 1] = END;
    } else {
        while(getchar() != LF);
        return false;
    }

    return true;
}

/**
 * alloc_chars
 */
char** alloc_chars(size_t n, size_t m) 
{

	char **chars;

	chars = malloc(sizeof(char *) * n);

	for(int i = 0; i < n; i++) {
		chars[i] = malloc(sizeof(char) * m); 
	    chars[i][0] = '\0';
	}
 
	return chars;
}
