// Sobel Edge Detection Filter
// 2020-01-01 K.OHWADA

// reference : OpenCL Programming Guide
// http://www.heterogeneouscompute.org/?page_id=5

//
// The operator uses two 3 x 3 kernels which are convolved with the
// original image to compute derivatives, one for horizontal changes
// & another for vertical.
//
// Gx, the horizontal derivative, is computed using the following
// 3 x 3 kernel:
//
//         [  -1     0    +1 ]
//  Gx =   [  -2     0    +2 ]
//         [  -1     0    +1 ]
//
// Gy, the vertical derivative, is computed using the following
// 3 x 3 kernel:
//
//         [  -1    -2    -1 ]
//  Gy =   [   0     0     0 ]
//         [  +1    +2    +1 ]
//

const sampler_t sampler = CLK_ADDRESS_CLAMP_TO_EDGE |
                          CLK_FILTER_NEAREST;
 kernel void
sobel_rgb(read_only image2d_t src, write_only image2d_t dst)
{
    int x = (int)get_global_id(0);
    int y = (int)get_global_id(1);

    if (x >= get_image_width(src) || y >= get_image_height(src))
        return;

    float4 p00 = read_imagef(src, sampler, (int2)(x - 1, y - 1));
    float4 p10 = read_imagef(src, sampler, (int2)(x,     y - 1));
    float4 p20 = read_imagef(src, sampler, (int2)(x + 1, y - 1));
    float4 p01 = read_imagef(src, sampler, (int2)(x - 1, y));
    float4 p21 = read_imagef(src, sampler, (int2)(x + 1, y));
    float4 p02 = read_imagef(src, sampler, (int2)(x - 1, y + 1));
    float4 p12 = read_imagef(src, sampler, (int2)(x,     y + 1));
    float4 p22 = read_imagef(src, sampler, (int2)(x + 1, y + 1));

    float3 gx = -p00.xyz + p20.xyz +
                 2.0f * (p21.xyz - p01.xyz)
                -p02.xyz + p22.xyz;
    float3 gy = -p00.xyz - p20.xyz +
                 2.0f * (p12.xyz - p10.xyz) +
                 p02.xyz + p22.xyz;
    float3  g = native_sqrt(gx * gx + gy * gy);

 // we could also approximate this as g = fabs(gx) + fabs(gy)
    write_imagef(dst, (int2)(x, y), (float4)(g.x, g.y, g.z, 1.0f));
 }

