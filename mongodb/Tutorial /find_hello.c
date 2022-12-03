/**
 * find_hello.c
 * 2022-06-01 K.OHWADA
 */

// Finding a Document
// To look for a specific document, add a specifier to query. 
// This example adds a call to BSON_APPEND_UTF8() to look for all documents matching {"hello" : "world"}.

#include <bson/bson.h>
#include <mongoc/mongoc.h>
#include <stdio.h>


/**
 * main
 */

int main (int argc, char *argv[])
{
   mongoc_client_t *client;
   mongoc_collection_t *collection;
   mongoc_cursor_t *cursor;
   const bson_t *doc;
   bson_t *query;
   char *str;

   mongoc_init ();

   client = mongoc_client_new (
      "mongodb://localhost:27017/?appname=find-specific-example");
   collection = mongoc_client_get_collection (client, "mydb", "mycoll");
   query = bson_new ();
   BSON_APPEND_UTF8 (query, "hello", "world");

   cursor = mongoc_collection_find_with_opts (collection, query, NULL, NULL);

   while (mongoc_cursor_next (cursor, &doc)) {
      str = bson_as_canonical_extended_json (doc, NULL);
      printf ("%s\n", str);
      bson_free (str);
   }

   bson_destroy (query);
   mongoc_cursor_destroy (cursor);
   mongoc_collection_destroy (collection);
   mongoc_client_destroy (client);
   mongoc_cleanup ();

   return 0;
}


// { "_id" : { "$oid" : "637cce540d0a6c1c74027631" }, "hello" : "world" }


