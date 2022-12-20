/**
 *  urandom.c
 * 2022-06-01 K.OHWADA
 */

// read random number from /dev/crandom

// wikipedia: /dev/random
// /dev/random and /dev/urandom are special files 
// that serve as cryptographically secure pseudorandom number generators.
// https://en.wikipedia.org/wiki//dev/random

// reference :  https://kaworu.jpn.org/kaworu/2008-06-13-2.php

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define DEV_RANDOM "/dev/urandom"
#define BUF 256


/**
 *  get_random
  */
int get_random (char * const buf, const int buflen, const int len)
{
	if (len > buflen)
	{
		warnx ("buffer size is small (%d / %d)", buflen, len);
		return (-1);
	}
	int fd = open(DEV_RANDOM, O_RDONLY);
	if (fd == -1)
	{
		warn ("can not open %s", DEV_RANDOM);
		return (-1);
	}
	int r = read (fd, buf, len);
	if (r < 0) {
		warn ("can not read");
		return (-1);
	}
	if (r != len)
	{
		warnx ("can not read(%d != %d)", r, len);
		return (-1);
	}

	(void) close (fd);
	return (0);
}


/**
 *  dump_hex
  */
void dump_hex(const char *p, const int len)
{

	printf ("len = %d \n", len);

	for (int i = 0; i < len; ++i)
	{
		unsigned char c = p[i];
		printf ("%02x ", c);
	} // for
	printf ("\n");
}


/**
 *  main
  */
int main (int argc, char *argv[])
{
	char	buf[BUF];
	int	buflen = sizeof(buf);

	int	len = 4;

	if (get_random(buf, buflen, len) == 0) {
		dump_hex(buf, len);
	}
	(void) printf ("\n");

	exit (EXIT_SUCCESS);
}

// len = 4 
// a5 dd 43 9b 
