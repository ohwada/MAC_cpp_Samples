/**
 * OpenCL Sample
 * Sobel Edge Detection Filter
 * 2020-01-01 K.OHWADA
 */

// Reference :
// OpenCL Programming Guide
// Chapter 15. Sobel Edge Detection Filter
//http://www.heterogeneouscompute.org/?page_id=5


#include "OpenCLFreeImageUtil.hpp"
#include "parse_filename.hpp"



/**
 * LoadImage
 */
cl_mem sobel_LoadImage(cl_context context, std::string fileName, int &width, int &height, bool is_gray)
{

//    Requires FreeImage library for image I/O:
//      http://freeimage.sourceforge.net/

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

    char* data = reverseAndSwap(buffer, width, height);


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
                            data,
                            &errNum);

    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error creating CL image object: " << errNum << std::endl;
        return 0;
    }

    return clImage;
}



/**
 * createOutputFileName
 */
std::string createOutputFileName(std::string input, bool is_gray )
{

    char UNDER_BAR = '_';


    std::string fname = getFileNameWithoutExt(input);

    std::string mode = "rgb";
    if(is_gray) {
        mode = "gray";
    }

    // extension must be PNG 
    std::string output = fname + UNDER_BAR + mode  + UNDER_BAR + "edge.png";

    return output;
}


/**
 *  Sobel
 */
 int Sobel(std::string input, bool is_gray )
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

    std::string output = createOutputFileName(input, is_gray );

    std::string programFile = "sobel_rgb.cl";
    std::string kernelName = "sobel_rgb";
    if(is_gray) {
        programFile = "sobel_gray.cl";
        kernelName = "sobel_grayscale";
    }

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
    int width;
    int height;
    memObjects[0] = sobel_LoadImage(context, input, width, height, is_gray);
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

    // Create OpenCL program
    program = CreateProgram(context, device, programFile);
    if (program == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, sampler);
        CleanupMem(memObjects, memSize);
        return 1;
    }

    std::cout << "create Program from: " << programFile << std::endl;

    // Create OpenCL kernel
    kernel = clCreateKernel(program, kernelName.c_str(), NULL);
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

    std::string input;
    bool is_gray = false;

    if (argc < 2) {
        std::cerr << "USAGE: " << argv[0] << " <inputImageFile> [mode]" << std::endl;
        return 1;
    } else if (argc == 3) {
            input = argv[1];
            std::string arg2 = argv[2];
            if(arg2 == "gray"){
                is_gray = true;
            }

    } else if (argc == 2) {
            input = argv[1];
    }

    return Sobel(input, is_gray);

}

