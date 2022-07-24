/**
 * version.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ version.cpp -o version -std=c++11 -lopencv_core

#include <opencv2/core/utility.hpp>
#include <iostream>


/**
 * main
 */
int main(int argc, const char* argv[])
{
        std::cout << "Welcome to OpenCV: " << CV_VERSION << std::endl;
        std::cout << cv::getBuildInformation() << std::endl;
        return 0;
}

// Welcome to OpenCV: 4.1.2-dev
