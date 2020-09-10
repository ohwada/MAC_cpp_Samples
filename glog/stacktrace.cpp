/**
 * glog sample
 * 2020-03-01 K.OHWADA
 */

// display stack trace when CRUSH
// reference : https://daily.belltail.jp/?p=1487

#include <glog/logging.h>


/**
 * div_zero
 */
void div_zero()
{
// division by zero
    int a = 1;
    int b = 0;

//  floating point exception
    int c = a / b;

}



/**
 * func
 */
void func()
{
    div_zero();

// Note;
// on macOS
// display no stacktrace , when throw exception
// https://stackoverflow.com/questions/9964839/backtracing-when-uncaught-exception-on-mac-osx
// throw;

}



/**
 * main
 */
int main(int argc, char *argv[])
{

    google::InitGoogleLogging(argv[0]);

// set a signal handler that emits a stack trace on CRASH
     google::InstallFailureSignalHandler();
  
    func();

    return 0;
}

// Aborted at 1599527194 (unix time) try "date -d 
// @1599527194" if you are using GNU date 
// PC: @                0x0 (unknown)
// SIGFPE (@0x1091a6f36) received by PID 40631 
// (TID 0x10ba1fdc0) stack trace: 
//    @     0x7fff6ca515fd _sigtramp
//    @        0x1091a6f37 div_zero()
//    @        0x1091a6f49 func()
//    @        0x1091a6f7c main
// zsh: floating point exception  ./trace
