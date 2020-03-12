/**
 * OpenCL Sample
 * 2020-02-01 K.OHWADA
 */


#include <cstdio>

#include "OpenCLFreeImageUtil.hpp"
#include "parse_filename.hpp"
#include "gaussian_kernel.hpp"


/**
 *  createWeightBuffer
 */
cl_mem createWeightBuffer(cl_context context, kernel_type gaussianKernel, int radius)
{

    float *buffer = convFloatArray1D(gaussianKernel, radius);

    int ksize = calcKernelSize(radius);
    cl_int errcode_ret;

    cl_mem  weightBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float)*ksize*ksize, buffer, &errcode_ret);

    if(errcode_ret != CL_SUCCESS) {
        std::cerr << "Failed to CreateBuffer: " << errcode_ret << std::endl;
        return 0;
    }

    return weightBuffer;
}


/**
 *  GaussianFilter.
 */
 int GaussianFilter(std::string input, std::string output, int radius, double sigma)
{

    std::string programfile = "gaussian_filter.cl";

    cl_context context = 0;
    cl_command_queue commandQueue = 0;
    cl_program program = 0;
    cl_device_id device = 0;
    cl_kernel kernel = 0;
    cl_sampler sampler = 0;
    cl_mem memObjects[3] = {0, 0, 0};
    int memSize = 3;
    cl_int errNum;


    // Create an OpenCL context
    context = CreateContext();
    if (context == NULL)
    {
        std::cerr << "Failed to create OpenCL context." << std::endl;
        return 1;
    }

    // Create a command-queue 
    commandQueue = CreateCommandQueue(context, &device);
    if (commandQueue == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }

    // Make sure the device supports images, otherwise exit
    bool imageSupport = checkImageSupport(device);
    if (!imageSupport)
    {
        std::cerr << "OpenCL device does not support images." << std::endl;
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }

    // Load input image from file and load it into
    // an OpenCL mem object
    int width, height;
    memObjects[0] = LoadImage(context, input, width, height);
    if (memObjects[0] == 0)
    {
        std::cerr << "Error loading: " << input << std::endl;
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }

    // Create ouput an to OpenCL mem object
    memObjects[1] = CreateOutputImage(context, width, height);
    if (memObjects[1] == 0)
    {
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }

    // Create Gaussian Kernel
    kernel_type kernel2d = produce2dGaussianKernel(radius, sigma);

    printGaussianKernelTitle(radius, sigma);
    printGaussianKernel(kernel2d);

    // Create Gaussian Kernel to  to an OpenCL mem object
    memObjects[2] = createWeightBuffer(context, kernel2d,  radius);
    if(memObjects[2] == 0) 
    {
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }


        
    // Create sampler for sampling image object
    sampler = CreateSampler(context);
    if(sampler == 0) 
    {
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }


    // Create OpenCL program
    program = CreateProgram(context, device, programfile);
    if (program == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }



    // Create OpenCL kernel
    kernel = clCreateKernel(program, "gaussian_filter", NULL);
    if (kernel == NULL)
    {
        std::cerr << "Failed to create kernel" << std::endl;
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }


    // Set the kernel arguments
    errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
    errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);

     errNum |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &memObjects[2]);

    errNum |= clSetKernelArg(kernel, 3, sizeof(cl_sampler), &sampler);
    errNum |= clSetKernelArg(kernel, 4, sizeof(cl_int), &width);
    errNum |= clSetKernelArg(kernel, 5, sizeof(cl_int), &height);
    errNum |= clSetKernelArg(kernel, 6, sizeof(cl_int), &radius);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error setting kernel arguments: " << errNum << std::endl;
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }


    size_t localWorkSize[2] = { 16, 16 };
    size_t globalWorkSize[2] =  { RoundUp(localWorkSize[0], width),
                                  RoundUp(localWorkSize[1], height) };

    // Queue the kernel up for execution
    errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL,
                                    globalWorkSize, localWorkSize,
                                    0, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error queuing kernel for execution: " << errNum << std::endl;
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }


    // Read the output buffer back to the Host
    char *buffer = new char [width * height * 4];
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3] = { (size_t)width, (size_t)height, 1};

    errNum = clEnqueueReadImage(commandQueue, memObjects[1], CL_TRUE,
                                origin, region, 0, 0, buffer,
                                0, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error reading result buffer." << std::endl;
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }

    std::cout << "Executed program succesfully." << std::endl;

    // Save the image out to disk
    bool ret = SaveImage(output, buffer, width, height);

    // Cleanup
    Cleanup(context, commandQueue, program, kernel, sampler);
    CleanupMem(memObjects, memSize);
    delete [] buffer;

    if (!ret) {
        std::cerr << "Error writing output image: " << output << std::endl;
        return 1;
    }

    std::cout << "save to output: " << output << std::endl;
    return 0;
}


/**
 * createOutputFileName
 */
std::string createOutputFileName(std::string input, int radius, double sigma )
{

    char UNDER_BAR = '_';

    std::string fname = getFileNameWithoutExt(input);

    int ksize = calcKernelSize(radius);
    std::string str_ksize = std::to_string(ksize);

    std::string str_sigma = d2str(sigma, "%0.1f");

    // extension must be PNG 
    std::string output = fname + UNDER_BAR + str_ksize + "x" + str_ksize + UNDER_BAR + str_sigma + UNDER_BAR + ".png";

    return output;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    std::string input;
    std::string output;

    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <inputImageFile> <radius> <sigma> " << std::endl;
        return 1;
    } 

    input = argv[1];

    int radius =  std::atoi(argv[2]);

    double sigma =  str2d(argv[3]);

    output = createOutputFileName(input, radius, sigma );

    return GaussianFilter( input, output, radius, sigma);

}
