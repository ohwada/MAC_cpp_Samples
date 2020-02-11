/**
 * OpenCV Sample
 * 2020-01-01 K.OHWADA
 */

#include <string> 
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include "parse_filename.hpp"

using namespace cv;
using namespace std;


/**
 * calcKernelSize
 */
static inline int calcKernelSize(int radius)
{
    return 2*radius+1;
}


/**
 * str2d
 */
double  str2d(std::string str)
{
    char* end;
    double ret =  strtod(str.c_str(), &end);
    return ret;
}


/**
 * d2str
 */
std::string d2str( double num, std::string format )
{

    char buffer[50]; 
    snprintf (buffer, sizeof(buffer), format.c_str(), num);

    std::string ret = buffer;

    return ret;
}


/**
 * createOutputFileName
 */
std::string createOutputFileName(std::string input, int radius, double sigma )
{

    char UNDER_BAR = '_';

    std::string dir;
    std::string title;
    std::string ext;
    parseFileName(input, dir, title, ext);

    int ksize = calcKernelSize(radius);
    std::string str_ksize = std::to_string(ksize);

    std::string str_sigma = d2str(sigma, "%0.1f");

    // extension must be PNG 
    std::string output = title + UNDER_BAR + str_ksize + "x" + str_ksize + UNDER_BAR + str_sigma + UNDER_BAR + ".png";

    return output;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "OpenCV Version: " << CV_VERSION << endl;

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <inputImageFile> <radius> <sigma>"  << endl;
        return 1;
    }

    // specify filename from commandline 
   string input = argv[1];

    int radius =  std::atoi(argv[2]);

    double sigma =  str2d(argv[3]);

    string output = createOutputFileName(input, radius, sigma);

    //load as color image
    Mat img = imread(input);


    // GaussianBlur
    Mat dst;
    int ksize = calcKernelSize(radius);
    GaussianBlur(img, dst, Size(ksize, ksize), sigma, sigma);

    // save image
    imwrite(output, dst);

    cout << "save to: " << output << endl;

    return 0;
}
