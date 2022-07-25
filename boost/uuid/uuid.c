/**
 * uuid.c
 * 2022-06-01 K.OHWADA
 */

 // gcc uuid.c -o uuid
// reference : https://ez-net.jp/article/45/0j8Uh_lI/w7b70NXnXUQL/

#include <uuid/uuid.h>
#include <stdio.h>


/**
 * main
 */
int main()
{

// generate uuid
	uuid_t value;
	uuid_generate(value);

 // convert to string
	uuid_string_t result;
	uuid_unparse_upper(value, result);

printf("%s \n", result);

	return 0;
}


