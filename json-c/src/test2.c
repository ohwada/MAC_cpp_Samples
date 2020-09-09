/**
 * json-c Sample
 * 2020-03-01 K.OHWADA
 */

// parse JSON from string
// and convert to string
// original : https://github.com/json-c/json-c/blob/json-c-0.15-20200726/tests/test2.c

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "parse_flags.h"

#ifdef TEST_FORMATTED
#define json_object_to_json_string(obj) json_object_to_json_string_ext(obj, sflags)
#else
/* no special define */
#endif

int main(int argc, char **argv)
{
	json_object *new_obj;
#ifdef TEST_FORMATTED
	int sflags = 0;
#endif

	MC_SET_DEBUG(1);

#ifdef TEST_FORMATTED
	sflags = parse_flags(argc, argv);
#endif

	new_obj = json_tokener_parse(
	    "/* more difficult test case */"
	    "{ \"glossary\": { \"title\": \"example glossary\", \"GlossDiv\": { \"title\": \"S\", "
	    "\"GlossList\": [ { \"ID\": \"SGML\", \"SortAs\": \"SGML\", \"GlossTerm\": \"Standard "
	    "Generalized Markup Language\", \"Acronym\": \"SGML\", \"Abbrev\": \"ISO 8879:1986\", "
	    "\"GlossDef\": \"A meta-markup language, used to create markup languages such as "
	    "DocBook.\", \"GlossSeeAlso\": [\"GML\", \"XML\", \"markup\"] } ] } } }");
	printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
	json_object_put(new_obj);

	return EXIT_SUCCESS;
}
