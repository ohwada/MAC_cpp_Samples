/**
 * delete.c
 * 2022-06-01 K.OHWADA
 */

// Deleting a Document
// This example illustrates the use of mongoc_collection_delete_one() to delete a document.
// The following code inserts a sample document into the database “mydb” and collection “mycoll”. Then, it deletes all documents matching {"hello" : "world"}.

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
   bson_error_t error;
   bson_oid_t oid;
   bson_t *doc;
  bson_t *reply  = NULL;

   mongoc_init ();

   client =
      mongoc_client_new ("mongodb://localhost:27017/?appname=delete-example");
   collection = mongoc_client_get_collection (client, "test", "test");

   doc = bson_new ();
   bson_oid_init (&oid, NULL);
   BSON_APPEND_OID (doc, "_id", &oid);
   BSON_APPEND_UTF8 (doc, "hello", "world");

   if (!mongoc_collection_insert_one (collection, doc, NULL, reply, &error)) {
      fprintf (stderr, "Insert failed: %s\n", error.message);
   }

   bson_destroy (doc);

   doc = bson_new ();
   BSON_APPEND_OID (doc, "_id", &oid);

   if (!mongoc_collection_delete_one (
          collection, doc, NULL, NULL, &error)) {
      fprintf (stderr, "Delete failed: %s\n", error.message);
   }

   bson_destroy (doc);
   mongoc_collection_destroy (collection);
   mongoc_client_destroy (client);
   mongoc_cleanup ();

   return 0;
}


// Use the MongoDB shell to prove that the documents have been removed successfully.
// % mongosh
// > use mydb
// > db.mycoll.countDocuments({"hello" : "world"})


