/*
 * test_upper_lower.c
 * 2022-06-01 K.OHWADA 
*/

#include <stdio.h>
#include "upper_lower.h"


/*
 * main
*/
int main()
{

	const int LF = 10;
	const int ESC = 27;

	printf("Enter one alphabet and return\n");
	printf("ESC to quit \n");

	while(1)
{
	int c = getchar();
	if( (c == EOF)||(c == ESC) ) {
			break;
	}
	if(c == LF){
		printf("%d : LF \n", c);
	} else {
		printf("%d : %c \n", c, c);
	}
	if( isUpper(c) ){
		int low = toLower(c);
		printf("Upper %c to %c \n", c, low);
	} else if( isLower(c) ){
		int up = toUpper(c);
		printf("Lower %c to %c \n", c, up);
	} else if( isDigit(c) ){
	printf("Digit %c \n", c);
	}
} // while

return 0;
}

// Enter one alphabet and return
// ESC to quit
// a
// 97 : a 
// Lower a to A 
// 10 : LF 
