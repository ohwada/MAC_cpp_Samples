/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef  __APPLE__
    #include <OpenCL/opencl.h>
#else
    #include <CL/cl.h>
#endif


const char  KERNEL_FILENAME[]    = "image_histogram.cl";

const int NUM_PIXELS_PER_WORK_ITEM = 32;

const int NUM_ITERATIONS = 1000;


cl_device_id getDevice();

bool check32bitLocalAtomicsSupport(cl_device_id device);

cl_context createContext(cl_device_id device);

cl_command_queue createCommandQueue(cl_context context, cl_device_id device);

void releaseResource(cl_context context, cl_command_queue queue);

cl_program createProgramFromFile(cl_context context, cl_device_id device, const char *filename);
   
cl_mem createHistogramBuffer(cl_context context);

cl_mem createPartialHistogramBuffer(cl_context context, size_t  num_groups);

int save_histogram(std::string output, unsigned int *histgram);

