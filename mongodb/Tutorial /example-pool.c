/**
 * example-pool.c
 * 2022-06-01 K.OHWADA
 */

// Threading
// http://mongoc.org/libmongoc/current/tutorial.html


#include <mongoc/mongoc.h>
#include <pthread.h>
#include <stdio.h>

static pthread_mutex_t mutex;
static bool in_shutdown = false;


/**
 * worker
*/
static void *
worker (void *data)
{
    printf("worker \n");

   mongoc_client_pool_t *pool = data;
   mongoc_client_t *client;
   bson_t ping = BSON_INITIALIZER;
   bson_error_t error;
   bool r;

   BSON_APPEND_INT32 (&ping, "ping", 1);

   while (true) {
      client = mongoc_client_pool_pop (pool);
      /* Do something with client. If you are writing an HTTP server, you
       * probably only want to hold onto the client for the portion of the
       * request performing database queries.
       */
      r = mongoc_client_command_simple (
         client, "admin", &ping, NULL, NULL, &error);

      if (!r) {
         fprintf (stderr, "%s\n", error.message);
      }

      mongoc_client_pool_push (pool, client);

      pthread_mutex_lock (&mutex);
      if (in_shutdown || !r) {
         pthread_mutex_unlock (&mutex);
         break;
      }

      pthread_mutex_unlock (&mutex);
   }

   bson_destroy (&ping);
   return NULL;
}


/**
 * main
*/

int main (int argc, char *argv[])
{
   const char *uri_string = "mongodb://127.0.0.1/?appname=pool-example";
   mongoc_uri_t *uri;
   bson_error_t error;
   mongoc_client_pool_t *pool;
   pthread_t threads[10];
   unsigned i;
   void *ret;

   pthread_mutex_init (&mutex, NULL);
   mongoc_init ();

   if (argc > 1) {
      uri_string = argv[1];
   }

   uri = mongoc_uri_new_with_error (uri_string, &error);
   if (!uri) {
      fprintf (stderr,
               "failed to parse URI: %s\n"
               "error message:       %s\n",
               uri_string,
               error.message);
      return EXIT_FAILURE;
   }

   pool = mongoc_client_pool_new (uri);
   mongoc_client_pool_set_error_api (pool, 2);

   for (i = 0; i < 10; i++) {
        printf("create: %d \n", i);
      pthread_create (&threads[i], NULL, worker, pool);
   }

   sleep (10);
   pthread_mutex_lock (&mutex);
   in_shutdown = true;
   pthread_mutex_unlock (&mutex);

   for (i = 0; i < 10; i++) {
      pthread_join (threads[i], &ret);
    printf("join: %d \n", i);
   }

   mongoc_client_pool_destroy (pool);
   mongoc_uri_destroy (uri);

   mongoc_cleanup ();

   return EXIT_SUCCESS;
}
