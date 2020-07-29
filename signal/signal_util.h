/**
 * signal sample
 * 2020-03-01 K.OHWADA
 */


#include <signal.h>


// prototype
 void printSignal(int signo);


/**
 *  printSignal
 */
void  printSignal (int signo)
{

    if (signo == SIGKILL) {
        printf(" received SIGKILL \n");
    } else if (signo == SIGSTOP) {
        printf(" received SIGSTOP \n");
    } else if (signo == SIGTERM) {
        printf(" received SIGTERM \n");
    } else if (signo == SIGINT) {
        printf(" received SIGINT \n");
    } else if (signo == SIGQUIT) {
        printf(" received SIGIQUIT \n");
    }else if (signo == SIGUSR1) {
        printf(" received SIGUSR1 \n");
    }else if (signo == SIGUSR2) {
        printf(" received SIGUSR2 \n");
    } else {
        printf(" unkown signal: %d \n", signo);
    }

}
