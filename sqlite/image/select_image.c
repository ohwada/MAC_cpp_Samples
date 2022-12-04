/**
 * select_image.c
 * 2022-06-01 K.OHWADA
 */

// select imaga data from sqlite
// and save into file

// reference : https://qiita.com/staatsschreiber/items/bc43c9b5c9cda2d7a5ea

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "file_util.h"


/**
 * main
 */
int main()
{

    const size_t BUFSIZE = 128;
    char fpath[BUFSIZE];
    char error[BUFSIZE];

    char* db_name = "image.db";

    sqlite3* db_ptr;
    sqlite3_stmt* stmt;
    int ret = 0;

    ret = sqlite3_open(db_name, &db_ptr);
    if (ret != SQLITE_OK) {
       fprintf(stderr, "sqlite3_open: %s \n", sqlite3_errstr(ret) );
        sqlite3_close(db_ptr);
        return EXIT_FAILURE;
    }

    char* query1 = "SELECT id, name FROM image_table";

    ret = sqlite3_prepare_v2(db_ptr,  query1, -1, &stmt, 0);
    if(ret != SQLITE_OK){
        fprintf(stderr, "ERROR(%d) %s\n",ret, sqlite3_errmsg(db_ptr));
        return EXIT_FAILURE;
    }

// read the line.
    ret = sqlite3_step(stmt);
    while(ret == SQLITE_ROW){
        int id = sqlite3_column_int(stmt, 0);
        char* name = (char *)sqlite3_column_text(stmt, 1);
        printf("%d : %s \n", id, name);
        ret = sqlite3_step(stmt);
    } // while

    printf("select id(0: quit) >");

    int select;
    scanf("%d", &select);

    if(select == 0){
        printf("bye \n");
        sqlite3_finalize(stmt);
        sqlite3_close(db_ptr);
        return EXIT_SUCCESS;
 }

    char* query2 = "SELECT name, data FROM image_table WHERE id=?";

    ret = sqlite3_prepare(db_ptr, query2, -1, &stmt, 0);

    if (ret != SQLITE_OK) {
        printf("sqlite3_prepare: %s \n", sqlite3_errmsg(db_ptr) );
        return EXIT_FAILURE;
    }

    sqlite3_bind_int(stmt, 1, select);

    sqlite3_step(stmt);

    char* name = (char *)sqlite3_column_text(stmt, 0);

    int img_size = sqlite3_column_bytes(stmt, 1);
    char * img_data = (char *)sqlite3_column_blob(stmt, 1);
  
    printf("name: %s \n", name);

    printf("img size: %d \n", img_size);

char *dir = "out";

make_path(dir, name, fpath);

printf("fpath: %s \n", fpath);

 bool ret2 = file_binary_write( fpath,  img_data, img_size, (char *)error );
if(!ret2){
    fprintf(stderr, "file_binary_write: %s \n", error);
    return EXIT_FAILURE;
}

    printf("save to %s\n", fpath);

    sqlite3_finalize(stmt);
    sqlite3_close(db_ptr);

    return EXIT_SUCCESS;
}

