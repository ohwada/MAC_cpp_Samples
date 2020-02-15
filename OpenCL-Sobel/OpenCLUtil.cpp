/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 */


#include "OpenCLUtil.hpp"


/**
 * CreateContext
 */
cl_context CreateContext()
{
    cl_int errNum;
    cl_uint numPlatforms;
    cl_platform_id firstPlatformId;
    cl_context context = NULL;

    // First, select an OpenCL platform to run on.  For this example, we
    // simply choose the first available platform.  Normally, you would
    // query for all available platforms and select the most appropriate one.
    errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
    if (errNum != CL_SUCCESS || numPlatforms <= 0)
    {
        std::cerr << "Failed to find any OpenCL platforms." << std::endl;
        return NULL;
    }

    // Next, create an OpenCL context on the platform.  Attempt to
    // create a GPU-based context, and if that fails, try to create
    // a CPU-based context.
    cl_context_properties contextProperties[] =
    {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)firstPlatformId,
        0
    };
    context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU,
                                      NULL, NULL, &errNum);
    if (errNum != CL_SUCCESS)
    {
        std::cout << "Could not create GPU context, trying CPU..." << std::endl;
        context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU,
                                          NULL, NULL, &errNum);
        if (errNum != CL_SUCCESS)
        {
            std::cerr << "Failed to create an OpenCL GPU or CPU context." << std::endl;
            return NULL;
        }
    }

    return context;
}


/**
 * CreateCommandQueue
 */
cl_command_queue CreateCommandQueue(cl_context context, cl_device_id *device)
{
    cl_int errNum;
    cl_device_id *devices;
    cl_command_queue commandQueue = NULL;
    size_t deviceBufferSize = -1;

    // First get the size of the devices buffer
    errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &deviceBufferSize);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Failed call to clGetContextInfo(...,GL_CONTEXT_DEVICES,...)";
        return NULL;
    }

    if (deviceBufferSize <= 0)
    {
        std::cerr << "No devices available.";
        return NULL;
    }

    // Allocate memory for the devices buffer
    devices = new cl_device_id[deviceBufferSize / sizeof(cl_device_id)];
    errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, deviceBufferSize, devices, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Failed to get device IDs";
        return NULL;
    }

    // In this example, we just choose the first available device.  In a
    // real program, you would likely use all available devices or choose
    // the highest performance device based on OpenCL device queries
    commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);
    if (commandQueue == NULL)
    {
        std::cerr << "Failed to create commandQueue for device 0";
        return NULL;
    }

    *device = devices[0];
    delete [] devices;
    return commandQueue;
}


/**
 * CreateProgram
 */
cl_program CreateProgram(cl_context context, cl_device_id device, std::string fileName)
{
    cl_int errNum;
    cl_program program;

    std::ifstream kernelFile(fileName.c_str(), std::ios::in);
    if (!kernelFile.is_open())
    {
        std::cerr << "Failed to open file for reading: " << fileName << std::endl;
        return NULL;
    }

    std::ostringstream oss;
    oss << kernelFile.rdbuf();

    std::string srcStdStr = oss.str();
    const char *srcStr = srcStdStr.c_str();
    program = clCreateProgramWithSource(context, 1,
                                        (const char**)&srcStr,
                                        NULL, NULL);
    if (program == NULL)
    {
        std::cerr << "Failed to create CL program from source." << std::endl;
        return NULL;
    }

    errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        // Determine the reason for the error
        char buildLog[16384];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
                              sizeof(buildLog), buildLog, NULL);

        std::cerr << "Error in kernel: " << std::endl;
        std::cerr << buildLog;
        clReleaseProgram(program);
        return NULL;
    }

    return program;
}


/**
 * checkImageSupport
 */
bool checkImageSupport(cl_device_id device)
{
    cl_bool imageSupport = CL_FALSE;
    clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(cl_bool),
                    &imageSupport, NULL);

    bool ret = (imageSupport == CL_TRUE)? true: false;
    return ret;
}


/**
 * CreateOutputImage
 */
