/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 *  original : https://github.com/bgaster/opencl-book-samples/tree/master/src/Chapter_14/histogram
 */

#include <iostream>
#include <string>

#include "histogram_util.hpp"


/**
 * getDevice
 */
cl_device_id getDevice()
{
    cl_device_id device;
    cl_device_type device_type = CL_DEVICE_TYPE_GPU;
    int err;

#if (__APPLE__) || defined(__MACOSX)
    cl_platform_id platform = NULL;
#else
    cl_platform_id platform = NULL;
    err = clGetPlatformIDs(1, &platform, NULL);
    if(err != CL_SUCCESS)
    {
        printf("clGetPlatformIDs() failed. (%d)\n", err);
        return 0;
    }
#endif

    err = clGetDeviceIDs(platform, device_type, 1, &device, NULL);
    if(err != CL_SUCCESS)
    {
        printf("clGetDeviceIDs() failed. (%d)\n", err);
        return 0;
    }

    // Dump device information
    char    deviceName[ 512 ];
    char    deviceVendor[ 512 ];
    char    deviceVersion[ 512 ];
    err = clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof( deviceVendor ),
                           deviceVendor, NULL);
    err |= clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof( deviceName ),
                          deviceName, NULL);
    err |= clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof( deviceVersion ),
                           deviceVersion, NULL);

    printf("Device Vendor: %s \n", deviceVendor); 
    printf("Device Name: %s \n",  deviceName);
    printf("Device Version: %s \n",  deviceVersion);

    size_t ext_size = 0;
    err |= clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 0, NULL, &ext_size);
    if (err != CL_SUCCESS) {
        printf("clGetDeviceInfo() failed. (%d)\n", err);
        return 0;
    }

    return device;
}


/**
 * check32bitLocalAtomicsSupport
 */
bool check32bitLocalAtomicsSupport(cl_device_id device)
{
    int ext_size = 1024;
    char ext_string[ext_size];
    int err;

    // Check if 32 bit local atomics are supported
    err = clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, sizeof( ext_string ), ext_string, NULL);
    if (err != CL_SUCCESS) {
        printf("clGetDeviceInfo() failed. (%d)\n", err);
        return false;
    }

    if (!strstr(ext_string, "cl_khr_local_int32_base_atomics")) {
        printf("Skipping: histogram requires local atomics support\n");
        return false;
    }

    return true;
}


/**
 * createContext
 */
cl_context createContext(cl_device_id device)
{
    cl_context context;
    int err;
    context = clCreateContext( 0, 1, &device, NULL, NULL, &err);
    if (!context || err)
    {
        printf("clCreateContext() failed. (%d)\n", err);
        return 0;
    }

    return context;
}


/**
 * createCommandQueue
 */
cl_command_queue createCommandQueue(cl_context context, cl_device_id device)
{
    cl_command_queue queue;
    int err;
    queue = clCreateCommandQueue( context, device, CL_QUEUE_PROFILING_ENABLE, &err);
    if(!queue || err)
    {
        printf("clCreateCommandQueue() failed. (%d)\n", err);
        return 0;
    }

    return queue;
}


/**
 * releaseResource
 */
void releaseResource(cl_context context, cl_command_queue queue)
{
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
}


/**
 * read_kernel_from_file
 */
 
static int 
read_kernel_from_file(const char *filename, char **source, size_t *len)
{
    struct stat statbuf;
    FILE        *fh;
    size_t      file_len;
    
    fh = fopen(filename, "r");
    if (fh == 0)
        return -1;
    
    stat(filename, &statbuf);
    file_len = (size_t)statbuf.st_size;
    *len = file_len;
    *source = (char *) malloc(file_len+1);
    fread(*source, file_len, 1, fh);
    (*source)[file_len] = '\0';
    
    fclose(fh);
    return 0;
}



/**
 * createProgramFromFile
 */
cl_program createProgramFromFile(cl_context context, cl_device_id device, const char *filename)
{ 

    cl_program program;
	size_t src_len[1];
    char  *source[1];
   int err;

    err = read_kernel_from_file(KERNEL_FILENAME, &source[0], &src_len[0]);
    if(err)
    {
        printf("read_kernel_from_file() failed. (%s) file not found\n", KERNEL_FILENAME);
        return 0;
    }

    program = clCreateProgramWithSource(context, 1, (const char **)source, (size_t *)src_len, &err);
    if(!program || err)
    {
        printf("clCreateProgramWithSource() failed. (%d)\n", err);
        return 0;
    }
    //free(source[0]);
  
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if(err != CL_SUCCESS)
    {
        char    buffer[2048] = "";
        printf("clBuildProgram() failed.\n");
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
        printf("Log:\n%s\n", buffer);
        return 0;
    }

    return program;
}


/**
 * createHistogramBuffer
 * tore the total histogram obtained by summing the partial histograms
 */    
cl_mem createHistogramBuffer(cl_context context)
{
    cl_mem buffer;
    int err;
    buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 257*3*sizeof(unsigned int), NULL, &err);
    if (!buffer || err)
    {
        printf("createHistogramBuffer failed. (%d)\n", err);
        return 0;
    }

    return buffer;
}



/**
 * createPartialHistogramBuffer
 * work area for target GPU to read and write partial histograms
 * No access from host CPU
 */    
cl_mem createPartialHistogramBuffer(cl_context context, size_t  num_groups)
{
    cl_mem buffer;
    int err;
    buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, num_groups*257*3*sizeof(unsigned int), NULL, &err);
    if (!buffer || err)
    {
        printf("createPartialHistogramBuffer failed. (%d)\n", err);
        return 0;
    }

    return buffer;
}


/**
 * save_histogram
 */
int save_histogram(std::string output, unsigned int *histgram)
{

    char LF = '\n';
    std::string COMMA = ", ";

    std::string red = "";
    std::string green = "";
    std::string blue = "";

    for(int i=0; i<256; i++){
         red += std::to_string(histgram[i]) + COMMA;
         green += std::to_string(histgram[256 + i]) + COMMA;
         blue += std::to_string(histgram[2*256 + i]) + COMMA;
    }

    std::string data = "";
    data += red + LF;
    data += green + LF;
    data += blue + LF;

    // open output file
    std::ofstream fout; 
    fout.open(output, std::ios::out); 
    if (fout.fail()){ 
        std::cerr << "open output file failed: " << output << std::endl;
        return 1;
    } 

    // write to output file
    fout<< data;
    fout.close();

    std::cout << "save to: " << output << std::endl;
    return 0;
}

