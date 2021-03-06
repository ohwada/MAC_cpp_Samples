// https://github.com/json-c/json-c/blob/json-c-0.15-20200726/tests/parse_flags.c



#include <stdio.h>
#include <string.h>
#include <config.h>
#include <json.h>
#include "parse_flags.h"

#if !defined(HAVE_STRCASECMP) && defined(_MSC_VER)
#define strcasecmp _stricmp
#elif !defined(HAVE_STRCASECMP)
#error You do not have strcasecmp on your system.
#endif /* HAVE_STRNCASECMP */


/**
 *  struct
 */
static struct
{
	const char *arg;
	int flag;
} format_args[] = {
    {"plain", JSON_C_TO_STRING_PLAIN},
    {"spaced", JSON_C_TO_STRING_SPACED},
    {"pretty", JSON_C_TO_STRING_PRETTY},
    {"pretty_tab", JSON_C_TO_STRING_PRETTY_TAB},
};


#ifndef NELEM
#define NELEM(x) (sizeof(x) / sizeof(x[0]))
#endif


/**
 *  parse_flags
 */
int parse_flags(int argc, char **argv)
{
	int arg_idx;
	int sflags = 0;
	for (arg_idx = 1; arg_idx < argc; arg_idx++)
	{
		int jj;
		for (jj = 0; jj < (int)NELEM(format_args); jj++)
		{
			if (strcasecmp(argv[arg_idx], format_args[jj].arg) == 0)
			{
				sflags |= format_args[jj].flag;
				break;
			}
		}
		if (jj == NELEM(format_args))
		{
			printf("Unknown arg: %s\n", argv[arg_idx]);
			exit(1);
		}
	}
	return sflags;
}
