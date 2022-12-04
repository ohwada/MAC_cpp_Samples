/**
 * insert_image.c
 * 2022-06-01 K.OHWADA
 */

// insert image data into sqlite by loading from file

// reference : https://www.includehelp.com/c-programs/insert-an-image-data-into-sqlite-table.aspx

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
    char error[BUFSIZE];

    char* fname = "sqlite_logo.png";

    char* fpath = "images/sqlite_logo.png";

    char* db_name = "image.db";

    size_t img_size;

    char* img_data = file_binary_read(fpath, &img_size, (char *)error);

if( !img_data ||(img_size == 0) ) {
    fprintf(stderr, "file_binary_read: %s \n", error);
    return EXIT_FAILURE;
}

    sqlite3* db_ptr;
    sqlite3_stmt* stmt;
    int ret = 0;


    ret = sqlite3_open(db_name, &db_ptr);

    if (ret != SQLITE_OK) {
        fprintf(stderr, "sqlite3_open: %s \n", sqlite3_errstr(ret) );
        sqlite3_close(db_ptr);
        return EXIT_FAILURE;
    }

    char* query = "INSERT INTO image_table(name, data) VALUES(?, ?)";

    ret = sqlite3_prepare(db_ptr, query, -1, &stmt, 0);

    if (ret != SQLITE_OK) {
        fprintf(stderr, "sqlite3_prepare: %s\n", sqlite3_errmsg(db_ptr) );
        return EXIT_FAILURE;
    }

    sqlite3_bind_text(stmt, 1, fname, strlen(fname), NULL);

    sqlite3_bind_blob(stmt, 2, img_data, img_size, SQLITE_STATIC);

    ret = sqlite3_step(stmt);

    if (ret != SQLITE_DONE) {
        fprintf(stderr, "sqlite3_step: %s \n", sqlite3_errmsg(db_ptr));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db_ptr);
    free(img_data);

    printf("Image inserted successfully\n");

    return EXIT_SUCCESS;
}

