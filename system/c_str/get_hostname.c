/**
 * syatem sample
 * 2020-07-01 K.OHWADA
 */

// get hostname

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


/**
 *  main
 */
int main(void)
{

    const size_t BUFSIZE = 100;
    char  name[BUFSIZE+1] ;

    int ret = gethostname( (char *)name, BUFSIZE);

if(ret == 0){
    printf("%s \n", name);
} else {
    int save_err = errno;
    fprintf(stderr, "%s \n", strerror(save_err) );
    return EXIT_FAILURE;
}

    return EXIT_SUCCESS;
}
