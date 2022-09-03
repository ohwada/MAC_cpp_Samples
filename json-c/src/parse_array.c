/**
 * parse_array.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://nuko-yokohama.hatenadiary.org/entry/20130305/1362479773


#include <stdio.h>
#include <json.h>


/**
 * print_array
 */
void print_array(json_object* array_obj)
{
    int array_num = json_object_array_length(array_obj);
    json_object* obj;
    for (int i = 0; i < array_num; i++) {
            obj = json_object_array_get_idx(array_obj, i);
            if (json_object_get_type(obj) == json_type_string) {
                printf("%d: %s\n", i, json_object_get_string(obj));
            }
    } // for
}


/**
 * print_columns
 */
void print_columns(json_object* root_obj)
{
    json_object *columns_obj;

    columns_obj = json_object_object_get(root_obj, "columns");
    // printf("columns_obj=%s\n", json_object_to_json_string(columns_obj));
    if (json_object_get_type(columns_obj) == json_type_array) {
        print_array(columns_obj);
    } // if
}


/**
 * print_data
 */
void print_data(json_object* root_obj)
{
    json_object *data_obj;

    data_obj = json_object_object_get(root_obj, "data");
    // printf("data_obj=%s\n", json_object_to_json_string(data_obj));
    if (json_object_get_type(data_obj) == json_type_array) {
        int i;
        int array_num = json_object_array_length(data_obj);
        // array_list* list = json_object_get_array(columns_obj);
        json_object* obj;
        for (i = 0; i < array_num; i++) {
            obj = json_object_array_get_idx(data_obj, i);
            if (json_object_get_type(obj) == json_type_array) {
                print_array(obj);
            }
        } // for
    } // if
}


/**
 * main
 */
int main()
{
const char* PATH = "jsons/columns.json";

    json_object *root_obj;

     root_obj = json_object_from_file(PATH);

    if (root_obj == NULL) {
        fprintf(stderr, "json parse error.\n");
        return 1;
    }

    print_columns(root_obj);

    print_data(root_obj);

    return 0;
}

// 0: name
// 1: area
// 0: Taro
/// 1: Yokohama

