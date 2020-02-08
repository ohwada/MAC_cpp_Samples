// Gaussian Filter
// 2020-01-01 K.OHWADA
// chang Gaussian Kernel to 5x5
// original : https://github.com/bgaster/opencl-book-samples/tree/master/src/Chapter_8/ImageFilter2D


__kernel void gaussian_filter(__read_only image2d_t srcImg,
                              __write_only image2d_t dstImg,
                              sampler_t sampler,
                              int width, int height)
{

// Gaussian Kernel:
// https://homepages.inf.ed.ac.uk/rbf/HIPR2/gsmooth.htm
//
// 1 4 7 4 1
// 4 16 26 16 4
// 7 26 41 26 7
// 4 16 26 16 4
 // 1 4 7 4 1
//
    float kernelWeights[25] = 
        { 1.0f, 4.0f, 7.0f, 4.0f, 1.0f,
          4.0f, 16.0f, 26.0f, 16.0f, 4.0f,
          7.0f, 26.0f, 41.0f, 26.0f, 7.0f,
           4.0f, 16.0f, 26.0f, 16.0f, 4.0f,
           1.0f, 4.0f, 7.0f, 4.0f, 1.0f };

    int2 startImageCoord = (int2) (get_global_id(0) - 2, get_global_id(1) - 2);
    int2 endImageCoord   = (int2) (get_global_id(0) + 2, get_global_id(1) + 2);
    int2 outImageCoord = (int2) (get_global_id(0), get_global_id(1));

    if (outImageCoord.x < width && outImageCoord.y < height)
    {
        int weight = 0;
        float4 outColor = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
        for( int y = startImageCoord.y; y <= endImageCoord.y; y++)
        {
            for( int x = startImageCoord.x; x <= endImageCoord.x; x++)
            {
                outColor += (read_imagef(srcImg, sampler, (int2)(x, y)) * (kernelWeights[weight] / 273.0f));
                weight += 1;
            }
        }

        // Write the output value to image
        write_imagef(dstImg, outImageCoord, outColor);
    }
}
