/**
 * getopt sample
 * 2020-03-01 K.OHWADA
 */


// parse commandline options with getopt
// reference : https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getopt.3.html


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


/**
 * main
 */
int main(int argc, char *argv[])
{

    int opt;
    int nsecs = 0;
    int tfnd = 0;
    int flags = 0;

    while ((opt = getopt(argc, argv, "nt:")) != -1) {
        switch (opt) {
        case 'n':
            flags = 1;
            break;
        case 't':
            nsecs = atoi(optarg);
            tfnd = 1;
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
            exit(EXIT_FAILURE);

        } // switch
    } // while

 printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n",
            flags, tfnd, nsecs, optind);

    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    printf("name argument = %s\n", argv[optind]);

    /* Other code omitted */

    exit(EXIT_SUCCESS);
}
 

// % ./a.out
// flags=0; tfnd=0; nsecs=0; optind=1
// Expected argument after options


// % ./a.out -t 10 -n hoge
// flags=1; tfnd=1; nsecs=10; optind=4
// name argument = hoge

