/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 */


#include <cstdlib>

#include "gaussian_kernel.hpp"


/**
 * main
 */
int main(int argc, char** argv)
{

    if (argc < 3) {
        std::cerr << "USAGE: " << argv[0] << " <radius> <sigma>" << std::endl;
        return 1;
    }

    int radius =  std::atoi(argv[1]);
    int ksize = calcKernelSize(radius);

    std::string str_sigma =  argv[2];

    double sigma =  str2d(str_sigma);

    kernel_type kernel2d = produce2dGaussianKernel(radius, sigma);

    printGaussianKernelTitle(radius, sigma);
    printGaussianKernel(kernel2d);

}

