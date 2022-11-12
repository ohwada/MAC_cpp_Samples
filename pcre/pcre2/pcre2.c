/**
 * tpcre2.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/PCRE2Project/pcre2/blob/master/src/pcre2demo.c

// The PCRE2_CODE_UNIT_WIDTH macro must be defined before including pcre2.h.
#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre2.h>


/**
 * main
 */
int main()
{
    pcre2_code *re;
    int errornumber;
    PCRE2_SIZE erroroffset;
    PCRE2_SIZE subject_length = 0;
    PCRE2_SIZE *ovector;
    pcre2_match_data *match_data;
    int rc;
    PCRE2_SPTR pattern;
    PCRE2_SPTR subject = NULL; 

    pattern = (const unsigned char *)"a(b*)c";
     subject = (const unsigned char *)"xiomfseabbBBbbcdegg";

printf("pattern: %s \n", pattern);
printf(" subject: %s \n",  subject);

  re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED,  PCRE2_CASELESS, &errornumber, &erroroffset, NULL);
  if (re == NULL) {
    PCRE2_UCHAR buffer[256];
    pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
    printf("PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset,
    buffer);
    exit(1);
  }

subject_length = (PCRE2_SIZE)strlen((char *)subject);

match_data = pcre2_match_data_create_from_pattern(re, NULL);

/* Now run the match. */

rc = pcre2_match(
  re,                   /* the compiled pattern */
  subject,              /* the subject string */
  subject_length,       /* the length of the subject */
  0,                    /* start at offset 0 in the subject */
  0,                    /* default options */
  match_data,           /* block for storing the result */
  NULL);                /* use default match context */


printf("rc: %d \n", rc);

if (rc < 0)
  {
  switch(rc)
    {
    case PCRE2_ERROR_NOMATCH: printf("No match\n"); break;
    /*
    Handle other special cases if you like
    */
    default: printf("Matching error %d\n", rc); break;
    }
  pcre2_match_data_free(match_data);   /* Release memory used for the match */
  pcre2_code_free(re);                 /*   data and the compiled pattern. */
  return 1;
  }

/* The output vector wasn't big enough. This should not happen, because we used
pcre2_match_data_create_from_pattern() above. */

if (rc == 0){
  printf("ovector was not big enough for all the captured substrings\n");
}

ovector = pcre2_get_ovector_pointer(match_data);
printf("Match succeeded at offset %d\n", (int)ovector[0]);

if (ovector[0] > ovector[1])
  {
  printf("\\K was used in an assertion to set the match start after its end.\n"
    "From end to start the match was: %.*s\n", (int)(ovector[0] - ovector[1]),
      (char *)(subject + ovector[1]));
  printf("Run abandoned\n");
  pcre2_match_data_free(match_data);
  pcre2_code_free(re);
  return 1;
  }

/* Show substrings stored in the output vector by number. Obviously, in a real
application you might want to do things other than print them. */

for (int i = 0; i < rc; i++)
  {
  PCRE2_SPTR substring_start = subject + ovector[2*i];
  PCRE2_SIZE substring_length = ovector[2*i+1] - ovector[2*i];
  printf("%2d: %.*s\n", i, (int)substring_length, (char *)substring_start);
  }

  return 0;
}
