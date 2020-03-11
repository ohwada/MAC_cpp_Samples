/**
 * Freeimage Sample
 * 2020-02-01 K.OHWADA
 */


// Caution
//FreeImage macOS Version has 
// the BUG that swwaps between Red ch and Blue ch 
// and reverse upside down
// https://sourceforge.net/p/freeimage/discussion/36110/thread/28c0cdfd/

#include "freeimage_util.hpp"


/**
 * loadImage
 * reverse upside down 
 * swap R and B
 */
char* fi_loadImage(std::string filename, int &width, int &height)
{

    FIBITMAP* bitmap = fi_loadBitmap(filename);

    char* data = fi_convertTo32Bits(bitmap, width, height);

    return reverseAndSwap(data, width, height);


}


/**
 * saveImage
 * reverse upside down 
 * swap R and B
 * 
 * writable extensiton :png, tif, bmp
 * NOT writable : jpg, gif
 */
bool fi_saveImage(std::string fileName, char *data, int width, int height)
{

    char* converted =  reverseAndSwap(data, width, height);

    FIBITMAP * bitmap = fi_convertFromRawBits(converted, width, height);

    return fi_saveBitmap(fileName, bitmap);

}


/**
 * loadBitmap
 */
FIBITMAP* fi_loadBitmap(std::string filename)
{

        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(), 0);
        FIBITMAP* image = FreeImage_Load(format, filename.c_str());
        if(!image) {
                std::cerr << "Load Failed: " << filename << std::endl;
                return NULL;
        }

    return image;

}


/**
 * saveBitmap
 */
bool fi_saveBitmap(std::string fileName, FIBITMAP* bitmap)
{

        FREE_IMAGE_FORMAT format = 
        FreeImage_GetFIFFromFilename(fileName.c_str());

    return FreeImage_Save(format, bitmap, fileName.c_str(), 0);

}


/**
 * convertTo32Bits
 */
char* fi_convertTo32Bits(FIBITMAP* bitmap, int &width, int &height)
{


        width = FreeImage_GetWidth(bitmap);
        height = FreeImage_GetHeight(bitmap);

        // Convert to 32-bit image
        FIBITMAP* bitmap32 = FreeImage_ConvertTo32Bits(bitmap);

        //copy to buffer
    int bufsize = 4 * width * height;
    char* buffer = new char[bufsize];
        memcpy(buffer, FreeImage_GetBits(bitmap32), bufsize);


        //Release image data
        FreeImage_Unload(bitmap);
        FreeImage_Unload(bitmap32);

    return buffer;

}


/**
 * convertFromRawBits
 */
FIBITMAP * fi_convertFromRawBits(char *data, int width, int height)
{

        FIBITMAP *bitmap = FreeImage_ConvertFromRawBits(
            (BYTE*)data, 
            width,
            height,
            (4*width),  // pitch
            32, // bpp
            0xFF000000,  // red_mask
            0x00FF0000,  // green_mask
            0x0000FF00  // blue_mask
        );

        return bitmap;
}


/**
 * reverse UpsideDown
 * swap R and B
 */
char* reverseAndSwap(char *src, int width, int height)
{


// https://sourceforge.net/p/freeimage/discussion/36110/thread/28c0cdfd/

// https://stackoverflow.com/questions/56727077/bitmap-is-loaded-mirrored-and-inverted


    int bufsize = 4 * width * height;
    char* buff = new char[bufsize];

    for(int y = 0;  y<height; y++)
    {
        for(int x = 0; x<width; x++)
        {
            int col     = x;
            int row     = height - y - 1;
            int src_index   = (row * width + col) * 4;
            int index_rev  = (row * width + (width - col)) * 4;
            int buf_index = bufsize - index_rev;
            buff[buf_index + 0] = src[src_index + 2]; // R = B
            buff[buf_index + 1] = src[src_index + 1]; // G
            buff[buf_index + 2] = src[src_index + 0]; // B + R
            buff[buf_index + 3] = src[src_index + 3]; // A
        }
    }

    return buff;
}

