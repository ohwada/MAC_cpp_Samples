/**
 * bmp Sample
 * 2020-02-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "image.h"


image_t *read_bmp_file(const char *filename);

image_t *read_bmp_stream(FILE *fp);

result_t write_bmp_file(const char *filename, image_t *img, int compress); 

result_t write_bmp_stream(FILE *fp, image_t *img, int compress);


