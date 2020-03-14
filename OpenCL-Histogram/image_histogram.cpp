/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 *  original : https://github.com/bgaster/opencl-book-samples/tree/master/src/Chapter_14/histogram
 */


#include "histogram_util.hpp"

#include "devil_util.hpp"

#include "parse_filename.hpp"


/**
 * LoadImage
 */
cl_mem LoadImage(cl_context context, std::string fileName, int &width, int &height)
{

    char* image = devil_loadImage(fileName, width, height);

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
                            image,
                            &errNum);

    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error creating CL image object" << std::endl;
        return 0;
    }

    return clImage;
}


/**
 * image_histogram
 */
int
image_histogram(std::string input, std::string output)
{

    cl_kernel           histogram_rgba_unorm8;
    cl_kernel           histogram_sum_partial_results_unorm8;
    cl_image_format     image_format;

    size_t              global_work_size[2];
    size_t              local_work_size[2];
    size_t              partial_global_work_size[2];
    size_t              partial_local_work_size[2];
    size_t              workgroup_size;
    size_t              num_groups;

    unsigned int       *histogram_results;

    void                *image_data_unorm8;

    cl_mem              input_image_unorm8;
    cl_mem              histogram_buffer;
    cl_mem              partial_histogram_buffer;

    cl_event            events[2];
    cl_ulong            time_start, time_end;
	size_t              src_len[1];
    char                *source[1];
    int                 i, err;

    cl_device_id device = getDevice();
    if(device == 0){
        return EXIT_FAILURE;
    }

    check32bitLocalAtomicsSupport(device);

    cl_context context = createContext(device);
    if(!context){
        return EXIT_FAILURE;
    }

    cl_command_queue queue = createCommandQueue(context, device);
    if(!queue){
        return EXIT_FAILURE;
    }
 
    cl_program program = createProgramFromFile(context, device, KERNEL_FILENAME);
    if(program == 0){
        return EXIT_FAILURE;
    }

    histogram_rgba_unorm8 = clCreateKernel(program, "histogram_image_rgba_unorm8", &err);
    if(!histogram_rgba_unorm8 || err)
    {
        printf("clCreateKernel() failed creating kernel void histogram_rgba_unorm8(). (%d)\n", err);
        return EXIT_FAILURE;
    }

    histogram_sum_partial_results_unorm8 = clCreateKernel(program, "histogram_sum_partial_results_unorm8", &err);
    if(!histogram_sum_partial_results_unorm8 || err)
    {
        printf("clCreateKernel() failed creating kernel void histogram_sum_partial_results_unorm8(). (%d)\n", err);
        return EXIT_FAILURE;
    }


    histogram_buffer = createHistogramBuffer(context);
    if (!histogram_buffer )
    {
        return EXIT_FAILURE;
    }


    int width;
    int height;
    input_image_unorm8 = LoadImage(context, input, width, height);
    if (!input_image_unorm8 )
    {
        return EXIT_FAILURE;
    }
    
// RGBA 8-bit histogram
    clGetKernelWorkGroupInfo(histogram_rgba_unorm8, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &workgroup_size, NULL);
    {
        size_t  gsize[2];
        int     w;
        
        if (workgroup_size <= 256)
        {
            gsize[0] = 16;
            gsize[1] = workgroup_size / 16;
        }
        else if (workgroup_size <= 1024)
        {
            gsize[0] = workgroup_size / 16;
            gsize[1] = 16;
        }
        else
        {
            gsize[0] = workgroup_size / 32;
            gsize[1] = 32;
        }
        
        local_work_size[0] = gsize[0];
        local_work_size[1] = gsize[1];
        
        w = (width + NUM_PIXELS_PER_WORK_ITEM - 1) / NUM_PIXELS_PER_WORK_ITEM;
        global_work_size[0] = ((w + gsize[0] - 1) / gsize[0]);
        global_work_size[1] = ((height + gsize[1] - 1) / gsize[1]);

        num_groups = global_work_size[0] * global_work_size[1];    
        global_work_size[0] *= gsize[0];
        global_work_size[1] *= gsize[1];
    }    

    partial_histogram_buffer = createPartialHistogramBuffer(context, num_groups);
    if (!partial_histogram_buffer)
    {
        return EXIT_FAILURE;
    }

    clSetKernelArg(histogram_rgba_unorm8, 0, sizeof(cl_mem), &input_image_unorm8);
    clSetKernelArg(histogram_rgba_unorm8, 1, sizeof(int), &NUM_PIXELS_PER_WORK_ITEM);
    clSetKernelArg(histogram_rgba_unorm8, 2, sizeof(cl_mem), &partial_histogram_buffer);
    

    clSetKernelArg(histogram_sum_partial_results_unorm8, 0, sizeof(cl_mem), &partial_histogram_buffer);
    clSetKernelArg(histogram_sum_partial_results_unorm8, 1, sizeof(int), &num_groups);
    clSetKernelArg(histogram_sum_partial_results_unorm8, 2, sizeof(cl_mem), &histogram_buffer);


    // excute kernel
    err = clEnqueueNDRangeKernel(queue, histogram_rgba_unorm8, 2, NULL, global_work_size, local_work_size, 0, NULL, NULL);
    if (err)
    {
        printf("clEnqueueNDRangeKernel() failed for histogram_rgba_unorm8 kernel. (%d)\n", err);
        return EXIT_FAILURE;
    }
    
    clGetKernelWorkGroupInfo(histogram_sum_partial_results_unorm8, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &workgroup_size, NULL);
    if (workgroup_size < 256)
    {
        printf("A min. of 256 work-items in work-group is needed for histogram_sum_partial_results_unorm8 kernel. (%d)\n", (int)workgroup_size);
        return EXIT_FAILURE;
    }

    partial_global_work_size[0] = 256*3;
    partial_local_work_size[0] = (workgroup_size > 256) ? 256 : workgroup_size;
    err = clEnqueueNDRangeKernel(queue, histogram_sum_partial_results_unorm8, 1, NULL, partial_global_work_size, partial_local_work_size, 0, NULL, NULL);
    if (err)
    {
        printf("clEnqueueNDRangeKernel() failed for histogram_sum_partial_results_unorm8 kernel. (%d)\n", err);
        return EXIT_FAILURE;
    }


    histogram_results = (unsigned int *)malloc(257*3*sizeof(unsigned int));

    err = clEnqueueReadBuffer(queue, histogram_buffer, CL_TRUE, 0, 256*3*sizeof(unsigned int), histogram_results, 0, NULL, NULL);
    if (err)
    {
        printf("clEnqueueReadBuffer() failed. (%d)\n", err);
        return EXIT_FAILURE;
    }

    // save histogram
    save_histogram(output, histogram_results);

    // now measure performance
    err = clEnqueueMarker(queue, &events[0]);
    if (err)
    {
        printf("clEnqeueMarker() failed for histogram_rgba_unorm8 kernel. (%d)\n", err);
        return EXIT_FAILURE;
    }

    for (i=0; i<NUM_ITERATIONS; i++)
    {
        err = clEnqueueNDRangeKernel(queue, histogram_rgba_unorm8, 2, NULL, global_work_size, local_work_size, 0, NULL, NULL);
        if (err)
        {
            printf("clEnqueueNDRangeKernel() failed for histogram_rgba_unorm8 kernel. (%d)\n", err);
            return EXIT_FAILURE;
        }
        
        err = clEnqueueNDRangeKernel(queue, histogram_sum_partial_results_unorm8, 1, NULL, partial_global_work_size, partial_local_work_size, 0, NULL, NULL);
        if (err)
        {
            printf("clEnqueueNDRangeKernel() failed for histogram_sum_partial_results_unorm8 kernel. (%d)\n", err);
            return EXIT_FAILURE;
        }        
    }

  
    //clReleaseEvent(events[0]);
    //clReleaseEvent(events[1]);

    //free(histogram_results);
    //free(image_data_unorm8);

    //clReleaseKernel(histogram_rgba_unorm8);
    //clReleaseKernel(histogram_sum_partial_results_unorm8);
    

    clReleaseProgram(program);    


    clReleaseMemObject(partial_histogram_buffer);
    clReleaseMemObject(histogram_buffer);
    clReleaseMemObject(input_image_unorm8);


    return EXIT_SUCCESS;
}


/**
 * main
 */
int 
main(int argc, char **argv)
{

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputImageFile> " << std::endl;
        return EXIT_FAILURE;
    } 

    std::string input = argv[1];


    std::string fname  = getFileNameWithoutExt(input);
    std::string output = fname + "_hist.txt";

	// Initialize DevIL.
	ilInit();

    int ret = image_histogram(input, output);
    if(ret != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    std::cout<< "image histogram Successfull" << std::endl;
    return EXIT_SUCCESS;

}

