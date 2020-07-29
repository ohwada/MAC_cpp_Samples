/**
 * signal sample
 * 2020-03-01 K.OHWADA
 */

// catch and handle signals using signal API
// reference : https://uguisu.skr.jp/Windows/c_signal.html


#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
 #include "signal_util.h"


static int g_signal = 0;
 

/**
 * sig_handler
 */
void sig_handler(int signo)
{
    printSignal(signo);
    g_signal = 1;
}
 

/**
 * main
 */
int main(void)
{

    printf("pid: %d \n", getpid());

// signal handler settings   
    if (signal(SIGKILL, sig_handler) == SIG_ERR) {
        // SIGKILL : not support
        printf("\ncan't catch SIGKILL \n");
        printf("ERR: %d %s \n", errno,  strerror(errno));
    }
 
    if (signal(SIGSTOP, sig_handler) == SIG_ERR) {
      // SIGSTOP : not support
        printf("\ncan't catch SIGSTOP \n");
        printf("ERR: %d %s \n", errno,  strerror(errno));
    }
 
    if (signal(SIGTERM, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SITERM \n");
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGINT \n");
    }

    if (signal(SIGQUIT, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGQUIT \n");
    }

    if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGUSR1 \n");
    }
 
    if (signal(SIGUSR2, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGUSR2 \n");
    }



// endless loop until signal is received
    printf("\n loop \n");
    while(1) {
        if (g_signal == 1) break;
        sleep(1);
        fprintf(stderr, ".");
    }
 
    fprintf(stderr, "\n");
    printf("the end \n");

    return 0;
}

