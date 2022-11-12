/**
 * tpcre.c
 * 2022-06-01 K.OHWADA
 */

// reference : http://x768.com/w/pcre.ja

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>


/**
 * main
 */
int main()
{
  pcre *re;
  const char *errptr;
  int erroffset;
  int capture_count;
  int *matches;
  int n_matches;
  int offset = 0;

  const char *pattern = "a(b*)c";
  const char *source = "xiomfseabbBBbbcdegg";

printf("pattern: %s \n", pattern);
printf("source: %s \n", source);

  re = pcre_compile(pattern, PCRE_CASELESS, &errptr, &erroffset, NULL);
  if (re == NULL) {
    fprintf(stderr, "%s at %d\n", errptr, erroffset);
    exit(1);
  }

  pcre_fullinfo(re, NULL, PCRE_INFO_CAPTURECOUNT, &capture_count);
  matches = malloc(sizeof(int) * (capture_count + 1) * 3);

  n_matches = pcre_exec(re, NULL, source, strlen(source), offset, 0, matches, (capture_count + 1) * 3);
  if (n_matches >= 0) {
    int i;
    for (i = 0; i < n_matches; i++) {
      int begin = matches[i * 2];
      int end = matches[i * 2 + 1];
      printf("(%d) : %.*s\n", i, end - begin, &source[begin]);
    }
  } else {
    printf("pattern not found\n");
  }

  return 0;
}
