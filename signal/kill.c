/**
 * signal sample
 * 2020-03-01 K.OHWADA
 */

// send signal using kill API

#include <signal.h>
#include <errno.h>


/**
 * main
 */
int main(int argc, char **argv)
{

    if(argc != 2){
        printf("Usage: %s <pid> \n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);

    int ret = kill(pid, SIGUSR1);
    if(ret < 0){
        printf("ERR: kill %d: %s: \n", pid, strerror(errno));
        return(-1);
    }

    printf("kill USR1 %d \n", pid);

    return 0;
}
