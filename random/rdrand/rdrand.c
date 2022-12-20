// change log 
// 2022-06-01 K.OHWADA
 // hex mode in default


 // Very fast random byte
// generating command 
// using Intel's rdrand instruction.
// default: 8 byte=64 bit

// https://github.com/SUZUKI-HIRONOBU/rdrand/blob/master/rdrand.c

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*

rdrand : random generator using Intel's rdrand.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or any
later version.

See. https://www.gnu.org/licenses/

$Id: rdrand.c,v 1.1 2019/05/28 06:00:35 hironobu Exp hironobu $

Hironobu SUZUKI <suzuki.hironobu@gmail.com>

 */


/**
 *  call_rdrand64
 */
unsigned char call_rdrand64 (uint64_t *r)
{
	unsigned char ret;
	asm volatile ("rdrand %0; setc %1"
		: "=r" (*r), "=qm" (ret));

	return ret;
}

#define YES 1
#define NO  0


/**
 *  main
 */
int main(int argc, char **argv) 
{
  uint64_t r;
  unsigned char ret;
  int hex=YES;
  int quo = 1; /* quotient : default 8byte = 64bit*/
  int rem = 0; /* remainder */

  if (argc>1) {
    for(int i=1; i < argc ; i++) {
      if( strncmp(argv[i],"--hex",strlen("--hex")) == 0 ) {
	hex=YES;
      }
      if ( isdigit(argv[i][0]) ) {
	int v=atoi(argv[i]);
	quo = v / 8;
	rem = v % 8;
      }
    }
  }
  while( !NULL ){
    if ( (ret=call_rdrand64(&r)) != 1) {
      fprintf(stderr,"rdrand error: %d",ret);
      exit(1);
    }
    if ( quo-- > 0 ) {
      if(hex == YES) {
	printf("%x%x",(unsigned int)(r>>32&0xffffffff),(unsigned int)(r&0xffffffff));
      }
      else {
	fwrite(&r,sizeof(uint64_t),1,stdout);
      }
    }
    else {
      if ( hex == YES) {
	for(int j=rem ; j > 0 ; j--) {
	  printf("%x",(unsigned int)((r >> j*8)&0xff));
	}
      }
      else {
	fwrite(&r,sizeof(unsigned char),rem,stdout);
      }
      break;
    }
  }
  if (hex == YES) {
    puts("");
  }
  exit(0);
}

// d16c58ee11e69a7c

