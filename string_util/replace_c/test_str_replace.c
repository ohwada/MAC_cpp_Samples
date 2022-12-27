/**
 * test_str_replace.c
 * 2022-06-01 K.OHWADA
 */

# include <stdio.h>
# include <assert.h>
# include "str_replace.h"


/**
 * main
 */
int main()
{
    const size_t BUFSIZE = 100;
    char result[BUFSIZE]; 

    char *src = "The quick brown fox jumps over the lazy dog";
    char *target = "brown";
    char *replace = "white";

    char *expect = "The quick white fox jumps over the lazy dog";

    bool ret = str_replace(src, target, replace, (char *)result );
    if(!ret){
        printf("cannot replace");
    }

    printf("%s \n", src);
    printf("%s \n", result);

    assert(strcmp(result, expect)==0);

    printf("successful \n");

    return 0;
}

// The quick brown fox jumps over the lazy dog 
// The quick white fox jumps over the lazy dog 
// successful 