cl_mem CreateOutputImage(cl_context context, int width, int height) {

    cl_int errNum;
    cl_image_format clImageFormat;
    clImageFormat.image_channel_order = CL_RGBA;
    clImageFormat.image_channel_data_type = CL_UNORM_INT8;

    cl_mem image = clCreateImage2D(context,
                                       CL_MEM_WRITE_ONLY,
                                       &clImageFormat,
                                       width,
                                       height,
                                       0,
                                       NULL,
                                       &errNum);

    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error creating CL output image object." << std::endl;
        return 0;
    }

    return image;
}


/**
 * CreateSampler
 */
cl_sampler CreateSampler(cl_context context) {

    cl_int errNum;
    cl_sampler sampler = clCreateSampler(context,
                              CL_FALSE, // Non-normalized coordinates
                              CL_ADDRESS_CLAMP_TO_EDGE,
                              CL_FILTER_NEAREST,
                              &errNum);

    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error creating CL sampler" << std::endl;
        return 0;
    }

return sampler;
}

/**
 * Cleanup
 */
void Cleanup(
        cl_context context, 
        cl_command_queue commandQueue,
        cl_program program,
        cl_kernel kernel,
        cl_sampler sampler)
{

    if (commandQueue != 0)
        clReleaseCommandQueue(commandQueue);

    if (kernel != 0)
        clReleaseKernel(kernel);

    if (program != 0)
        clReleaseProgram(program);

    if (sampler != 0)
        clReleaseSampler(sampler);

    if (context != 0)
        clReleaseContext(context);

}

/**
 * CleanupMem
 */
void CleanupMem(cl_mem *memObjects, int size)
{
        for (int i = 0; i < size; i++) {
            if (memObjects[i] != 0)
                clReleaseMemObject(memObjects[i]);
        }
}


/**
 * RoundUp
 */
size_t RoundUp(int groupSize, int globalSize)
{
    int r = globalSize % groupSize;
    if(r == 0)
    {
     	return globalSize;
    }
    else
    {
     	return globalSize + groupSize - r;
    }
}


/**
 * LoadImage
 */
cl_mem LoadImage(cl_context context, std::string fileName, int &width, int &height, bool is_gray)
{


    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName.c_str(), 0);
    FIBITMAP* image = FreeImage_Load(format, fileName.c_str());

    FIBITMAP* temp = image;

    if(is_gray) {
        // convert to black and white
        FIBITMAP * gray = 
            FreeImage_ConvertToGreyscale(image);
            if(!gray) {
                std::cerr << "Convert Failed " << std::endl;
                return 0;
            }

        image = FreeImage_ConvertTo32Bits(gray);

    } else {
        image = FreeImage_ConvertTo32Bits(image);
    }

    FreeImage_Unload(temp);

    width = FreeImage_GetWidth(image);
    height = FreeImage_GetHeight(image);

    char *buffer = new char[width * height * 4];
    memcpy(buffer, FreeImage_GetBits(image), width * height * 4);

    FreeImage_Unload(image);

    // Create OpenCL image
    cl_image_format clImageFormat;
    clImageFormat.image_channel_order = CL_RGBA;
    clImageFormat.image_channel_data_type = CL_UNORM_INT8;

    cl_int errNum;
    cl_mem clImage;
    clImage = clCreateImage2D(context,
                            CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                            &clImageFormat,
                            width,
                            height,
                            0,
                            buffer,
                            &errNum);

    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error creating CL image object: " << errNum << std::endl;
        return 0;
    }

    return clImage;
}


/**
 * SaveImage
 */
bool SaveImage(std::string fileName, char *buffer, int width, int height)
{

    FREE_IMAGE_FORMAT format = 
    FreeImage_GetFIFFromFilename(fileName.c_str());

    FIBITMAP *image = FreeImage_ConvertFromRawBits((BYTE*)buffer, width,
                        height, width * 4, 32,
                        0xFF000000, 0x00FF0000, 0x0000FF00);
    return (FreeImage_Save( format, image, fileName.c_str() ) == TRUE) ? true : false;
}
