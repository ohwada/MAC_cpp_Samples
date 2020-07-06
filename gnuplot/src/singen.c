/**
 * gnuplot sample
 * 2020-03-01 K.OHWADA
 */

// genarete sin wave data to stdout
// reference : https://bluefish.orz.hm/sdoc/fftw_sim.html#%E6%AD%A3%E5%BC%A6%E6%B3%A2%E7%99%BA%E7%94%9F


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>


#define SAMPLINGRATE 1000000 // 1MHz
#define MAX      32767
#define POINT  1000000


/**
 *  main
 */
int main( int argc, char **argv )
{

    int freq = 1000; // 1KHz

    if(argc == 2){
        freq = atoi(argv[1]);
    } else{
        // printf("Usage: %s <freq> \n", argv[0]);
    }

    double d = 2*M_PI*(double)freq/SAMPLINGRATE;

    for (int i=0; i<POINT ; i++) {
          double out = (MAX/2) * sin(i*d);
          printf("%d \n",(int)out);
    }

    return 0;
}
