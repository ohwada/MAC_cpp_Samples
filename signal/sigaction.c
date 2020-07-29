/**
 * signal sample
 * 2020-03-01 K.OHWADA
 */

// catch and handle signals using signaction API
// original : https://gist.github.com/doi-t/9001945


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include "signal_util.h"

#define Sigaction(s,a,o)			e_Sigaction((s),(a),(o), __FILE__, __FUNCTION__, __LINE__)


// define the Sigfuc type as a type that represents a void function that returns nothing
typedef void Sigfunc(int);
 

// prototype
void err_msg(const char *, const char *, int, const char *, const char *, ...);

int	e_Sigaction(int, const struct sigaction *, struct sigaction *, const char *, const char *, int);

Sigfunc *Signal(int , Sigfunc *);

// global
static int g_signal = 0;


/**
 * sigint_handler
 */
void sigint_handler(int signo)
{
    printSignal(signo);

    g_signal = 1;

}


/**
 * main
 */
int main(int argc, char **argv)
{

    int mode = 0;
    if(argc==2){
        mode = atoi(argv[1]);
    } else {
        printf("Usage: %s [mode] \n", argv[0]);
    }

	Signal(SIGINT, sigint_handler);
	Signal(SIGQUIT, sigint_handler);
	Signal(SIGUSR1, sigint_handler);
	Signal(SIGUSR2, sigint_handler);


    if(mode == 1){
// restore the specified signal to the default behavior of the OS
        printf("mode1: SIG_DFL \n");
	    Signal(SIGINT, SIG_DFL);
    }


    if(mode == 2){
// ignore the specified signal
        printf("mode2: SIG_ING \n");
	    Signal(SIGINT, SIG_IGN); 
    }

	Signal(SIGCHLD, NULL);

	printf("Signal: %p\n", Signal);

// endless loop until signal is received
    printf("\n loop \n");
    while(1) {
        if (g_signal == 1) break;
        sleep(1);
        fprintf(stderr, ".");
    }
 
    fprintf(stderr, "\n");
    printf("the end\n");

	return 0;
}


/**
 * Signal
 * defining the Sigfunc type simplifies the Signal definition
 */
Sigfunc * Signal(int signo, Sigfunc *func)
{

// act: newly defined action, 
// oact: previous action
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if(signo == SIGALRM){
        // macOS not support
        //For example, if you want to manage the timeout of I/O with alarm(2), interrupt the system call being executed.
		// act.sa_flags |= SA_INTERRUPT;
	} else {
        // restart the system call interrupted by the signal
		act.sa_flags |= SA_RESTART;
	}

	if(signo == SIGCHLD){
        // ignore signal
		act.sa_handler = SIG_IGN;
 
        // dont make the child process a zombie process 
        // functions on Linux 2.6 or later
		act.sa_flags |= SA_NOCLDWAIT;
	}


// call the newly defined wrapper function e_Sigaction
// exit if sigaction(2) fails
	Sigaction(signo, &act, &oact);


// returns NULL, for example, if the caller is responsible for handling the error
	//if(sigaction(signo, &act, &oact) < 0) retrun NULL;

 
// return previous signal settings as return value
	return (oact.sa_handler);
}


/*
Notes on SIGCHLD
SIGCHLD ignores signals by default,
If the handler setting is SIG_DFL, the zombie process will remain.
If the handler is set to SIG_IGN, no zombie process will remain.
If you do not explicitly ignore the same ignorance, a zombie process is created.
*/


/**
 * e_Sigaction
 */
int e_Sigaction(int signum, const struct sigaction *act, struct sigaction *oldact,
		const char *file, const char *function, int line)
{
	int n;
	if((n = sigaction(signum, act, oldact)) < 0){
		err_msg(file, function, line, "error","[%d]=sigaction(%d,%p,%p):%s", n, signum, act, oldact, strerror(errno));
		exit(1);
	}
	return n;
}


/**
 *  err_msg
 */
void err_msg(const char *file, const char *function, int line, const char *type, const char *fmt, ...)
{
	time_t timer;
	time(&timer);
	char *t = ctime(&timer);
	t[strlen(t)-1] = '\0';

// display current time
	fprintf(stderr, "%s ", t); 

// display process ID
	fprintf(stderr, "%d ", getpid());
	fprintf(stderr, "%s %s %d %s ", file, function, line, type);

	va_list ap;
	va_start(ap, fmt);

// sequentially call a variable number of arguments according to the fmt format
	vfprintf(stderr, fmt, ap);

	va_end(ap);

// display error message
	fprintf(stderr, " %s(%d)", strerror(errno), errno); 
	fputc('\n', stderr);
}
