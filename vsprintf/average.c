/**
* average.c 
* Sample of variable length arguments 
* 2022-06-01 K.OHWADA 
 */

// refference: https://hatekbn.hatenadiary.org/entry/20120328/1332898512


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


double average(double first, ...);


/**
 *  main
 */
int main()
{
double mean;
mean = average(1.0, 2.0, 3.0, 9.0, -1.0);

printf("mean: %5.2f \n", mean);

return 0;
}


/**
 *  average
 * calculate the average of 
 * variable length arguments
 */
double average(double first, ...)
{
const int BUFSIZE = 100;
char buf[ BUFSIZE];
char form[BUFSIZE];

double sum;
double d = first;
int count = 1;

va_list marker, marker_o;

strcpy(form, " ");
printf("data: %5.1f", first);

sum = 0.0;

// Initialization of variable arguments
va_start(marker, first); 

va_copy(marker_o, marker);

while (d >= 0.0) 
{
	sum += d;
	// get the next argument
	d = va_arg(marker, double); 
	if (d >= 0.0) {
		strcat(form, "%5.1f ");
		count ++;
	}
} // while

strcat(form, "\n");
vsprintf(buf, form, marker_o);

// reset Variable argument reset
va_end(marker); 

printf("%s", buf);

return (sum / count);
}

// data:   1.0   2.0   3.0   9.0 
// mean:  3.75
