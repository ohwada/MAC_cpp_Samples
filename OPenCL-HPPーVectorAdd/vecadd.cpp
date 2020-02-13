/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 * original : https://github.com/bgaster/opencl-book-samples/tree/master/src/Chapter_12/VectorAdd
 */

//
// Book:      OpenCL(R) Programming Guide
// Authors:   Aaftab Munshi, Benedict Gaster, Timothy Mattson, James Fung, Dan Ginsburg
// ISBN-10:   0-321-74964-2
// ISBN-13:   978-0-321-74964-2
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780132488006/
//            http://www.openclprogrammingguide.com
//


// vecadd.cpp
//
//    This is a simple example that demonstrates use OpenCL C++ Wrapper API.

// Enable OpenCL C++ exceptions
#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#define BUFFER_SIZE 100

int A[BUFFER_SIZE];
int B[BUFFER_SIZE];
int C[BUFFER_SIZE];

static char
kernelSourceCode[] = 
"__kernel void                                                               \n"
"vadd(__global int * a, __global int * b, __global int * c)                                                                     \n"
"{                                                                           \n"
"    size_t i =  get_global_id(0);                                           \n"
"                                                                            \n"
"    c[i] = a[i] + b[i];                                                     \n"
"}                                                                           \n"
;


/**
 * printError
 */
void printError (cl::Error err, std::string label) 
{
         std::cerr
             << label
             << err.what()
             << "("
             << err.err()
             << ")"
             << std::endl;
}

/**
 * createContext
 */
cl::Context createContext()
{

    cl_int err;

    cl::Context context;
    try {
        std::vector<cl::Platform> platformList;

        // Pick platform
        cl::Platform::get(&platformList);

        if( platformList.size() == 0 ) {
            std::cerr << "can not found OpenCL Platforms" << std::endl;
            return context;
        }

        // Pick first platform
        cl::Platform firstPlatform = platformList[0];

         std::string platform_name = firstPlatform.getInfo<CL_PLATFORM_NAME>();
         std::string platform_version = firstPlatform.getInfo<CL_PLATFORM_VERSION>();

        std::cout << "Platform Name: " << platform_name << std::endl;
        std::cout << "Platform Version: " << platform_version << std::endl;

        cl_context_properties cprops[] = {
            CL_CONTEXT_PLATFORM, (cl_context_properties)(firstPlatform)(), 0};

        context = cl::Context(
            CL_DEVICE_TYPE_GPU, cprops, NULL, NULL, &err);
        if ( err != CL_SUCCESS ) {
            std::cerr << "Failed to Create Context" << std::endl;
        }

    } 
    catch (cl::Error err) 
    {
        printError (err, "createContext ERROR: ");
    }

    return context;
}


/**
 * getDevices
 */
std::vector<cl::Device> getDevices(cl::Context context)
{

    std::vector<cl::Device> devices(0);
    try {

        // Query the set of devices attched to the context
        devices = context.getInfo<CL_CONTEXT_DEVICES>();

        if( devices.size() == 0 ) {
            std::cerr << "can not found OpenCL Devices" << std::endl;
        }

    } 
    catch (cl::Error err) {
        printError (err, "getDevices ERROR: ");
    }

    return devices;
}


/**
 * printDeviceInfo
 */
void printDeviceInfo(cl::Device device)
{

    try {
        std::string device_name = device.getInfo<CL_DEVICE_NAME>();
         std::string device_version = device.getInfo<CL_DEVICE_VERSION>();

        std::cout << "Device Name: " << device_name << std::endl;
        std::cout << "Device Version: " << device_version << std::endl;

    } 
    catch (cl::Error err) {
        printError (err, "printDeviceInfo ERROR: ");
    }

}


/**
 * createKernel
 */
cl::Kernel createKernel(cl::Context context, char*
kernelSourceCode, std::vector<cl::Device> devices, std::string kernelName)
{

    int err;
    cl::Kernel kernel;
    try{
        // Create and program from source
        //cl::Program::Sources sources(1, //std::make_pair(kernelSourceCode, 0));

 	//Program (const Context &context, const string &source, bool build=false, cl_int *err=NULL)

        cl::Program program(context, kernelSourceCode, false, &err);
        if ( err != CL_SUCCESS ) {
            std::cerr << "Failed to Create Program" << std::endl;
        }

        // Build program
        err = program.build(devices);
        if ( err != CL_SUCCESS ) {
            std::cerr << "Failed to build program" << std::endl;
        }

        // Create kernel object
        kernel = cl::Kernel(program, kernelName.c_str(), &err);
        if ( err != CL_SUCCESS ) {
            std::cerr << "Failed to Create Kernel" << std::endl;
        }

    } 
    catch (cl::Error err) 
    {
        printError (err, "createKernel ERROR: ");
    }

    return kernel;
}


