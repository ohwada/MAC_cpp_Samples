/**
 * string sample
 * 2020-07-01 K.OHWADA
 */

// replace string all

# include <stdio.h>
# include "str_replace.h"


/**
 *  main
 */
int main(void) 
{

    char src[] = "hello world hello japan";

    char *target1  = "hello";
    char *replace1 = "goodby";

    char result[100];

    printf("%s\n", src);

    bool ret1 = str_replace_all( src, target1, replace1, (char *)result );
    if(ret1){
        printf("%s\n", result); 
    }else {
        fprintf(stderr, "not found: %s \n", target1); 
        return EXIT_FAILURE;
    }

    char *target2  = "abc";
    char *replace2 = "xyz";

    bool ret2 = str_replace_all( src, target2, replace2, (char *)result );
    if(ret2){
        printf("%s\n", result); 
    }else {
        fprintf(stderr, "not found: %s \n", target2); 
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


// hello world hello japan
// goodby world goodby japan
// not found: abc 


