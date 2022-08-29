#pragma once
/**
 * png_util.h
 * 2022-06-01 K.OHWADA
 */


#include<iostream>
#include <string> 
#include <vector>
#include <png++/png.hpp>


// prototype
std::vector<char> loadImage1(std::string input, int &width, int &height);
char* loadImage2(std::string input, int &width, int &height);
bool saveImage(std::string output, std::vector<char> data, int width, int height);
bool saveImage(std::string output, char* data, int width, int height);


/**
 * loadImage1
 */
std::vector<char> loadImage1(std::string input, int &width, int &height)
{

    std::vector<char> vec;

    try{
        // read image
        png::image< png::rgba_pixel > image(input);

        width = image.get_width();
        height = image.get_height();

        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){
                    png::rgba_pixel p = image[y][x];
                    char r = p.red;
                    char g = p.green;
                    char b = p.blue;
                    char a = p.alpha;
                    vec.push_back(r);
                    vec.push_back(g);
                    vec.push_back(b);
                    vec.push_back(a);
            } // x
        } // y

    }
    catch (std::exception const& error)
    {
            std::cerr << "Faild: " << error.what() << std::endl;
            width = 0;
            height = 0;
    }

    return vec;
}


/**
 * loadImage2
 */
char* loadImage2(std::string input, int &width, int &height)
{

char *data;

    try{
        // read image
        png::image< png::rgba_pixel > image(input);

        width = image.get_width();
        height = image.get_height();

    int size = 4*width * height;
    data = (char *)calloc(size, sizeof(char));

        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){
                    int index = 4*width*y + 4*x;
                    png::rgba_pixel p = image[y][x];
                    char r = p.red;
                    char g = p.green;
                    char b = p.blue;
                    char a = p.alpha;
                    data[index] = r;
                    data[index+1] = g;
                    data[index+2] = b;
                    data[index+3] = a;
            } // x
        } // y

    }
    catch (std::exception const& error)
    {
            std::cerr << "Faild: " << error.what() << std::endl;
            width = 0;
            height = 0;
            return nullptr;
    }

    return data;
}


/**
 * saveImage
 */
bool saveImage(std::string output, std::vector<char> data, int width, int height)
{
    try
    {

        png::image< png::rgba_pixel > image(width, height);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                    int index = 4*width*y + 4*x;
                    char r = data[index +0];
                    char g = data[index +1];
                    char b = data[index +2];
                    char a = data[index +3];
                    png::rgba_pixel pix(r, g, b, a);
                    image.set_pixel(x, y, pix);
            } // x
        }// y

        image.write(output);

    }
    catch (std::exception const& error)
    {
        std::cerr << "save image Faild: " << error.what() << std::endl;
        return false;
    }

    return true;
}


/**
 * saveImage
 */
bool saveImage(std::string output, char* data, int width, int height)
{
    try
    {

        png::image< png::rgba_pixel > image(width, height);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                    int index = 4*width*y + 4*x;
                    char r = data[index +0];
                    char g = data[index +1];
                    char b = data[index +2];
                    char a = data[index +3];
                    png::rgba_pixel pix(r, g, b, a);
                    image.set_pixel(x, y, pix);
            } // x
        }// y

        image.write(output);

    }
    catch (std::exception const& error)
    {
        std::cerr << "save image Faild: " << error.what() << std::endl;
        return false;
    }

    return true;
}
