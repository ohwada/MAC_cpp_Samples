/**
 * uuid.c
 * 2022-06-01 K.OHWADA
 */

 // gcc uuid.c  -luuid
// reference : https://ez-net.jp/article/45/0j8Uh_lI/w7b70NXnXUQL/
// https://kaworu.jpn.org/c/C%E8%A8%80%E8%AA%9E%E3%81%A7UUID%E3%82%92%E7%94%9F%E6%88%90%E3%81%99%E3%82%8B%E6%96%B9%E6%B3%95

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
	// uuid_string_t result;
	// uuid_unparse_upper(value, result);

const int UUID_LEN = 37; 
	char result[UUID_LEN];
	uuid_unparse(value, result);

printf("%s \n", result);

	return 0;
}


