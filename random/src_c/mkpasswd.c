/**
 *  random sample
 * 2022-06-01 K.OHWADA
 */


// generate password with passwd.h.
// like LINUX mkpasswd
// parse commandline options with getopt

// reference : https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getopt.3.html
// https://raw.githubusercontent.com/aeruder/expect/master/example/mkpasswd

// Difference from Linux mkpasswd
//
// on Linux mkpasswd
// if You specify the command option as shown below
// You get a warning
// % mkpasswd -d 10
// impossible to generate 9-character password with 10 // numbers, 2 lowercase letters, 2 uppercase letters and 1 special characters.
//
// in this program
// adjust password length
// and generate long passwords


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "passwd.h"


#ifdef DEBUG
    const bool FLAG_DEBUG = true;
#else
    const bool FLAG_DEBUG = false;
#endif


/**
 * main
 */
int main(int argc, char *argv[])
{
    const char ZERO = '\0';

    const int BUFSIZE = 128;
	char buf[BUFSIZE];
	buf[0] = ZERO;

// mkpasswd command options
// https://docs.oracle.com/cd/E36784_01/html/E36870/mkpasswd-1.html
// l : passwd length default: 9
// d : digit default : 2
// c : lower: default 2
// C : upper default : 2
// s : speclal default: 1

    const char* optstring = "l::d::c::C::s::";
    int length = 9;
    int digit = 2;
    int lower = 2;
    int upper = 2;
    int special = 1;

    int opt;
    while ((opt = getopt(argc, argv, optstring )) != -1) {
        switch (opt) {
        case 'l':
            length = atoi(optarg);
            break;
        case 'd':
            digit = atoi(optarg);
            break;
      case 'c':
            lower = atoi(optarg);
            break;
      case 'C':
            upper = atoi(optarg);
            break;
      case 's':
            special = atoi(optarg);
            break;
        } // switch
    } // while

	int mix = length - lower - upper - digit - special;
    if(mix < 0){
        mix = 0;
    }

    if(FLAG_DEBUG) {
        printf("l: %d\n", length);
        printf("d: %d\n", digit);
        printf("c: %d\n", lower);
        printf("C: %d\n", upper);
        printf("s: %d\n", special);
        printf("mix: %d\n", mix);
    }

    genPasswd(buf, BUFSIZE-1, lower, upper,
digit, special, mix );

    if(FLAG_DEBUG) {
        printf("%s \n", buf);
    }

	int len = strlen(buf);
	shuffle( buf, len);

	printf("%s \n", buf);

    exit(EXIT_SUCCESS);
}
 