/**
 * createInputBuffer
 */
cl::Buffer createInputBuffer( cl::Context  context, int *array)
{

    int err;
    cl::Buffer buffer;
    try {
            buffer = cl::Buffer(
            context, 
            CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
            BUFFER_SIZE * sizeof(int), 
            (void *) array, &err);
            if ( err != CL_SUCCESS ) {
                std::cerr << "Failed to createInputBuffer" << std::endl;
            }        
    } 
    catch (cl::Error err) 
    {
        printError (err, "createInputBuffer ERROR: ");
    }

    return buffer;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    std::cout << "OpenCL C++ Bindings: vecaadd" << std::endl;

    cl_int err;

    // Initialize A, B, C
    for (int i = 0; i < BUFFER_SIZE; i++) {
        A[i] = i;
        B[i] = i * 2;
        C[i] = 0;
    }

    int *output;
    try {

        cl::Context context = createContext();

        std::vector<cl::Device> devices = getDevices(context);
        if(devices.size() == 0) {
                 return EXIT_FAILURE; 
        }

        printDeviceInfo(devices[0]);

        cl::Kernel kernel = createKernel(context, kernelSourceCode, devices, "vadd");

        // Create buffer for A and copy host contents
        cl::Buffer aBuffer = createInputBuffer(context, A);

        // Create buffer for B and copy host contents
        cl::Buffer bBuffer =createInputBuffer(context, B);

        // Create buffer for that uses the host ptr C
        //cl::Buffer cBuffer = createOutputbuffer(context, C);
        cl::Buffer cBuffer = cl::Buffer(
            context, 
            CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, 
            BUFFER_SIZE * sizeof(int), 
            (void *) &C[0], &err);
            if ( err != CL_SUCCESS ) {
                std::cerr << "Failed to create cBuffer" << std::endl;
            } 

        // Set kernel args
        kernel.setArg(0, aBuffer);
        kernel.setArg(1, bBuffer);
        kernel.setArg(2, cBuffer);



        // Create command queue
        cl::CommandQueue queue(context, devices[0], 0);
 
        // Do the work
        queue.enqueueNDRangeKernel(
            kernel, 
            cl::NullRange, 
            cl::NDRange(BUFFER_SIZE), 
            cl::NullRange);
 
// enqueueMapBuffer (const Buffer &buffer, 
//cl_bool blocking, 
//cl_map_flags flags, 
//size_type offset, 
//size_type size, 
//const vector< Event > *events=NULL, 
//Event *event=NULL, cl_int 
//*err=NULL) const

        // Map cBuffer to host pointer. This enforces a sync with 
        // the host backing space, remember we choose GPU device.
            output = (int *) queue.enqueueMapBuffer(
            cBuffer,
            CL_TRUE, // block 
            CL_MAP_READ,
            0,
            BUFFER_SIZE * sizeof(int),
            NULL, NULL, &err);
//CL_INVALID_MEM_OBJECT                       -38
         if ( err != CL_SUCCESS ) {
            std::cerr << "Failed to enqueueMapBuffer" << std::endl;
            return EXIT_FAILURE;
        }

        // Finally release our hold on accessing the memory
        err = queue.enqueueUnmapMemObject(
            cBuffer,
            (void *) output);
         if ( err != CL_SUCCESS ) {
            std::cerr << "Failed to enqueueUnmapMemObject" << std::endl;
            return EXIT_FAILURE;
        }

    } 
    catch (cl::Error err) {
        printError (err, "main ERROR: ");
         return EXIT_FAILURE;
    }

    // print and check output
    std::cout << "output: " << std::endl;
    for (int i = 0; i < BUFFER_SIZE; i++) {
            // check output
           int tmp = A[i] + B[i];
            if ( tmp != output[i] ) {
                std::cout <<  "unmach" << std::endl;
                break;
            }
            // print output
            std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "OpenCL Ssuccesfully" << std::endl;

    return EXIT_SUCCESS;
}
