/**
 * insert.c
 * 2022-06-01 K.OHWADA
 */

// Inserting a Document
// http://mongoc.org/libmongoc/current/tutorial.html

#include <bson/bson.h>
#include <mongoc/mongoc.h>
#include <stdio.h>


/**
 * main
 */

int main (int   argc, char *argv[])
{
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    bson_error_t error;
    bson_oid_t oid;
    bson_t *doc;

    mongoc_init ();

    client = mongoc_client_new ("mongodb://localhost:27017/?appname=insert-example");
    collection = mongoc_client_get_collection (client, "mydb", "mycoll");

    doc = bson_new ();
    bson_oid_init (&oid, NULL);
    BSON_APPEND_OID (doc, "_id", &oid);
    BSON_APPEND_UTF8 (doc, "hello", "world");

    if (!mongoc_collection_insert_one (
           collection, doc, NULL, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
    }

    bson_destroy (doc);
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);
    mongoc_cleanup ();

    return 0;
}


// To verify that the insert succeeded
// % mongosh
// test>  use mydb
// mydb> db.mycoll.find()
// [ { _id: ObjectId("637cce540d0a6c1c74027631"), hello: 'world' } ]


