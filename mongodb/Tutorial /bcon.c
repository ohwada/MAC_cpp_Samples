/**
 * bcon.c
 * 2022-06-01 K.OHWADA
 */

// Using BCON
// http://mongoc.org/libmongoc/current/tutorial.html

#include <bson/bson.h>


/**
 * main
 */
int main (int   argc, char *argv[])
{
   struct tm born = { 0 };
   struct tm died = { 0 };
   bson_t   *document;
   char     *str;

   born.tm_year = 6;
   born.tm_mon = 11;
   born.tm_mday = 9;

   died.tm_year = 92;
   died.tm_mon = 0;
   died.tm_mday = 1;

   document = BCON_NEW (
      "born", BCON_DATE_TIME (mktime (&born) * 1000),
      "died", BCON_DATE_TIME (mktime (&died) * 1000),
      "name", "{",
      "first", BCON_UTF8 ("Grace"),
      "last", BCON_UTF8 ("Hopper"),
      "}",
      "languages", "[",
      BCON_UTF8 ("MATH-MATIC"),
      BCON_UTF8 ("FLOW-MATIC"),
      BCON_UTF8 ("COBOL"),
      "]",
      "degrees", "[",
      "{", "degree", BCON_UTF8 ("BA"), "school", BCON_UTF8 ("Vassar"), "}",
      "{", "degree", BCON_UTF8 ("PhD"), "school", BCON_UTF8 ("Yale"), "}",
      "]");

   /*
    * Print the document as a JSON string.
    */
   str = bson_as_canonical_extended_json (document, NULL);
   printf ("%s\n", str);
   bson_free (str);

   /*
    * Clean up allocated bson documents.
    */
   bson_destroy (document);
   return 0;
}


// { "born" : { "$date" : { "$numberLong" : "-1990170000000" } }, "died" : { "$date" : { "$numberLong" : "694191600000" } }, "name" : { "first" : "Grace", "last" : "Hopper" }, "languages" : [ "MATH-MATIC", "FLOW-MATIC", "COBOL" ], "degrees" : [ { "degree" : "BA", "school" : "Vassar" }, { "degree" : "PhD", "school" : "Yale" } ] }

