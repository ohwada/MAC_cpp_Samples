/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#include <FreeImage.h>


cl_context CreateContext();

cl_command_queue CreateCommandQueue(cl_context context, cl_device_id *device);

cl_program CreateProgram(cl_context context, cl_device_id device, std::string fileName);

void Cleanup(cl_context context, cl_command_queue commandQueue,
             cl_program program, cl_kernel kernel,
             cl_sampler sampler);

void CleanupMem(cl_mem *memObjects, int size);

bool checkImageSupport(cl_device_id device);

cl_sampler CreateSampler(cl_context context);

size_t RoundUp(int groupSize, int globalSize);

cl_mem CreateOutputImage(cl_context context, int width, int height);

cl_mem LoadImage(cl_context context, std::string fileName, int &width, int &height);

bool SaveImage(std::string fileName, char *buffer, int width, int height);


