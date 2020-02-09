// Gaussian Filter
// 2020-01-01 K.OHWADA

__kernel void gaussian_filter(
        __read_only image2d_t srcImg,
        __write_only image2d_t dstImg,
        __constant float * weights,
                    sampler_t sampler,
                     int width, 
                    int height, 
                    int radius)
{

    int2 startImageCoord = (int2) (get_global_id(0) - radius, get_global_id(1) - radius);
    int2 endImageCoord   = (int2) (get_global_id(0) + radius, get_global_id(1) + radius);
    int2 outImageCoord = (int2) (get_global_id(0), get_global_id(1));

    if (outImageCoord.x < width && outImageCoord.y < height)
    {
        int index = 0;
        float4 outColor = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
        for( int y = startImageCoord.y; y <= endImageCoord.y; y++)
        {
            for( int x = startImageCoord.x; x <= endImageCoord.x; x++)
            {
                outColor += (read_imagef(srcImg, sampler, (int2)(x, y)) * (weights[index]));
                index += 1;
            }
        }

        // Write the output value to image
        write_imagef(dstImg, outImageCoord, outColor);
    }
}
