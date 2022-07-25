/**
 * parse_file.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/ksttr/items/25a2db2178e2bbd3ac7b

#include <stdio.h>
#include <string.h>
#include <jansson.h>


/**
 * main
 */
int main()
{

const char* FILEPATH = (char *)"sample.json";

json_t  *obj;
json_error_t jerror;

	obj = json_load_file(FILEPATH, 0, &jerror);
	if(!obj){
		printf( "%s \n", jerror.text); 
		return 1;
	}

	char *name;
	name = (char *)json_string_value( 
	json_object_get(obj, "name") );

	int age = (int)json_integer_value( 
	json_object_get(obj, "age") );

	printf("name: %s \n", name);
	printf("age: %d \n", age);

	return 0;
}

// name: okura 
// age: 10 

