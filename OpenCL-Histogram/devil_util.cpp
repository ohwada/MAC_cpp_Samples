/**
 * Devil Sample
 * 2020-02-01 K.OHWADA
 */

// Caution
// DevIL saving images upside-down
// https://www.gamedev.net/forums/topic/467011-devil-saving-images-upside-down/


#include "devil_util.hpp" 

// macro 
#define PRINT_ERROR_MACRO printf("Error: 0x%X\n", (unsigned int)Error)

// global variable
ILenum Error;


/**
 * loadImage
 */
char*  devil_loadImage(std::string fileName, int &width, int &height)
{
	ILuint	ImgId;

	// Generate the main image name to use.
	ilGenImages(1, &ImgId);

	// Bind this image name.
	ilBindImage(ImgId);

	// Loads the image specified by File into the image named by ImgId.
    bool ret = ilLoadImage(fileName.c_str());
	if (!ret) {
		std::cerr << "could not load Image: " << fileName << std::endl;
		return NULL;
	}

    width = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT);

    int bufsize = 4 * width * height; 
    char *buff =  new char[bufsize];

    ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA,
IL_UNSIGNED_BYTE, buff);

    return buff;
}


/**
 * saveImage
 */
bool  devil_saveImage(std::string fileName, char *data, int width, int height)
{
	ILuint	ImgId;


// DevIL saving images upside-down
// https://www.gamedev.net/forums/topic/467011-devil-saving-images-upside-down/

// therefore, reverse image orientation
    char* buff = reverseUpsideDown(data, width, height);


	// Generate the main image name to use.
	ilGenImages(1, &ImgId);

	// Bind this image name.
	ilBindImage(ImgId);

    bool ret1 = ilTexImage(width,
    height, 1, 4,
    IL_RGBA, IL_UNSIGNED_BYTE, buff);
    if(!ret1){
        std::cerr << "ilTexImage faild" << std::endl;
        return false;
    }

    ilSetPixels(
        0,
        0,
        0,
        width,
        height,
        1,
        IL_RGBA,
        IL_UNSIGNED_BYTE,
        buff
    );

	// Enable this to let us overwrite the destination file if it already exists.
	ilEnable(IL_FILE_OVERWRITE);

	// save image
	bool ret2 = ilSaveImage(fileName.c_str());
	if (!ret2) {
		std::cerr << "could not save Image: " << fileName << std::endl;
        return false;
	}

	// We're done with the image, so let's delete it.
	ilDeleteImages(1, &ImgId);

    return true;
}


/**
 * reverse UpsideDown
 */
char* reverseUpsideDown(char *src, int width, int height)
{

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
            buff[buf_index + 0] = src[src_index + 0]; // R
            buff[buf_index + 1] = src[src_index + 1]; // G
            buff[buf_index + 2] = src[src_index + 2]; // B
            buff[buf_index + 3] = src[src_index + 3]; // A
        }
    }

    return buff;
}


/**
 * printError
 */
void devil_printError()
{
	// Simple Error detection loop that displays the Error to the user in a human-readable form.
    while ((Error = ilGetError())) {
	    PRINT_ERROR_MACRO;
    }

}

