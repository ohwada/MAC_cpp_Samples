/**
 * parse_file.c
 * 2020-03-01 K.OHWADA
 */

// psrse JSON from file
// reference : https://github.com/koara-local/json-test/blob/master/json.cpp

#include <stdio.h>
#include <json.h>


/**
 * test_parse_obj_to_string
 */
void test_parse_obj_to_string(struct json_object* const obj) {
    printf("\n test_parse_obj_to_string \n\n");
    json_object_object_foreach(obj, key, val) {
        printf("-- \t%s: %s\n", key, json_object_to_json_string(val));
    }
}


/**
 * test_parse_check_type
 */
void test_parse_check_type(struct json_object* const obj) {
    printf("\n test_parse_check_type \n\n");
    json_object_object_foreach(obj, key, val) {
        if (json_object_is_type(val, json_type_null)) {
            printf("-- \tjson_type_null -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
        }
        if (json_object_is_type(val, json_type_boolean)) {
            printf("-- \tjson_type_boolean -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("-- \t\tvalue: %s\n", json_object_get_boolean(val)? "true": "false");
        }
        if (json_object_is_type(val, json_type_double)) {
            printf("-- \tjson_type_double -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("-- \t\tvalue: %lf\n", json_object_get_double(val));
        }
        if (json_object_is_type(val, json_type_int)) {
            printf("-- \tjson_type_int -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("-- \t\tvalue: %d\n", json_object_get_int(val));
        }
        if (json_object_is_type(val, json_type_object)) {
            printf("-- \tjson_type_object -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("\n >>> START object \n");
            test_parse_check_type(val);
            printf("<<< END object \n\n");
        }
        if (json_object_is_type(val, json_type_array)) {
            printf("-- \tjson_type_array -> \t%s: %s\n",
                    key, json_object_to_json_string(val));

            for (int i = 0; i < json_object_array_length(val); ++i) {
                struct json_object *a = json_object_array_get_idx(val, i);
                printf("-- \t\tvalue: [%d]=%s\n", i, json_object_to_json_string(a));
            }
        }
        if (json_object_is_type(val, json_type_string)) {
            printf("-- \tjson_type_object -> \t%s: %s\n",
                    key, json_object_to_json_string(val));
            printf("-- \t\tvalue: %s\n", json_object_get_string(val));
        }
    }
}


/**
 * main
 */
int main(int argc, char **argv) 
{
    char* file = (char *)"jsons/sample1.json";

    if(argc == 2){
        file = argv[1];
    } else {
        printf("Usage: %s <jsonFile> \n", argv[0]);
    }

      printf("file: %s \n", file);

    printf("json parse from file: %s \n", file);
    struct json_object *jobj_from_file = json_object_from_file(file);
    test_parse_obj_to_string(jobj_from_file);

    //printf("json parse from file & check type \n");
    test_parse_check_type(jobj_from_file);

    return 0;
}
