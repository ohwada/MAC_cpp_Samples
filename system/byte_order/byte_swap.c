/**
 * byte_swap.c
 * 2022-06-01 K.OHWADA
 */

// https://qiita.com/stanaka2/items/8b5da26302ec1eb2930f

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __APPLE__
#include <libkern/OSByteOrder.h>
#define bswap_16 OSSwapInt16
#define bswap_32 OSSwapInt32
#define bswap_64 OSSwapInt64
#else
#include <byteswap.h>
#endif


/**
 * main
 */
int main(int argc, char **argv)
{
  int    ii=-10000, iic;
  uint32_t   ui=10000,  uic;
  float  f=10.12345, fc;
  double d=-200.011, dc;
  int64_t i64=-123456, i64c;
  uint64_t ui64=1234567890123, ui64c;

  iic = bswap_32(ii);
  uic = bswap_32(ui);
  fc  = bswap_32(f);

  dc    = bswap_64(d);
  i64c  = bswap_64(i64);
  ui64c = bswap_64(ui64);

  printf("ii: %0x \n", ii);
  printf("iic: %0x \n", iic);
printf("ui: %0x \n", ui);
printf("uic: %0x \n", uic);
 printf("f: %0x \n", f);
printf("fc: %0x \n", fc);

 printf("d: %0llx \n", d);
 printf("dc: %0llx \n", dc);
 printf("i64: %0llx \n", i64);
 printf("i64c: %0llx \n", i64c);
 printf("ui64: %0llx \n", ui64);
printf("ui64c: %0llx \n", ui64c);

  return EXIT_SUCCESS;
}

