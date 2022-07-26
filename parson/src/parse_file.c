/**
 * parse_file.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/tomato3713/items/8e88b538844c99aae0b8

#include <stdio.h>
#include "parson.h"

/**
 * main
 */
int main() 
{
const char* FILEPATH = (char *)"sample.json";

JSON_Value* value;
value = json_parse_file(FILEPATH);
if(!value){
    fprintf(stderr, "can not read: %s \n", FILEPATH);
    return 1;
  }

JSON_Object *obj;
obj = json_object(value);
if(!obj){
    fprintf(stderr, "can not parse \n");
    return 1;
  }

char  *name;
name = (char *)json_object_dotget_string ( obj, "name");

int age  = (int)json_object_dotget_number ( obj,  "age");

double height = json_object_dotget_number ( obj,  "height");

printf("name: %s \n", name);

printf("age: %d \n", age);

printf("height: %.1f \n", height);

return 0;
}

// name: taro 
// age: 10 
// height: 140.5
