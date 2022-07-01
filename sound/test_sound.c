/**
 * test_sound.c
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
 #include <stdlib.h>
#include <string.h>

#include "sound.h"

int main(int argc, char* argv[])
{
const int BUFSIZE = 1024;
char buf[BUFSIZE];

	strcpy(buf, "media/Japanese_Temple_Bell_Small.wav");

    if (argc == 2) {
    		strcpy(buf, argv[1]);
    }

	playSound(buf);

	return 0;
}
