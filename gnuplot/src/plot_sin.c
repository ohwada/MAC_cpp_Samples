/**
 * gnuplot sample
 * 2020-03-01 K.OHWADA
 */

// plot sin wave with popen
// reference : http://ayapin-film.sakura.ne.jp/Gnuplot/Tips/callfrom.html

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "keyboard.h"

/**
 *  main
 */
int main(int argc, char **argv)
{
    const char *CMD = "/usr/local/bin/gnuplot";

    FILE *gp = popen(CMD, "w");
    if(!gp){
        printf("popen faild: %s \n", CMD);
        return 1;
    }

    fprintf(gp, 
        "set title 'popen: sin' \n"
        "plot sin(x) \n"
    );
    fflush(gp);
    sleep(10); // 10 sec

    printf("quit when press ESC key \n \n");
    waitPressESC();

    fprintf(gp,  "exit \n" );
    fflush(gp);
    fclose(gp);
    return 0;
}
