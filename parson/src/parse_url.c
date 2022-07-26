#/**
 * parse_url.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/kgabis/parson

#include <stdio.h>
#include <stdlib.h>
#include "parson.h"


const char OUTPUT_FILENAME[] = "commits.json";


/**
 * print_commits_info
 */
void print_commits_info(const char *username, const char *repo) {
    JSON_Value *root_value;
    JSON_Array *commits;
    JSON_Object *commit;
    size_t i;
    
    char curl_command[512];
    char cleanup_command[256];

    
    /* it ain't pretty, but it's not a libcurl tutorial */
    sprintf(curl_command, 
        "curl -s \"https://api.github.com/repos/%s/%s/commits\" > %s",
        username, repo, OUTPUT_FILENAME);
    sprintf(cleanup_command, "rm -f %s", OUTPUT_FILENAME);
    system(curl_command);
    
    /* parsing json and validating output */
    root_value = json_parse_file(OUTPUT_FILENAME);
    if (json_value_get_type(root_value) != JSONArray) {
        system(cleanup_command);
        return;
    }
    
    /* getting array from root value and printing commit info */
    commits = json_value_get_array(root_value);
    int cnt = json_array_get_count(commits);
    printf("count: %d \n", cnt);
    printf("\n");
    const int MAX = 10;
    printf("%-10.10s %-10.10s %s\n", "Date", "SHA", "Author");
    for (i = 0; i < MAX; i++) {
        commit = json_array_get_object(commits, i);
        printf("%.10s %.10s %s\n",
               json_object_dotget_string(commit, "commit.author.date"),
               json_object_get_string(commit, "sha"),
               json_object_dotget_string(commit, "commit.author.name"));
    }
    
    /* cleanup code */
    json_value_free(root_value);
    // system(cleanup_command);
}


/**
 * main
 */
int main(int argc, char **argv) 
{
    char *username = (char *)"ohwada";
    char *repo =  (char *)"MAC_cpp_Samples";
    int cleanup = 1;

    if(argc == 4){
        username = argv[1];
        repo = argv[2];
        cleanup = atoi(argv[3]);
    } else {
        printf("Usage: %s <username> <repo> <cleanup> \n", argv[0]);
    }

    printf("username : %s \n", username );
    printf("repo : %s \n", repo );
    printf("cleanup : %d \n", cleanup );
    printf("\n");

    char cleanup_command[256];
    sprintf(cleanup_command, "rm -f %s", OUTPUT_FILENAME);

    print_commits_info(username, repo);
 
    if( cleanup ) {
        system(cleanup_command);
    }

    return 0;
}
