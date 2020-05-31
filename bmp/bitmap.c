/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

// this sample support 24 bit uncompressed bmp format
// original : https://github.com/kawasin73/todai-bmp
//  Copied from http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#include"bitmap.h"


/**
 * Read_Bmp
 *  read Bitmap file
 *  and put height, width and RGB btmap in img structure
 */
Image *Read_Bmp(char *filename)
{
    int i, j;

    // number of bytes for one line on File data
    int real_width;

    // horizontal and vertical number of pixels
    unsigned int width, height;
 
    // number of imsge bits           
    unsigned int color;

    // header information
    unsigned char header_buf[HEADERSIZE]; 
   
    // one line image data
    unsigned char *bmp_line_data;  

    FILE *fp;

    Image *img;

    if((fp = fopen(filename, "rb")) == NULL){
        fprintf(stderr, "Error: %s could not read.", filename);
        return NULL;
    }


        // read all header parts
    fread(header_buf, sizeof(unsigned char), HEADERSIZE, fp); //

    // check the first 2 bytes BM (Bitmap file)
    if(strncmp((const char *)header_buf, (const char *)"BM", 2)){
        fprintf(stderr, "Error: %s is not Bitmap file.", filename);
        return NULL;
    }

    // the apparent width of the image
    memcpy(&width, header_buf + 18, sizeof(width));

    // image height
    memcpy(&height, header_buf + 22, sizeof(height));

    // imsge bits
    memcpy(&color, header_buf + 28, sizeof(unsigned int));

    // finish if not 24bit
    if(color != 24){
        fprintf(stderr, "Not support %d bit : %s ", color, filename);
        return NULL;
    }

// match RGB bitmap to one line
// because it must be a multiple of 4 bytes
    real_width = width*3 + width%4;

    // Buffer to fetch RGB bitmap for one line 
    if((bmp_line_data = (unsigned char *)malloc(sizeof(unsigned char)*real_width)) == NULL){
        fprintf(stderr, "Error: Allocation error.\n");
        return NULL;
    }

    // Buffer for capturing RGB bitmap
    if((img = Create_Image(width, height)) == NULL){
        free(bmp_line_data);
        fclose(fp);
        return NULL;
    }

    // the RGB bitmap of the bmp file 
    // is arranged from bottom left to right, bottom to top
    for(i=0; i<height; i++){
        fread(bmp_line_data, 1, real_width, fp);
        for(j=0; j<width; j++){
            img->data[(height-i-1)*width + j].b = bmp_line_data[j*3];
            img->data[(height-i-1)*width + j].g = bmp_line_data[j*3 + 1];
            img->data[(height-i-1)*width + j].r = bmp_line_data[j*3 + 2];
        }
    }

    free(bmp_line_data);

    fclose(fp);

    return img;
}


/**
 * Write_Bmp
 */
int Write_Bmp(char *filename, Image *img)
{
    int i, j;
    FILE *fp;
    int real_width;


    // stores RGB bitmap for one line
    unsigned char *bmp_line_data;

    // store header
    unsigned char header_buf[HEADERSIZE];

    unsigned int file_size;
    unsigned int offset_to_data;
    unsigned long info_header_size;
    unsigned int planes;
    unsigned int color;
    unsigned long compress;
    unsigned long data_size;
    long xppm;
    long yppm;

    if((fp = fopen(filename, "wb")) == NULL){
        fprintf(stderr, "Error: %s could not open.", filename);
        return 1;
    }

    real_width = img->width*3 + img->width%4;

    // create header from here
    file_size = img->height * real_width + HEADERSIZE;
    offset_to_data = HEADERSIZE;
    info_header_size = INFOHEADERSIZE;
    planes = 1;
    color = 24;
    compress = 0;
    data_size = img->height * real_width;
    xppm = 1;
    yppm = 1;

    header_buf[0] = 'B';
    header_buf[1] = 'M';
    memcpy(header_buf + 2, &file_size, sizeof(file_size));
    header_buf[6] = 0;
    header_buf[7] = 0;
    header_buf[8] = 0;
    header_buf[9] = 0;
    memcpy(header_buf + 10, &offset_to_data, sizeof(file_size));
    header_buf[11] = 0;
    header_buf[12] = 0;
    header_buf[13] = 0;

    memcpy(header_buf + 14, &info_header_size, sizeof(info_header_size));
    header_buf[15] = 0;
    header_buf[16] = 0;
    header_buf[17] = 0;
    memcpy(header_buf + 18, &img->width, sizeof(img->width));
    memcpy(header_buf + 22, &img->height, sizeof(img->height));
    memcpy(header_buf + 26, &planes, sizeof(planes));
    memcpy(header_buf + 28, &color, sizeof(color));
    memcpy(header_buf + 30, &compress, sizeof(compress));
    memcpy(header_buf + 34, &data_size, sizeof(data_size));
    memcpy(header_buf + 38, &xppm, sizeof(xppm));
    memcpy(header_buf + 42, &yppm, sizeof(yppm));
    header_buf[46] = 0;
    header_buf[47] = 0;
    header_buf[48] = 0;
    header_buf[49] = 0;
    header_buf[50] = 0;
    header_buf[51] = 0;
    header_buf[52] = 0;
    header_buf[53] = 0;

    // write header
    fwrite(header_buf, sizeof(unsigned char), HEADERSIZE, fp);

    if((bmp_line_data = (unsigned char *)malloc(sizeof(unsigned char)*real_width)) == NULL){
        fprintf(stderr, "Error: Allocation error.\n");
        fclose(fp);
        return 1;
    }

    //Write RGB bitmap
    for(i=0; i<img->height; i++){
        for(j=0; j<img->width; j++){
            bmp_line_data[j*3]            =    img->data[(img->height - i - 1)*img->width + j].b;
            bmp_line_data[j*3 + 1]    =    img->data[(img->height - i - 1)*img->width + j].g;
            bmp_line_data[j*3 + 2]            =    img->data[(img->height - i - 1)*img->width + j].r;
        }

    // adjust RGB ibitmap to a multiple of 4 bytes
        for(j=img->width*3; j<real_width; j++){
            bmp_line_data[j] = 0;
        }
        fwrite(bmp_line_data, sizeof(unsigned char), real_width, fp);
    }

    free(bmp_line_data);

    fclose(fp);

    return 0;
}


/**
 * Create_Image
 */
Image *Create_Image(int width, int height)
{
    Image *img;

    if((img = (Image *)malloc(sizeof(Image))) == NULL){
        fprintf(stderr, "Allocation error\n");
        return NULL;
    }

    if((img->data = (Rgb*)malloc(sizeof(Rgb)*width*height)) == NULL){
        fprintf(stderr, "Allocation error\n");
        free(img);
        return NULL;
    }

    img->width = width;
    img->height = height;

    return img;
}

//release RGB bitmap
void Free_Image(Image *img)
{
    free(img->data);
    free(img);
}


