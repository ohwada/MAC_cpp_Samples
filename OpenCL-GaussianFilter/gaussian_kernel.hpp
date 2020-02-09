/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 */

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>


typedef std::vector<double> kernel_row;
typedef std::vector<kernel_row> kernel_type;


static inline int calcKernelSize(int radius)
{
    return 2*radius+1;
}


double gaussian( double x, double mu, double sigma );

kernel_type produce2dGaussianKernel(int kernelRadius, double sigma);

void printGaussianKernel(kernel_type kernel2d);

float* convFloatArray1D(kernel_type kernel2d, int radius);

void printGaussianKernelTitle(int radius, double sigma);

double  str2d(std::string str);

std::string d2str( double num, std::string format );

