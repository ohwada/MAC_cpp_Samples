/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 * original : https://github.com/bgaster/opencl-book-samples/tree/master/src/Chapter_8/ImageFilter2D
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

// ImageFilter2D.cpp
//
//    This example demonstrates performing gaussian filtering on a 2D image using
//    OpenCL
//
//    Requires FreeImage library for image I/O:
//      http://freeimage.sourceforge.net/

#include "OpenCLUtil.hpp"
#include "parse_filename.hpp"


/**
 *  ImageFilter2D
 */
 int ImageFilter2D(std::string programfile, std::string input, std::string  output )
{

    cl_context context = 0;
    cl_command_queue commandQueue = 0;
    cl_program program = 0;
    cl_device_id device = 0;
    cl_kernel kernel = 0;
    cl_sampler sampler = 0;
    cl_mem memObjects[2] = { 0, 0 };
    int memSize = 2;
    cl_int errNum;


    // Create an OpenCL context on first available platform
    context = CreateContext();
    if (context == NULL)
    {
        std::cerr << "Failed to create OpenCL context." << std::endl;
        return 1;
    }

    // Create a command-queue on the first device available
    // on the created context
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
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }

    // Load input image from file and load it into
    // an OpenCL image object
    int width, height;
    memObjects[0] = LoadImage(context, input, width, height);
    if (memObjects[0] == 0)
    {
        std::cerr << "Error loading: " << input << std::endl;
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }

    // Create ouput image object
        memObjects[1] = CreateOutputImage(context, width, height);
    if (memObjects[1] == 0)
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

    std::cout << "create Program from: " << programfile << std::endl;

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
    errNum |= clSetKernelArg(kernel, 2, sizeof(cl_sampler), &sampler);
    errNum |= clSetKernelArg(kernel, 3, sizeof(cl_int), &width);
    errNum |= clSetKernelArg(kernel, 4, sizeof(cl_int), &height);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error setting kernel arguments." << std::endl;
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
        std::cerr << "Error queuing kernel for execution." << std::endl;
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

    std::cout << std::endl;
    std::cout << "Executed program succesfully." << std::endl;

    //memset(buffer, 0xff, width * height * 4);
    // Save the image out to disk
    bool ret = SaveImage(output, buffer, width, height);

    // Cleanup
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        delete [] buffer;

    if (!ret)
    {
        std::cerr << "Error writing output image: " << output << std::endl;
        return 1;
    }

    std::cout << "save to output: " << output << std::endl;

    return 0;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    std::string programfile;
    std::string input;
    std::string output;
    bool is_five = false;

    if (argc < 2) {
        std::cerr << "USAGE: " << argv[0] << " <inputImageFile> [kernel size]" << std::endl;
        return 1;

    } else if (argc == 3) {
            input = argv[1];
            std::string arg2 = argv[2];
            if(arg2 == "5"){
                is_five = true;
            }

    } else if (argc == 2) {
            input = argv[1];
    }

    std::string dir;
    std::string title;
    std::string ext;
    parseFileName(input, dir, title, ext);

    std::string matrix = "_3x3";
    if(is_five) {
        matrix = "_5x5";
    }

    programfile = "gaussian_filter" + matrix  + ".cl";

    // extension must be PNG 
    output = title + matrix + ".png";

    return ImageFilter2D(programfile, input, output);

}
