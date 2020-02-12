/**
 * OpenCL Sample
 * 2020-01-01 K.OHWADA
 */

// reference : https://stackoverflow.com/questions/8204645/implementing-gaussian-blur-how-to-calculate-convolution-matrix-kernel


#include "gaussian_kernel.hpp"


/**
 * gaussian
 */
double gaussian(int row, int col,  int radius, double sigma ) {
     double x = (double)(col - radius); 
     double y = (double)(row - radius);    
    double a = (x*x + y*y) / ( 2 * sigma * sigma );
    double ret = std::exp( -a ) / (2 * M_PI * sigma);
    return ret;
}


typedef std::vector<double> kernel_row;
typedef std::vector<kernel_row> kernel_type;


/**
 * produce2dGaussianKernel
 */
kernel_type produce2dGaussianKernel(int kernelRadius, double sigma) {

    int ksize = calcKernelSize(kernelRadius);
    kernel_type kernel2d(ksize, kernel_row(ksize));
    double sum = 0;
  // compute values
  for (int row = 0; row < kernel2d.size(); row++)
    for (int col = 0; col < kernel2d[row].size(); col++) {
        double x = gaussian(row, col, kernelRadius, sigma);
        kernel2d[row][col] = x;
        sum += x;
    }
  // normalize
  for (int row = 0; row < kernel2d.size(); row++)
    for (int col = 0; col < kernel2d[row].size(); col++)
      kernel2d[row][col] /= sum;
  return kernel2d;
}


/**
 *  convFloatArray1D
 */
float* convFloatArray1D(kernel_type kernel2d, int radius)
{

    int ksize = calcKernelSize(radius);
    int bufsize = ksize * ksize;
    float * buffer = new float[bufsize];
    int i = 0;

    for (int row = 0; row < kernel2d.size(); row++) {
        for (int col = 0; col < kernel2d[row].size(); col++) {
            buffer[i]  = kernel2d[row][col];
            i++;
        }
    }

    return buffer;
}


/**
 * printGaussianKernel
 */
void printGaussianKernel(kernel_type kernel2d) {

    const char LF = '\n';
    const char SPACE = ' ';

    std::cout << std::setprecision(5) << std::fixed;
    for (int row = 0; row < kernel2d.size(); row++) {
        for (int col = 0; col < kernel2d[row].size(); col++) {
            std::cout << kernel2d[row][col] << SPACE;
        }
        std::cout << LF;
    }
    std::cout << LF;
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
 * printGaussianKernelTitle
 */
void printGaussianKernelTitle(int radius, double sigma) {

    int ksize = calcKernelSize(radius);
    std::string str_ksize = std::to_string(ksize);

    std::string str_sigma = d2str( sigma, "%0.1f");

    std::cout << "Gaussian Kernel: " << str_ksize << " x " << str_ksize << " sigma= " << str_sigma << std::endl;
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
