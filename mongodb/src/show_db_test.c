/**
 * show_db_test.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/Ki4mTaria/items/5b2029464db6515f8bfb

#include <bson.h>
#include <mongoc.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * main
 */
int main( void )
{
  mongoc_client_t *     conn    = NULL;
  mongoc_collection_t * coll    = NULL;
  mongoc_cursor_t *     cusr    = NULL;
  const bson_t *        doc     = NULL;
  char *                ret_str = NULL;
  bson_t                query;

// Destination URI
 char* uri = "mongodb://localhost:27017/";

  // connect DB
  conn = mongoc_client_new( uri );
  if( NULL == conn ){
    fprintf(stderr, "mongoc_client_new faild \n");
    return EXIT_FAILURE;
  }
  
char* db_name = "db_test";

// colectionname
char* col_name = "cl_test";

// get data
  coll = mongoc_client_get_collection (
           conn, db_name,  col_name );

  if( NULL == coll ){
        fprintf(stderr, "mongoc_client_get_collection faild \n");
    mongoc_client_destroy ( conn );
                    return EXIT_FAILURE;
  }

  bson_init (&query);
  cusr = mongoc_collection_find_with_opts(
           coll,  // collection
           &query, // query (unspecified)
           NULL, // query options
           NULL  // read_prefs 
         );

  if( NULL == cusr ){
    fprintf(stderr, "mongoc_collection_find_with_opts faild \n");
    mongoc_client_destroy ( conn );
    bson_destroy (&query);
    return EXIT_FAILURE;
  }
  while (mongoc_cursor_next ( cusr , &doc ) ) {
    ret_str = bson_as_json ( doc , NULL );
    printf ( "%s\n", ret_str );
    bson_free ( ret_str );
  }
  // cean up
  mongoc_collection_destroy( coll );
  mongoc_client_destroy ( conn );
  bson_destroy (&query);

      return EXIT_SUCCESS;
}


// { "_id" : { "$oid" : "637d6a1112dd8ea13868b7ae" }, "id" : 1, "name" : "aaa" }
// { "_id" : { "$oid" : "637d6a2712dd8ea13868b7af" }, "id" : 2, "name" : "bbb" }
// { "_id" : { "$oid" : "637d6a3f12dd8ea13868b7b0" }, "id" : 3, "name" : "ccc" }


