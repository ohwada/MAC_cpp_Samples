// Sobel Edge Detection Filter
// 2020-01-01 K.OHWADA

// reference : OpenCL Programming Guide
// http://www.heterogeneouscompute.org/?page_id=5

const sampler_t sampler = CLK_ADDRESS_CLAMP_TO_EDGE |
                          CLK_FILTER_NEAREST;

 kernel void
sobel_grayscale(read_only image2d_t src, write_only image2d_t dst)
{
    int x = (int)get_global_id(0);
    int y = (int)get_global_id(1);
    if (x >= get_image_width(src) || y >= get_image_height(src))
        return;

    float4 p00 = read_imagef(src, sampler, (int2)(x - 1, y - 1));
    float4 p10 = read_imagef(src, sampler, (int2)(x,     y - 1));
    float4 p20 = read_imagef(src, sampler, (int2)(x + 1, y - 1));
    float4 p01 = read_imagef(src, sampler, (int2)(x - 1, y));
    float4 p02 = read_imagef(src, sampler, (int2)(x - 1, y + 1));
    float4 p21 = read_imagef(src, sampler, (int2)(x + 1, y));
    float4 p12 = read_imagef(src, sampler, (int2)(x,     y + 1));
    float4 p22 = read_imagef(src, sampler, (int2)(x + 1, y + 1));

    float3 gx = -p00.xyz + p20.xyz +
                 2.0f * (p21.xyz - p01.xyz)
                -p02.xyz + p22.xyz;
    float3 gy = -p00.xyz - p20.xyz +
                 2.0f * (p12.xyz - p10.xyz) +
                 p02.xyz + p22.xyz;
    float gs_x = 0.3333f * (gx.x + gx.y + gx.z);
    float gs_y = 0.3333f * (gy.x + gy.y + gy.z);
    float g = native_sqrt(gs_x * gs_x + gs_y * gs_y);

    write_imagef(dst, (int2)(x, y), (float4)(g, g, g, 1.0f));
 }
